#include <STC8G.H>
#include "intrins.h"
#define U8 unsigned char
sbit K=P5^4;
U8 i;
U8 disp_zhr[7]={0x7E,0x13,0x00,0x02,0x00,0x01,0xEF};
void Delay2ms(void)	//@22.1184MHz
{
	unsigned char data i, j;

	_nop_();
	_nop_();
	i = 58;
	j = 112;
	do
	{
		while (--j);
	} while (--i);
}
void Uart1_Init(void)	//9600bps@22.1184MHz
{
	EA=1;
	ES=1;
	REN=1;
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xC0;			//设置定时初始值
	TH1 = 0xFD;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}
void main()
{
	P1M1 = 0x00; P1M0 = 0x00; //P1
	P3M1 = 0x00; P3M0 = 0x00; //P3
	P5M1 = 0x00; P5M0 = 0x00; //P5
	Uart1_Init();
	while(1)
	{
		if(K==0)
		{
			while(K==0);
			for(i=0;i<7;i++)
			{
				P_SW1=0X40;
				SBUF=disp_zhr[i];
				while(TI);
				Delay2ms();
			}
		}
	}						   
}
void zhr() interrupt 4
{
	if(TI)
	{ 
		TI=0;
	}                                                                                                                     
	if(RI)
	{	
		RI=0;												
	}	
}