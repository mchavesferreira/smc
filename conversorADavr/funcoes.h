#ifndef FUNCOES_H
#define FUNCOES_H

extern volatile unsigned int tempo[];

extern void IO_init(void);
extern void Timer0_init(void);
extern int Read_ADC(int canal);
extern void Set_PWM_T1A(uint16_t valor);
extern void Set_PWM_T1B(uint16_t valor);
extern void Set_PWM_T1C(uint16_t valor);

#endif

