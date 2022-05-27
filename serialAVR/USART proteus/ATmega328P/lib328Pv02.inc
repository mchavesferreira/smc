; Arquivo de sub-rotinas de uso geral para o ATMEGA328P - Versão 01

.def delay_time = r25		
.def display_number = r24		
.def eeprom_address = r23
.def eeprom_number = r22
.def transmit_caracter = r21	
.def receive_caracter = r15	
.def adc_value = r14
.def pwm_value = r20
.def overflow_counter = r13
.def lcd_caracter = r19
.def lcd_number = r18		
.def lcd_col = r17	
.def aux =	r16		

.equ rs_lcd = pd2
.equ enable_lcd = pd3

; ### Sub-rotina de atraso em segundos ###
delay_seconds:
	ldi r31,82
	ldi r30,0
	ldi r29,0		
loop_delay:
	dec r29					
	brne loop_delay			
	dec r30					
	brne loop_delay			
	dec r31					
	brne loop_delay			
	dec delay_time					
	brne delay_seconds		
	ret						

; ### Sub-rotina de atraso em milisegundos ###
delay_miliseconds:
	ldi r30,22
	ldi r29,0			
loop_delayms:
	dec r29					
	brne loop_delayms			
	dec r30						
	brne loop_delayms			
	dec delay_time						
	brne delay_miliseconds		
	ret
	
; ### Sub-rotina de atraso de 1 microsegundo ###   1 ciclo = 1/16MHz = 62.5ns   16 ciclos = 16*62.5ns = 1us
delay_1microsecond:
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	nop							
	ret							

; ### Sub-rotina para mostrar a dezena e unidade em dois displays de 7-segmentos (Dezena: pd7,pd6,pd5,pd4 - Unidade: pd3,pd2,pd1,pd0)  ###
display_write:
	ldi aux,0b11111111
	out ddrd,aux
	ldi r30,0				
	ldi r31,0				
	mov r31,display_number			
	cpi display_number,10				
	brlo display_show					
display_loop:
	sbci r31,10				
	inc r30					
	cpi r31,10				
	brlo display_show					
	rjmp display_loop					
display_show:	
	ldi r29,0					
	mov r29,r30				
	swap r29					
	or r29,r31				
	out portd,r29				
	ret				

; ### Sub-rotina para apagar o display de 7-segmentos ###
display_off:
	ldi aux,0b11111111
	out ddrd,aux
	ldi r30,0b11111111
	out portd,r30
	ret
	
; ### Sub-rotina para escrita na eeprom ###
eeprom_write:
	sbic EECR,EEPE					
	rjmp eeprom_write
	out EEARL,eeprom_address		
	out EEDR,eeprom_number			
	sbi EECR,EEMPE					
	sbi EECR,EEPE					
	ret

; ### Sub-rotina para leitura na eeprom ###
eeprom_read:
	sbic EECR,EEPE					
	rjmp eeprom_read
	out EEARL,eeprom_address		
	sbi EECR,EERE					
	in eeprom_number,EEDR				
	ret
	
; ### Sub-rotina de configuração da USART em 9600bps ###
usart_init:
	ldi r30,0			
	sts UBRR0H,r30		 
	ldi r30,103			
	sts UBRR0L,r30		
	ldi r30,0b00011000	
	sts UCSR0B,r30		 
	ret					
	
; ### Sub-rotina para transmissão de caracter pela USART ###
usart_transmit:
	lds r30,UCSR0A		
	sbrs r30,UDRE0     
	rjmp usart_transmit	
	sts UDR0,transmit_caracter		
	ret					

; ### Sub-rotina para transmissão de caracter pela USART ###
usart_receive:
	lds r30,UCSR0A		
	sbrs r30,RXC0		
	rjmp usart_receive	
	lds receive_caracter, UDR0		
	ret

; ### Sub-rotina ADC com 8 bits => LSB = Vref/(2^n-1) = 5/255 =~ 20mV => 0b00000001 =~ 20mV ###
analog_read:
	ldi r30,0b00100000
	sts ADMUX,r30
	ldi r30,0b11000111
	sts ADCSRA,r30
loop_ad:
	lds r30, ADCSRA		
	sbrc r30, ADSC		
	rjmp loop_ad
	lds adc_value,ADCH
	ret

; ### Sub-rotina PWM de 8 bits e 500Hz pela PB2 ###
pwm_write:
	sbi ddrb,pb2
	ldi r30,0b10100001
	sts TCCR1A,r30
	ldi r30,0
	sts OCR1BH,r30
	mov r30,pwm_value
	sts OCR1BL,r30
	ldi r30,0b00000011
	sts TCCR1B,r30
	ret

; ### Sub-rotina Start Timer1 (1 pulso de clock = 62.5ns) Pre-scale de 64 e timer1 de 16bits => Cada estouro acontece a cada 64*65536*62.5ns = 0.262s ###
start_timer1:
	ldi r30,0b00000011		   
	sts TCCR1B,r30			   
	ldi r30,0b00000001		   
	sts TIMSK1,r30			   
	sei						  
	ret						   

