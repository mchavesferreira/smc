///  biblioteca para cafeteira

//definiçao para acessar a memória flash 
PROGMEM const char msg_bemvindo[] = "Bem vindo !!!            \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_quantasxicaras[] = "Quantas xicaras         \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_escolhertamanho[] = "Tamanho xicara           \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_escolhercafe[] = "Deseja Cafe?          \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_escolherleite[] = "Deseja Leite?           \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_escolhercha[] = "Deseja Cha?     \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_recebendo[] = "Recebendo     \0"; //mensagem armazenada na memoria Flash

//XX  criar outras mensagens
//XX
//XX
PROGMEM const char msg_inicializando[] = "Em processo....      \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_fim[] = "Fim do processo         \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_enchendoagua[] = ">agua            \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_enchendocafe[] = ">cafe            \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_enchendoleite[] = ">leite          \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_enchendocha[] = ">cha          \0"; //mensagem armazenada na memoria Flash
//XX
PROGMEM const char msg_reiniciando[] = "Reiniciando....    \0"; //mensagem armazenada na memoria Flash
PROGMEM const char msg_um[] =   "[1]  2 ";
PROGMEM const char msg_dois[] = " 1  [2] ";
PROGMEM const char msg_tamanhoP[] = "[P]  M   G   ";
PROGMEM const char msg_tamanhoM[] = " P  [M]  G   ";
PROGMEM const char msg_tamanhoG[] = " P   M  [G]  ";
PROGMEM const char msg_sim[] = "[sim]  nao ";  // =1
PROGMEM const char msg_nao[] = " sim  [nao]";  //=0


unsigned char  quantidade_bicos = 1;
unsigned char  quantidaaguaPMG =1;
unsigned char  tempo_cafe = 0;  // tempo cafe sera em funcao do tamanhoda xicara (P=3, M=6 ou G=9)
unsigned char  tempo_leite = 0;
unsigned char  tempo_quantidaaguaPMG = 0;
unsigned char  tempo_cha = 0;
unsigned char  tempo_acucar = 0;
unsigned char  tempo_chocolate = 0;
unsigned char  tempo_capuccino = 0;

unsigned char flag1;  // 8 bits

// flags   1 bit de posição de memória. Neste caso utilizando para indicar Verdadeiro ou Falso
#define inseriu_cartao 0
#define  deseja_cafe 1
#define  deseja_leite 2
#define  deseja_cha 3
#define  deseja_acucar 4
#define  deseja_chocolate 5
#define  deseja_capuccino 6


////
////  funcoes
///
void estado_inicial()  
{
	pressionado=0;   // variavel
	cmd_LCD(0x80,0);  //limpa display
	escreve_LCD_Flash(msg_bemvindo);  // imprime mensagem
	USART_Transmite('I');
    USART_Transmite('\n');
	if(!tempo) {    // vefica tempo=0
	           estado=1;  //muda de estado
	           cmd_LCD(0x01,0);  // posiciona cursor
			   		 USART_Transmite('J');
			   		 USART_Transmite('\n');
		       }	
} // fim estado inicial

void configura_quantidadexicaras()
{
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_quantasxicaras); // imprime mensagem lcd linha 0

	cmd_LCD(0xC2,0);	//posiciona numero no lcd linha 1
	if(quantidade_bicos==1) escreve_LCD_Flash(msg_um);
	if(quantidade_bicos==2) escreve_LCD_Flash(msg_dois);
	
	if(!tst_bit(PINC,0)) { quantidade_bicos++; if(quantidade_bicos>2){ quantidade_bicos=1; } _delay_ms(200); }  //if botao+
	if(!tst_bit(PINC,1)) { estado=2;  _delay_ms(300); cmd_LCD(0x01,0); }	
}

void configura_tamanhoxicara() {
	cmd_LCD(0x80,0); 
	escreve_LCD_Flash(msg_escolhertamanho); // imprime mensagem
	cmd_LCD(0xC2,0);	//posiciona numero no lcd linha 1
	if(quantidaaguaPMG==1) escreve_LCD_Flash(msg_tamanhoP);
	if(quantidaaguaPMG==2) escreve_LCD_Flash(msg_tamanhoM);
	if(quantidaaguaPMG==3) escreve_LCD_Flash(msg_tamanhoG);

	if(!tst_bit(PINC,0)) { quantidaaguaPMG++; if(quantidaaguaPMG>3){ quantidaaguaPMG=1; } _delay_ms(200); }  //if botao+
	if(!tst_bit(PINC,1)) { estado=3;  _delay_ms(300); cmd_LCD(0x01,0); 
		 USART_Transmite('L');
		 USART_Transmite('\n');}

}

