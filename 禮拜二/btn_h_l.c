#include "AT89X52.H"
sfr  LED=0x80;
sbit KEY=0xA2;
sbit speak=0xA6;
main(){
	LED=0;
	while(1)
	{
		do
		{
			while(KEY==1);
				Delay_ms(20);
		}
		while(KEY==1);
		LED++;
		do
		{
			while(KEY==0);
				Delay_ms(20);
		}
		while(KEY==0);
	}

}