; ### Sub-rotina Stop Timer1 (1 pulso de clock = 62.5ns) Pre-scale de 64 e timer1 de 16bits => Cada estouro acontece a cada 64*65536*62.5ns = 0.262s ###
stop_timer1:
	ldi r30,0b00000000			
	sts TCCR1B,r30
	ldi r30,0b00000000			
	sts TIMSK1,r30
	ldi r30,0b00000000			
	sts TCNT1H,r30				
	sts TCNT1L,r30
	ldi r30,0					
	mov overflow_counter,r30
	ret
	
; ### Sub-rotina para inicialização do LCD no PORTD ###
lcd_init:
	sbi ddrd,2
	sbi ddrd,3
	sbi ddrd,4
	sbi ddrd,5
	sbi ddrd,6
	sbi ddrd,7
	cbi portd,rs_lcd			
	cbi portd,enable_lcd		
	cbi portd,pd7				
	cbi portd,pd6
	cbi portd,pd5
	cbi portd,pd4
	ldi delay_time,15			
	rcall delay_miliseconds		 
	cbi portd,pd7				
	cbi portd,pd6
	sbi portd,pd5
	sbi portd,pd4
	rcall pulse_enable
	ldi delay_time,5			
	rcall delay_miliseconds		
	cbi portd,pd7				
	cbi portd,pd6
	sbi portd,pd5
	sbi portd,pd4
	rcall pulse_enable
	ldi delay_time,5			
	rcall delay_miliseconds		
	cbi portd,pd7				
	cbi portd,pd6
	sbi portd,pd5
	sbi portd,pd4
	rcall pulse_enable
	ldi delay_time,5			
	rcall delay_miliseconds		
	cbi portd,pd7				
	cbi portd,pd6
	sbi portd,pd5
	cbi portd,pd4
	rcall pulse_enable
	ldi delay_time,1			
	rcall delay_miliseconds		
	ldi lcd_caracter,0x28			
	rcall lcd_write_caracter				
	ldi lcd_caracter,0x0C			
	rcall lcd_write_caracter				
	ldi lcd_caracter,0x01			
	rcall lcd_write_caracter				
	ldi delay_time,2			
	rcall delay_miliseconds		
	ldi lcd_caracter,0x06			
	rcall lcd_write_caracter				
	sbi portd,rs_lcd			
	ret							
	
; ### Sub-rotina para limpar o LCD ###
lcd_clear:
	cbi portd, rs_lcd			
	ldi lcd_caracter,1				
	rcall lcd_write_caracter				
	ldi delay_time,2			
	rcall delay_miliseconds		
	sbi portd,rs_lcd			
	ret
	
; ### Sub-rotina para escrever um caracter no LCD ###
lcd_write_caracter:
	sbrc lcd_caracter,7
	sbi portd,pd7
	sbrs lcd_caracter,7
	cbi portd,pd7
	sbrc lcd_caracter,6
	sbi portd,pd6
	sbrs lcd_caracter,6
	cbi portd,pd6
	sbrc lcd_caracter,5
	sbi portd,pd5
	sbrs lcd_caracter,5
	cbi portd,pd5
	sbrc lcd_caracter,4
	sbi portd,pd4
	sbrs lcd_caracter,4
	cbi portd,pd4
	rcall pulse_enable
	sbrc lcd_caracter,3
	sbi portd,pd7
	sbrs lcd_caracter,3
	cbi portd,pd7
	sbrc lcd_caracter,2
	sbi portd,pd6
	sbrs lcd_caracter,2
	cbi portd,pd6
	sbrc lcd_caracter,1
	sbi portd,pd5
	sbrs lcd_caracter,1
	cbi portd,pd5
	sbrc lcd_caracter,0
	sbi portd,pd4
	sbrs lcd_caracter,0
	cbi portd,pd4
	rcall pulse_enable
	ret
	
; ### Sub-rotina para gerar um pulso de enable e aguardar =~50us ###
pulse_enable:
	cbi portd,enable_lcd		
	rcall delay_1microsecond
	sbi portd,enable_lcd		
	rcall delay_1microsecond
	cbi portd,enable_lcd
	ldi r26,50
loop_pulse:
	rcall delay_1microsecond
	dec r26
	cpi r26,0
	brne loop_pulse
	ret

; ### Sub-rotina para posicionar cursor na linha 0 do LCD ###
lcd_lin0_col:
	cbi portd,rs_lcd			
	ldi r30,0x80
	add lcd_col,r30
	mov lcd_caracter,lcd_col			
	rcall lcd_write_caracter				
	sbi portd,rs_lcd			
	ret

; ### Sub-rotina para posicionar cursor na linha 1 do LCD ###
lcd_lin1_col:
	cbi portd,rs_lcd			
	ldi r30,0xC0
	add lcd_col,r30
	mov lcd_caracter,lcd_col			
	rcall lcd_write_caracter				
	sbi portd,rs_lcd			
	ret

; ### Sub-rotina para escrever um numero de 0 a 99 no LCD ###
lcd_write_number:
	ldi r31,0				
	ldi r30,0				
	mov r30,lcd_number			
	cpi lcd_number,10				
	brlo lcd_show					
lcd_loop:
	sbci r30,10				
	inc r31					
	cpi r30,10				
	brlo lcd_show					
	rjmp lcd_loop					
lcd_show:	
	ldi r29,48
	add r30,r29
	add r31,r29
	mov lcd_caracter,r31
	rcall lcd_write_caracter
	mov lcd_caracter,r30
	rcall lcd_write_caracter
	ret