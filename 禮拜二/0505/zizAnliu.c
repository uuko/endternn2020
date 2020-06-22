#include "AT89X52.H"
unsigned char code Table[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,
0x5e,0x79,0x71
};
void beep(unsigned char i);
sbit speak=0xA6;
sbit   KEY=P3^2; 
sfr datta=0x80;
sbit ssled0=0x90;sbit ssled1=0x91; sbit ssled2=0x92; sbit ssled3=0x93;
void main(){
	unsigned int num =0001;
	unsigned char i;
	unsigned int scan;

	while(1){

		for( scan =0 ;scan<10;scan++){
			if(KEY==0){
				beep(2);
			}
			ssled0=ssled1=ssled2=ssled3=1;
			i=num%10;
			datta=~Table[i];
			ssled0=0;
			Delay_ms(1000);
			
			ssled0=ssled1=ssled2=ssled3=1;
			i=(num%100)/10;
			datta=~Table[i];
			ssled1=0;
			Delay_ms(1000);
			
			ssled0=ssled1=ssled2=ssled3=1;
			i=(num%1000)/100;
			datta=~Table[i];
			ssled2=0;
			Delay_ms(1000);
			
			ssled0=ssled1=ssled2=ssled3=1;
			i=num/1000;
			datta=~Table[i];
			ssled3=0;
			Delay_ms(1000);
		
		}
		num++;
		if(num>9999) num=0;
	
	}


}

void beep(unsigned char k)
{
	unsigned int j;
	while(k--)
	{
		for(j=0;j<100;j++)
		{
			speak=!speak;
			Delay_ms(1);
		}
		Delay_ms(200);
	}
}