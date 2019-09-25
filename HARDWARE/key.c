#include "key.h"
 
sbit KEY1 = P2^0;
sbit KEY2 = P2^1;
sbit KEY3 = P2^2;
sbit KEY4 = P2^3;

unsigned char keySta[4] = {1,1,1,1};
unsigned char keyMap[4] = {'s', 'u', 'd', 'q'};
/*
函数名称：key_drive(void)
参数： void
返回值： void
说明：更新key_buff[]
作者：王慧云
时间：2019.3.26
*/
void key_scan()
{
    unsigned char i;
    static unsigned char key_suff[4] ={0xff,0xff,0xff,0xff};

    key_suff[0] = (key_suff[0] << 1) | KEY1;
    key_suff[1] = (key_suff[1] << 1) | KEY2;
    key_suff[2] = (key_suff[2] << 1) | KEY3;
    key_suff[3] = (key_suff[3] << 1) | KEY4;
    
    for(i = 0; i < 4; i ++)
    {
        if((key_suff[i] & 0x0f) == 0x0f)
        {
            keySta[i] = 1;
        }
        if((key_suff[i] & 0x0f) == 0x00)
        {
            keySta[i] = 0;
        }
        else
        {}
    }
}

/*
函数名称：key_drive(void)
参数： void
返回值： unsigned char res
说明：函数返回值为 S7:0xeX; S6:0xdX
				S5:0xcX; S4: 0XbX
				X[0,1]: 0时为第一次按下
						1时为第二次按下
作者：王慧云
时间：2019.3.26
*/
unsigned char key_drive(void)
{
    unsigned char i, res;
    static unsigned char backup[4] = {1,1,1,1};
    for(i = 0; i < 4; i ++)
    {
		if(backup[i] != keySta[i])
		{
			if(backup[i] != 0)
			{
				res = keyMap[i];
			}
			else 
				res = 0xff;
         }
         backup[i] = keySta[i];  
    }
	return res;
}

