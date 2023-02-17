//-------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								 //	
//-------------------------------------------------------------------------------------- //

#include "DS1307.h"
#include "LCD.h"

volatile unsigned char escrita, oper_TWI_concl, end_escr_leit, dado_escr, dado_leit, passo, cont_max_erro; 
unsigned char tempo[7], segs[14], aux_disp[4], flag_pontos = 1, cont = 0;
char escr[4];

//---------------------------------------------------------------------------------------
void inic_TWI()	//SCL = 100 kHz (limite do DS1307) com F_CPU = 16 MHz
{
	//Ajuste da frequência de trabalho - SCL = F_CPU/(16+2.TWBR.Prescaler) 
	TWBR = 18;		
	TWSR |= 0x01;							//prescaler =  4;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);	//habilita o TWI e a interrupção
}
//---------------------------------------------------------------------------------------
void escreve_DS1307(unsigned char end_escrita, unsigned char dado)
{
	//passa variaveis da função para as váriaveis globais alteradas na ISR
	
	escrita = 1;		//1 para escrita, 0 para leitura
	end_escr_leit = end_escrita;
	dado_escr = dado;
		
	oper_TWI_concl=0;	//trava do sistema até a conclusão da transmissão
	
	start_bit();		//envia o Start bit. Passo (1)
	passo = 1;
	cont_max_erro = 0xFF;
	
	while(oper_TWI_concl==0);//se for crítica a espera, o programa principal pode gerenciar esta operação
}
//---------------------------------------------------------------------------------------
unsigned char le_DS1307(unsigned char end_leitura)
{
	//passa variaveis da função para as váriaveis globais alteradas na ISR

	escrita = 0;		//1 para escrita 0 para leitura
	end_escr_leit = end_leitura;

	oper_TWI_concl=0;	//trava do sistema até a conclusão da transmissão
	
	start_bit();		//envia o Start bit. Passo (1)
	passo = 1;
	cont_max_erro=0xFF;
	
	while(oper_TWI_concl==0); //se for crítica a espera, o programa principal pode gerenciar esta operação
	return dado_leit;
	
}
//---------------------------------------------------------------------------------------
ISR(TWI_vect)//Rotina de interrupção da TWI
{
	static unsigned char fim_escrita;
		
	switch (TWSR & 0xF8)	//lê o código de resultado da TWI e executa a próxima ação
	{
		/*LEITURA E ESCRITA
		PASSO 2 <start condition transmitted>. Passo (1) concluído, executa passo (2)*/
		case (TW_START):													
						TWDR = 0xD0;			//envia endereço do dispositivo e o bit de escrita
						clr_start_bit();		//limpa o start bit 
						passo = 2;
						break;

		/*LEITURA E ESCRITA
		PASSO 3 <SLA+W transmitted, ACK received>. Passo (2) concluído, executa passo (3)*/
		case (TW_MT_SLA_ACK):				
						TWDR = end_escr_leit;	//envia o endereço de escrita ou leitura
						passo=3;
						fim_escrita=0;			//inicializa variavel para uso na escrita, PASSO 4
						break;

		/*LEITURA E ESCRITA
		PASSO 4 <data transmitted, ACK received>. Passo (3) concluído, executa passo (4).
				 Passo (4) concluído, executa passo (5) (só na escrita). O passo (4) para uma leitura é o reínicio*/
		case (TW_MT_DATA_ACK):			
						if(fim_escrita)			//se o passo (4) foi concluído executa o passo (5), escrita
						{	
							stop_bit();
							oper_TWI_concl = 1; //avisa que operação foi concluida
							break;
						}						
						if(escrita)	//envia um único dado quando for operação de escrita e depois um stop_bit()
						{
							TWDR = dado_escr;	//dado para escrita no endereço de escrita
							fim_escrita = 1;	//avisa que é o último dado a ser escrito
						}
						else
							start_bit();		//envia reínicio (só para operação de leitura) 
							
						passo = 4;					
						break;
						
		/*LEITURA
		PASSO 5 <repeated start condition transmitted>. Passo (4) concluído, executa o passo (5)*/
		case (TW_REP_START):				
						TWDR  = 0xD1;			//Envia endereço e read bit (4)
						clr_start_bit();		//limpa start bit 
						passo = 5;
						break;

		/*LEITURA
		PASSO 6 <SLA+R transmitted, ACK received>. Passo (5) concluído, prepara para a executação do NACK*/
		case (TW_MR_SLA_ACK) :			
						TWCR &=~(1<<TWEA);		//enviará um NACK após a recepção do dado
						passo=6;
						break;
	
		/*LEITURA
		PASSO 7 <data received, NACK returned>. Passo (6) concluído, NACK recebido, executa passo (7)*/ 
		case (TW_MR_DATA_NACK):		
						dado_leit = TWDR;		//dado lido
						stop_bit();
						oper_TWI_concl = 1;		//avisa que operação foi concluida
						break;

 		/*TRATAMENTO DOS POSSÍVEIS ERROS
		 Quando um erro acontece a operação errada é repetida até funcionar ou até
		 que o contador para o número máximo de tentavas chegue a zero*/
		 
		default: 
				cont_max_erro--;
				
				switch(passo)
				{
						case(1): start_bit(); break;
						case(2): TWDR = 0xD0; break;
						case(3): TWDR = end_escr_leit; break;
						case(4):
								if(escrita)
									TWDR = dado_escr;
								else
									start_bit();	//reínicio
								break;
						case(5): TWDR  = 0xD1; 		break;
						case(6): TWCR &=~(1<<TWEA); break;
				}
				if(cont_max_erro==0)//para saber se houve estouro na contagem ou insucesso na correção dos erros, basta ler cont_max_erro.
				{
					stop_bit();
					oper_TWI_concl = 1;			//libera o sistema
				}				
					
	}

	TWCR |= (1<<TWINT); //limpa flag de interrupção
}
//---------------------------------------------------------------------------------------
//Rotinas complementares para o trabalho com o LCD
//---------------------------------------------------------------------------------------
void converte2BCD(unsigned char dado, unsigned char endereco) 
{
   endereco = endereco + endereco;				//2 x endereço, sao dois digitos por dado
   segs[endereco] = dado & 0b00001111;			//BCD - primeiro digito - direita
   segs[endereco+1] = (dado & 0b11110000)>>4;	//BCD - segundo digito - esquerda

}//rotina para ler o dado do RTC e converter para o valor de segmento correto
//---------------------------------------------------------------------------------------
void ler_convert_tudo(unsigned char ende)//le todo o tempo do RTC e converte para o LCD
{	
	unsigned char j;
    
	for (j=0;j<7;j++)					//leitura e conversao do tempo do RTC
    {
      tempo[j] = le_DS1307(j+ende);		//salva todos os dados do relogio
      converte2BCD(tempo[j], j);
    }//j -> 0x00 segundos, 0x01 minutos, 0x02 horas, 0x03 dia semana, 0x04 dia mes, 0x05 mes, 0x06 ano. 
}
//---------------------------------------------------------------------------------------
void ajusta_tempo(unsigned char end, unsigned char limite,unsigned char ini_nr1)//endereco de ajuste e seu limite 
{ 
 //ini_nr1 -> flag para avisar se o nr. comeca em 1 (dia e mes)
   unsigned char aux, conta=0;
  
   aux = segs[end+end] + 10*segs[end+end+1];//converte 2 BCDs em 1 byte
   
   if (aux<limite)
      aux++;								//incremento no tempo
   else
      aux = 0;
      
   //converte aux para  2 BCD 
   if (aux<10)
      tempo[end] = aux;
   else
   { do
     { aux = aux - 10;
       conta++;
     }while(aux>9);
   }
     
   if(ini_nr1==1)
   {
    if (aux==0 && conta==0)					//se for dia e mes nao pode mostrar o zero
      aux = 1;
   }
     
   tempo[end] = aux + (conta<<4);			//monta o tempo ajustado - 2 BCDs
     
	escreve_DS1307(end,tempo[end]);			//altera o valor no RTC
}
//---------------------------------------------------------------------------------------
// Rotina que chama o ajuste_tempo conforme selecao de botao
//---------------------------------------------------------------------------------------
void ajusta_tempo2(unsigned char qual)
{

	 switch(qual)//qual ajuste sera efetuado
	 {
	   case 0: break;
	   case 1: ajusta_tempo(0x02, 23,0); break;		//ajusta as horas (0x02) e seu limite (23)
	   case 2: ajusta_tempo(0x01, 59,0); break;		//ajuste dos minutos
	   case 3: escreve_DS1307(0x00, 0x00); break;	//só zera os segundos
	   case 4: ajusta_tempo(0x04, 31,1); break;		//ajuste dos dias
	   case 5: ajusta_tempo(0x05, 12,1); break;		//ajuste dos meses 
	   case 6: ajusta_tempo(0x06, 99,0); break;		//ajuste do ano
	   case 7: ajusta_tempo(0x03, 7,1);  break;       
	 }//switch(count) 
}
//---------------------------------------------------------------------------------------
void mostra_tempo()//coloca os dados do RTC no formato padrao no LCD
{
	//mostrar tempo no LCD -> 1a linha, horas
	cmd_LCD(0x81,0);
	cmd_LCD(segs[5]+48,1);		//horas   
	cmd_LCD(segs[4]+48,1);
	cmd_LCD(0x84,0);// 
	cmd_LCD(segs[3]+48,1);		//minutos   
	cmd_LCD(segs[2]+48,1);
	cmd_LCD(0x87,0);			//espaço em branco 
	cmd_LCD(segs[1]+48,1);		//segundos   
	cmd_LCD(segs[0]+48,1); 
	//mostrar tempo no LCD -> 2a linha, calendário   
	cmd_LCD(0xC1,0);
	cmd_LCD(segs[9]+48,1);		//dia do mês  
	cmd_LCD(segs[8]+48,1); 
	cmd_LCD(0xC4,0);			//espaço em branco 
	cmd_LCD(segs[11]+48,1);		//mês   
	cmd_LCD(segs[10]+48,1);
	cmd_LCD(0xC7,0);			//espaço em branco 
	cmd_LCD(segs[13]+48,1);		//ano   
	cmd_LCD(segs[12]+48,1); 
   
   	switch(segs[6])				//dia da semana
	{
		case 1:  escr[0] = 'D'; escr[1] = 'o'; escr[2] = 'm'; break;
		case 2:  escr[0] = 'S'; escr[1] = 'e'; escr[2] = 'g'; break;         
		case 3:  escr[0] = 'T'; escr[1] = 'e'; escr[2] = 'r'; break;      
		case 4:  escr[0] = 'Q'; escr[1] = 'u'; escr[2] = 'a'; break;                   
		case 5:  escr[0] = 'Q'; escr[1] = 'u'; escr[2] = 'i'; break;         
		case 6:  escr[0] = 'S'; escr[1] = 'e'; escr[2] = 'x'; break;      
		case 7:  escr[0] = 'S'; escr[1] = 'a'; escr[2] = 'b'; break;
		default: escr[0] = 'x'; escr[1] = 'x'; escr[2] = 'x'; break;
	}//switch

	cmd_LCD(0xCC,0); 
	escreve_LCD(escr);			//mostra dia da semana
}
//---------------------------------------------------------------------------------------
void mostra_pontos(unsigned char desliga)	//coloca pontos e barra no display e limpa algumas posições
{
   if (desliga==1)
   {	
    	cmd_LCD(0x80,0);cmd_LCD(0x20,1);	//limpa antes da hora
		cmd_LCD(0x83,0);cmd_LCD(0x3A,1);	//dois pontos depois das horas
    	cmd_LCD(0x86,0);cmd_LCD(0x3A,1);	//dois pontos depois dos segundos
    	cmd_LCD(0xC0,0);cmd_LCD(0x20,1);	//limpa antes do dia do mês
    	cmd_LCD(0xC3,0);cmd_LCD(0x2F,1);	//barra inclinada depois do dia do mês
    	cmd_LCD(0xC6,0);cmd_LCD(0x2F,1);	//barra inclinada antes do ano
    	cmd_LCD(0xCB,0);cmd_LCD(0x20,1);	//limpa antes do dia da semana
	}
}
//---------------------------------------------------------------------------------------
void alerta_display(unsigned char qual)	//seta no display para o ajuste
{
    switch(qual)
    {
    case 1: cmd_LCD(0x80,0); break;		//horas
    case 2: cmd_LCD(0x83,0); break;		//minutos
    case 3: cmd_LCD(0x86,0); break;		//segundos
    case 4: cmd_LCD(0xC0,0); break;		//dia mes
    case 5: cmd_LCD(0xC3,0); break;		//mês
    case 6: cmd_LCD(0xC6,0); break;		//ano
    case 7: cmd_LCD(0xCB,0); break;		//dia da semana
    }//switch(count)
	
	if(cont!=0)				//este if é só para corrigir a seta na última pressionada do botao SELECAO, após o dia.
    	cmd_LCD(0x7E,1);	//-> seta para ajuste
}
//---------------------------------------------------------------------------------------