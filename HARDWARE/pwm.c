#include "pwm.h"

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;

sbit PWM_OUT_IO = P1^4;
uint16_t PWM_CYCLE[] = {0};


void pwm_out(uint16_t cycle)
{
		PWM_CYCLE[0] = cycle;
}


void pwm_timer(uint16_t period)
{
	static uint16_t cnt = 0;
	cnt ++;
	if(cnt > period)
	{
		cnt = 0;
		PWM_OUT_IO = 1;
	}
	else if(cnt < PWM_CYCLE[0])
	{
		PWM_OUT_IO = 1;
	}
	else
	{
		PWM_OUT_IO = 0;
	}
	
}