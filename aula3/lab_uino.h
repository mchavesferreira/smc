

#define F_CPU 8000000UL 

#define Liga_D0() PORTD |= (1<<4)
#define Liga_D1() PORTD |= (1<<6)
#define Liga_D2() PORTD |= (1<<7)
#define Liga_D3() PORTB |= (1<<4)
#define Liga_D4() PORTB |= (1<<5)
#define Liga_D5() PORTB |= (1<<6)
#define Liga_D6() PORTC |= (1<<6)
#define Liga_D7() PORTC |= (1<<7)

#define Desliga_D0() PORTD &= ~(1<<4)
#define Desliga_D1() PORTD &= ~(1<<6)
#define Desliga_D2() PORTD &= ~(1<<7)
#define Desliga_D3() PORTB &= ~(1<<4)
#define Desliga_D4() PORTB &= ~(1<<5)
#define Desliga_D5() PORTB &= ~(1<<6)
#define Desliga_D6() PORTC &= ~(1<<6)
#define Desliga_D7() PORTC &= ~(1<<7)

#define Toggle_D0() PORTD ^= (1<<4)
#define Toggle_D1() PORTD ^= (1<<6)
#define Toggle_D2() PORTD ^= (1<<7)
#define Toggle_D3() PORTB ^= (1<<4)
#define Toggle_D4() PORTB ^= (1<<5)
#define Toggle_D5() PORTB ^= (1<<6)
#define Toggle_D6() PORTC ^= (1<<6)
#define Toggle_D7() PORTC ^= (1<<7)

#define Liga_Strobe() PORTB |= (1<<7)
#define Liga_Feed() PORTB |= (1<<3)
#define Liga_Sel_in() PORTB |= (1<<1)
#define Liga_Init() PORTB |= (1<<2)

#define Desliga_Strobe() PORTB &= ~(1<<7)
#define Desliga_Feed() PORTB &= ~(1<<3)
#define Desliga_Sel_in() PORTB &= ~(1<<1)
#define Desliga_Init() PORTB &= ~(1<<2)

#define Toggle_Strobe() PORTB ^= (1<<7)
#define Toggle_Feed() PORTB ^= (1<<3)
#define Toggle_Sel_in() PORTB ^= (1<<1)
#define Toggle_Init() PORTB ^= (1<<2)

#define Ch_error_lig !(PIND & (1<<0))
#define Ch_ack_lig !(PIND & (1<<1))
#define Ch_busy_lig !(PIND & (1<<5))
#define Ch_prog_lig !(PINE & (1<<2))
#define Ch_paper_out_lig !(PINF & (1<<7))
#define Ch_sel_out_lig !(PINF & (1<<6))

#define Ch_error_des (PIND & (1<<0))
#define Ch_ack_des (PIND & (1<<1))
#define Ch_busy_des (PIND & (1<<5))
#define Ch_prog_des (PINE & (1<<2))
#define Ch_paper_out_des (PINF & (1<<7))
#define Ch_sel_out_des (PINF & (1<<6))

#define Liga_LCD_RS() PORTB |= (1<<0)
#define Desliga_LCD_RS() PORTB &= ~(1<<0)
#define Toggle_LCD_RS() PORTB ^= (1<<0)

#define Liga_LCD_E() PORTE |= (1<<6)
#define Desliga_LCD_E() PORTE &= ~(1<<6)
#define Toggle_LCD_E() PORTE ^= (1<<6)
