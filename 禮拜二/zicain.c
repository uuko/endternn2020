#include "AT89X52.H"
sfr Data=0x80;
sbit SSLED0=0x90;
sbit SSLED1=0x91;
sbit SSLED2=0x92;
sbit SSLED3=0x93;
sbit KEY=0xB2;
sbit speak=0xA6;
unsigned int Num =5900;
unsigned char i;
unsigned char code Table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void beep(unsigned char k);
void main()
{
	unsigned char scan;
	while(1)
	{
		for(scan=0;scan<250;scan++)
		{
				while(KEY==0) //偵測KEY(P3.2)是否被按下
			 {
					beep(1); //進入蜂鳴器副程式
					scan=0; //將SCAN歸零確保秒數後小數點重數
			 }
				SSLED0=SSLED1=SSLED2=SSLED3=1; //將七段顯示器全數關閉
				i=Num % 10; //抽出個位數
				Data=~Table[i]; //把個位數對應的七段顯示器陣列給DATA
				SSLED0=0; //把第一個七段顯示器(個位數)打開
				Delay_ms(1); //延遲1ms
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=(Num % 100)/10; //抽出十位數
				Data=~Table[i]; //把十位數對應的七段顯示器陣列給DATA
				SSLED1=0; //把第二個七段顯示器(十位數)打開
				Delay_ms(1);
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=(Num % 1000)/100; //抽出百位數
				Data=~Table[i]; //把百位數對應的七段顯示器陣列給DATA
				SSLED2=0; //把第三個七段顯示器(百位數)打開
				Delay_ms(1);
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=Num / 1000; //抽出千位數
				Data=~Table[i]; //把千位數對應的七段顯示器陣列給DATA
				SSLED3=0; //把第四個七段顯示器(千位數)打開
				Delay_ms(1);
		}
		Num++; //計數器數字加一
		if ( Num%100==60 )
		{
			Num=Num+100;
			Num=Num-60;
		}
		if (Num>6000) Num=0; //計數器到6000時歸零
	}
}
void beep(unsigned char k) //蜂鳴器副程式在P3.2按下時計數器一樣加一
{
		unsigned int j;
		while(k--)
		{
				for(j=0;j<100;j++)
				{
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num % 10;
					Data=~Table[i];
					SSLED0=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 100)/10;
					Data=~Table[i];
					SSLED1=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 1000)/100;
					Data=~Table[i];
					SSLED2=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num / 1000;
					Data=~Table[i];
					SSLED3=0;
					Delay_ms(1);
					speak=!speak;
				}
				for(j=0;j<150;j++)
				{
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num % 10;
					Data=~Table[i];
					SSLED0=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 100)/10;
					Data=~Table[i];
					SSLED1=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 1000)/100;
					Data=~Table[i];
					SSLED2=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num / 1000;
					Data=~Table[i];
					SSLED3=0;
					Delay_ms(1);
					speak=!speak;
				}
			Num++;
		}
}