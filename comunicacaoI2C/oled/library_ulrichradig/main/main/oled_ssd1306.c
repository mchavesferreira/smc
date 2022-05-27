/*
 *  Created: 19.06.2016 11:38:00
 *  Author: Ulrich
 */ 

#include "oled_ssd1306.h"
#include "font.h"

static uint8_t oled_x = 0, oled_y = 0, font_size = 0;

const uint8_t ssd1306_init_cmd [] PROGMEM = {
SET_DISPLAY_OFF,
COMMAND_NO_OPERATION,
SET_MEMORY_ADDR_MODE, HORIZONTAL_ADDRESSING_MODE,
SET_PAGE_START,
SET_COM_OUTPUT_REMAPPED, 
SET_LOWER_COLUMN,
SET_HIGHER_COLUMN,
SET_DISPLAY_START_LINE,			
ENTIRE_DISPLAY_ON, 
SET_SEGMENT_REMAP_O2,
SET_DISPLAY_NORMAL,	
SET_CONTRAST_CONTROL,	0xFF,	
SET_MULTIPLEX_RATIO,	0x3F,	
SET_DISPLAY_OFFSET,		0x00, 
SET_DISPLAY_CLOCK,		0xF0,
SET_PRECHARGE_PERIOD,	0x22, 
SET_COM_PINS,			0x12, 
SET_VCOMH_DESELECT,		0x20, 
CHARGE_BUMB_SETTING,	0x14, 
SET_DISPLAY_ON };

//***************************************************************************************
void i2c_init(void){
	I2C_PORT |= (1 << SDA_PIN | 1 << SCL_PIN);			//Port Pullup
	TWCR = 0;
	TWSR = 0;
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
	_delay_ms(50);
}

//***************************************************************************************
uint8_t i2c_start (void){
	uint8_t timeout = 0;
    TWCR = (1 << TWINT | 1 << TWSTA | 1 << TWEN);
    while(!(TWCR & (1<<TWINT))){
	    if((timeout++) > 100) return 1;
    }
    TWDR = OLED_I2C_ADDR;
    TWCR = (1 << TWINT | 1 << TWEN);
	timeout = 0;
    while(!(TWCR & (1<<TWINT))){
	    if((timeout++) > 100) return 1;
    }
	return 0;
}

//***************************************************************************************
uint8_t i2c_byte (uint8_t byte){  
	uint8_t timeout = 0;
    TWDR = byte;
    TWCR = (1 << TWINT | 1 << TWEN);
    while(!(TWCR & (1<<TWINT))){
		if((timeout++) > 100) return 1;
	}
	return 0;
}

//***************************************************************************************
void i2c_stop (void){
    TWCR = (1 << TWINT | 1 << TWSTO | 1 << TWEN);
	TWCR = 0;
}

//***************************************************************************************
void oled_init (void){
	i2c_init();
	i2c_start();
	i2c_byte(COMMAND);
	for (uint8_t tmp = 0; tmp< sizeof(ssd1306_init_cmd); tmp++) {	
		i2c_byte(pgm_read_byte(&ssd1306_init_cmd[tmp]));
	}
	i2c_stop();
    oled_clear_screen();
}

//***************************************************************************************
void oled_clear_screen (void){
	oled_gotoxy(0,0);
	i2c_start();
    i2c_byte(DATA);
    for (uint16_t i = 0; i < 128<<4 ; i++) {	// 128 * (64 / Byte) 
        i2c_byte(0);	
    }
    i2c_stop();
	oled_gotoxy(0,0);
}

//***************************************************************************************
void oled_gotoxy (uint8_t x, uint8_t y){
	oled_x = x;
	oled_y = y;
    i2c_start();		
    i2c_byte(COMMAND);
    i2c_byte(SET_PAGE_START|y);
	i2c_byte(SET_COLUMN_ADDRESS);
    i2c_byte(x * 8);
	i2c_byte(SET_DISPLAY_START_LINE|0x3F);
    i2c_stop();			
}

