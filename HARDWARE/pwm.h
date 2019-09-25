#ifndef __PWM_H_
#define __PWM_H_

#include <STC15F2K60S2.H>

void pwm_out(unsigned int cycle);
void pwm_timer(unsigned int  period);

#endif
