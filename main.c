#include <STC15F2K60S2.H>
#include <intrins.h>
#include "display.h"
#include "pwm.h"

#define foc 11059200ul
#define T0H 65536 - (2 * foc) / (12 * 1000)/ 256
#define T0L 65536 - (2 * foc) / (12 * 1000)% 256


typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;

sbit TLC594_CS = P1^5;
sbit TLC594_DOUT = P1^6;
sbit TLC594_CLK = P1^7;

bit Flag = 0; //这个是数码管扫描产生
bit Flag1 = 0; //这个是AD扫描产生标志

uint8_t ADcount = 0;

uint8_t bdata AdValue;
sbit AIN = AdValue^0;


void Timer0_Init();
uint16_t get_ADValue();

/************
/*This is the main function
************/
void main()
{
	uint8_t i = 0;
	uint8_t j = 0;
	
	uint8_t ucAdValue = 0;
	uint16_t uiAdValue = 0;
	
	float fAdValue = 0.0;
	
	Timer0_Init();
	
	while(1)
	{
		if(Flag1)
		{
			Flag1 = 0;
			ucAdValue = get_ADValue();
			fAdValue =(float)(ucAdValue * 5.0/255.0);
			uiAdValue = fAdValue*1000;
			show_number(uiAdValue);		
			pwm_out(ucAdValue);
		}
		if(Flag)
		{
			Flag = 0;
			led_scan();
			
		}
	}
}


uint16_t get_ADValue()
{
	uint8_t i;

	TLC594_CS = 0;
	TLC594_DOUT = 1;
	TLC594_CLK = 0;

	for(i = 0; i < 8; i ++)
	{
		AdValue = AdValue << 1;
		TLC594_CLK = 1;
		_nop_();
		_nop_();
		AIN = TLC594_DOUT;
		TLC594_CLK = 0;

		_nop_();
		_nop_();		
	}
	TLC594_CS = 1;
	return AdValue;
}


void Timer0_Init() //Initialize the timer.
{
    TMOD = 0x01;
    TH0 = T0H;
    TL0 = T0L;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0_ISR() interrupt 1
{   
    TH0 = T0H;
    TL0 = T0L;	
	Flag = 1;
	pwm_timer(255);
    if(ADcount ++ >= 20)
    {
        ADcount = 0;
        Flag1 = 1;
    }
}