//***************************************************************************************
void oled_font_size (uint8_t byte){
	font_size = byte;
}

//***************************************************************************************
void oled_write_char (char c){
	if(font_size != 0){		
		uint8_t tmp = 0;
		oled_gotoxy(oled_x,oled_y);
		i2c_start();
		i2c_byte(DATA);
		for (uint8_t count = 0; count < 8; count++){
			tmp = pgm_read_byte(&font[(unsigned char)c][count]);
			tmp = tmp & 0x0f;
			tmp = ((tmp&0x01)*3)+(((tmp&0x02)<<1)*3)+(((tmp&0x04)<<2)*3)+(((tmp&0x08)<<3)*3);
			i2c_byte(tmp);
			i2c_byte(tmp);
		}
		i2c_stop();
		oled_gotoxy(oled_x,oled_y + 1);
		i2c_start();
		i2c_byte(DATA);
		for (uint8_t count = 0; count < 8; count++){
			tmp = pgm_read_byte(&font[(unsigned char)c][count]);
			tmp = (tmp & 0xf0)>>4;
			tmp = ((tmp&0x01)*3)+(((tmp&0x02)<<1)*3)+(((tmp&0x04)<<2)*3)+(((tmp&0x08)<<3)*3);
			i2c_byte(tmp);
			i2c_byte(tmp);
		}
		i2c_stop();
		oled_x +=2;
		oled_y -=1;
	}else{
		oled_gotoxy(oled_x,oled_y);
		i2c_start();
		i2c_byte(DATA);
		for (uint8_t count = 0; count < 8; count++){
			i2c_byte(pgm_read_byte(&font[(unsigned char)c][count]));
		}
		i2c_stop();
		oled_x +=1;
	}
}

//***************************************************************************************
void oled_write_str (char* str){
    while (*str) {
        oled_write_char(*str++);
    }
}

//***************************************************************************************
void oled_write_P (const char *Buffer,...)
{
	va_list ap;
	va_start (ap, Buffer);	
	
	int format_flag;
	char str_buffer[10];
	char str_null_buffer[10];
	char move = 0;
	char Base = 0;
	int tmp = 0;
	char by;
	char *ptr;
		
	//Ausgabe der Zeichen
    for(;;){
		by = pgm_read_byte(Buffer++);
		if(by==0) break; // end of format string
            
		if (by == '%'){
            by = pgm_read_byte(Buffer++);
			if (isdigit(by)>0){                   
 				str_null_buffer[0] = by;
				str_null_buffer[1] = '\0';
				move = atoi(str_null_buffer);
                by = pgm_read_byte(Buffer++);
				}

			switch (by){
                case 's':
                    ptr = va_arg(ap,char *);
                    while(*ptr) { oled_write_char(*ptr++); }
                    break;
				case 'b':
					Base = 2;
					goto ConversionLoop;
				case 'c':
					//Int to char
					format_flag = va_arg(ap,int);
					oled_write_char (format_flag++);
					break;
				case 'i':
					Base = 10;
					goto ConversionLoop;
				case 'o':
					Base = 8;
					goto ConversionLoop;
				case 'x':
					Base = 16;
					//****************************
					ConversionLoop:
					//****************************
					itoa(va_arg(ap,int),str_buffer,Base);
					int b=0;
					while (str_buffer[b++] != 0){};
					b--;
					if (b<move){
						move -=b;
						for (tmp = 0;tmp<move;tmp++){
							str_null_buffer[tmp] = '0';
							}
						//tmp ++;
						str_null_buffer[tmp] = '\0';
						strcat(str_null_buffer,str_buffer);
						strcpy(str_buffer,str_null_buffer);
						}
					oled_write_str (str_buffer);
					move =0;
					break;
				}
		}else{
			oled_write_char (by);	
		}
	}
	va_end(ap);
}