void configura_desejacafe()
{
	 cmd_LCD(0x80,0); 	
	 escreve_LCD_Flash(msg_escolhercafe);

	 cmd_LCD(0xC0,0);	
	 //deseja_cafe
	 if(tst_bit(flag1, deseja_cafe)) { escreve_LCD_Flash(msg_sim); } else { escreve_LCD_Flash(msg_nao); }
	 
	 if(!tst_bit(PINC,0)) { cpl_bit(flag1, deseja_cafe); _delay_ms(200);   }
	 if(!tst_bit(PINC,1)) { estado=4;  _delay_ms(300); cmd_LCD(0x01,0); 
	 	  USART_Transmite('M');
	 	  USART_Transmite('\n');}
}

void configura_desejaleite ()
{
	cmd_LCD(0x80,0);
	 escreve_LCD_Flash(msg_escolherleite);

	 cmd_LCD(0xC0,0);
	 if(tst_bit(flag1, deseja_leite)) { escreve_LCD_Flash(msg_sim); } else { escreve_LCD_Flash(msg_nao); }
	 
	 if(!tst_bit(PINC,0)) { cpl_bit(flag1, deseja_leite); _delay_ms(200);   }
	 if(!tst_bit(PINC,1)) { estado=5;  _delay_ms(300); cmd_LCD(0x01,0);
	 	 USART_Transmite('N');
	 	 USART_Transmite('\n'); }
}


void configura_desejacha ()
{
	cmd_LCD(0x80,0);
	escreve_LCD_Flash(msg_escolhercha);

	cmd_LCD(0xC0,0);
	if(tst_bit(flag1, deseja_cha)) { escreve_LCD_Flash(msg_sim); } else { escreve_LCD_Flash(msg_nao); }
	
	if(!tst_bit(PINC,0)) { cpl_bit(flag1, deseja_cha); _delay_ms(200);   }
	if(!tst_bit(PINC,1)) { estado=6;  _delay_ms(300); cmd_LCD(0x01,0);  tempo=8; 
	 USART_Transmite('O');
	 USART_Transmite('\n');}
}

//XX
//XX  Criar outras configurações acucar capuccino chocolate
//XX
void inicializando_processo()
{
	 cmd_LCD(0x80,0); 	escreve_LCD_Flash(msg_inicializando);

	 ident_num(tempo,digitos);
	 cmd_LCD(0xC5,0);
	 cmd_LCD(digitos[2],1);
	 cmd_LCD(digitos[1],1);
	 cmd_LCD(digitos[0],1);
   	
   	// tempos em funcao da escolha do tamanho da xicara
   	if(quantidaaguaPMG==1) { tempo_quantidaaguaPMG=3; tempo_cafe=3;  tempo_leite=3;}
   	if(quantidaaguaPMG==2) { tempo_quantidaaguaPMG=6; tempo_cafe=6; tempo_leite=6;}
   	if(quantidaaguaPMG==3) { tempo_quantidaaguaPMG=9; tempo_cafe=9; tempo_leite=9;}	 
	 
	 if(!tempo) 
	     {
		 estado=7; 
		 cmd_LCD(0xC0,0); escreve_LCD_Flash(msg_enchendoagua);   // mensagem da proxima etapa	
		  USART_Transmite('Q');
		  USART_Transmite('\n');
		 tempo=tempo_quantidaaguaPMG;  // tempo passado para o próximo estado
		 }


	 
		 
}
void enchendoagua()
      {
		 // enchendo agua por tamanho
	 //  if(quantidade_bicos==2) set_bit(PORTB,0);    // abre valvula para duas xicaras	
    	set_bit(PORTB,2);

		     /// imprimindo tempo para acompanhar processo OPCIONAL
		 	 ident_num(tempo,digitos);   
		 	 cmd_LCD(0xCD,0);
             cmd_LCD(digitos[2],1);
		 	 cmd_LCD(digitos[1],1);
		 	 cmd_LCD(digitos[0],1);
         if(!tempo)
         {
                clr_bit(PORTB,2);
                tempo=tempo_cafe;  // tempo passado para o próximo estado
                estado=8;
				cmd_LCD(0xC0,0); escreve_LCD_Flash(msg_enchendocafe);   // mensagem da proxima etapa
				 USART_Transmite('R');
				 USART_Transmite('\n');
	    	}
      }


