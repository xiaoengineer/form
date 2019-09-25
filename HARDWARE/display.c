#include "display.h"

typedef unsigned int uint16_t;
typedef unsigned char uint8_t;

uint8_t code seg_ment[] ={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80, 0x90};
uint8_t seg_buff[4] = {0xff, 0xff,  0xff ,0xff};

sbit COM1 = P1^3;
sbit COM2 = P1^2;
sbit COM3 = P1^1;
sbit COM4 = P1^0;

/*
函数名称：show_number(u8 mode, u16 dat)
参数： void
返回值： void
说明：更新seg_buff[]
作者：王慧云
时间：2019.3.26
*/
void led_scan(void)
{
	static uint8_t i = 0;
	P3 = 0XFF;
	P3 = seg_buff[i];
	switch(i)
	{
//		case 0: 
//			COM1 = 0; COM2 = 1; COM3 = 1; COM4 = 1; break;
//		case 1: 
//			COM1 = 1; COM2 = 0; COM3 = 1; COM4 = 1; break;
//		case 2: 
//			COM1 = 1; COM2 = 1; COM3 = 0; COM4 = 1; break;
//		case 3: 
//			COM1 = 1; COM2 = 1; COM3 = 1; COM4 = 0; break;	
		case 0: 
			COM1 = 1; COM2 = 0; COM3 = 0; COM4 = 0; break;
		case 1: 
			COM1 = 0; COM2 = 1; COM3 = 0; COM4 = 0; break;
		case 2: 
			COM1 = 0; COM2 = 0; COM3 = 1; COM4 = 0; break;
		case 3: 
			COM1 = 0; COM2 = 0; COM3 = 0; COM4 = 1; break;	
	}
	if(i >= 3)
	{
		i = 0;
	}
	else 
		i ++;
}

/*
函数名称：show_number(uint8_t dat)
参数： u8 mode, u16 dat
返回值： void
说明：  mode是显示模式选择0为显示频率， 1为显示电压,2为关
		dat为显示的数据
作者：王慧云
时间：2019.3.26
*/
void show_number(uint16_t dat)
{
	char i;
	uint8_t buff[4];
	
	for(i = 0; i < 4; i ++)
	{
		buff[i] = dat % 10;
		dat = dat / 10;
	}
	
	for(i = 3; i >= 0; i --)
	{
		if(buff[i] == 0)
		{
			seg_buff[i] = 0xC0;
		}
		else
			break;
	}
	
	for(; i >= 0; i --)
	{
		seg_buff[i] = seg_ment[buff[i]];
	}
	seg_buff[3] = seg_buff[3] & 0x7f;
}