void preparando_cafe()
        {
		if(tst_bit(flag1, deseja_cafe)) 
		  {
              set_bit(PORTB,3);
        //     _delay_ms(1);
         //    tempo--;
		     /// imprimindo tempo para acompanhar processo OPCIONAL
		     ident_num(tempo,digitos);
		     cmd_LCD(0xCD,0);
		     cmd_LCD(digitos[2],1);
		     cmd_LCD(digitos[1],1);
		     cmd_LCD(digitos[0],1);

		     if(!tempo)
                {
                clr_bit(PORTB,3); 
                estado=9;        //XX  próxima etapa
			                  //   
			     tempo=tempo_leite;  // tempo ms passado para o próximo estado
                 cmd_LCD(0xC0,0); escreve_LCD_Flash(msg_enchendoleite);   // mensagem da proxima etapa
				 USART_Transmite('S');
				 USART_Transmite('\n');
	           }
		       } else
		      { estado=9;  // pula para proximo estado sem abri esta valvula
				   USART_Transmite('S');
				   USART_Transmite('\n');
		      }
        
  }	  
  
  void preparando_leite()
      {
		           //XX  próxima etapa, porem etapas nao prontas deslocando para reiniciar
		if(tst_bit(flag1, deseja_leite))
		{
			set_bit(PORTB,4);
		//	_delay_ms(1);
		//	tempo--;
			/// imprimindo tempo para acompanhar processo OPCIONAL
			ident_num(tempo,digitos);
			cmd_LCD(0xCD,0);
			cmd_LCD(digitos[2],1);
			cmd_LCD(digitos[1],1);
			cmd_LCD(digitos[0],1);

			if(!tempo)
			{
				clr_bit(PORTB,4);
				estado=10;        //XX  próxima etapa
				//
				tempo=tempo_cha;  // tempo ms passado para o próximo estado
				cmd_LCD(0xC0,0); escreve_LCD_Flash(msg_enchendocha);   // mensagem da proxima etapa
				 USART_Transmite('T');
				 USART_Transmite('\n');
			}
		} else
		{ estado=10;  // pula para proximo estado sem abri esta valvula
				 USART_Transmite('T');
				 USART_Transmite('\n');
		}
		

      }
  
void preparando_cha()
{
		           //XX  próxima etapa, porem etapas nao prontas deslocando para reiniciar
		           if(tst_bit(flag1, deseja_cha))
		           {
			           set_bit(PORTB,5);
	
			           /// imprimindo tempo para acompanhar processo OPCIONAL
			           ident_num(tempo,digitos);
			           cmd_LCD(0xCD,0);
			           cmd_LCD(digitos[2],1);
			           cmd_LCD(digitos[1],1);
			           cmd_LCD(digitos[0],1);

			           if(!tempo)
			           {
				           clr_bit(PORTB,5);
				           estado=11;        //XX  próxima etapa
				           //
				           tempo=tempo_cha;  // tempo ms passado para o próximo estado
				           cmd_LCD(0xC0,0); escreve_LCD_Flash(msg_fim);   // mensagem da proxima etapa
						   USART_Transmite('U');
						   USART_Transmite('\n');
			           }
		           } else
		           { estado=11;  // pula para proximo estado sem abri esta valvula
					   	 USART_Transmite('U');
					   	 USART_Transmite('\n');
		           }
}


void preparando_acucar()
{
	estado=14;  
	// XX adaptar exemplo da rotina preparando_cafe()
}

void preparando_capuccino()
{
	// XX adaptar exemplo da rotina preparando_cafe()
}

void preparando_chocolate()
{
	// XX adaptar exemplo da rotina preparando_cafe()
}

void reinicializando()
            {
		    PORTB=0;  // desliga todas valvulas]
			flag1=0;  // desliga todos bits de escolha
			// reinicia valor padrao para tempos
			tempo_cafe = 0;  
			tempo_leite = 0;
			tempo_quantidaaguaPMG = 0;
			tempo_cha = 0;
			tempo_acucar = 0;
			tempo_chocolate = 0;
			tempo_capuccino = 0;
            estado=0;
            cmd_LCD(0x01,0);
            tempo=5;
            escreve_LCD_Flash(msg_reiniciando);
			 USART_Transmite('V');
			 USART_Transmite('\n');
            _delay_ms(1000);
            }
