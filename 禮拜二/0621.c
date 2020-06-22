#include "AT89X52.H"
sfr Data=0x80;
sbit ssled0=0x90;
sbit ssled1=0x91;
sbit ssled2=0x92;
sbit ssled3=0x93;
sbit RS=0x96;sbit EN=0x97;
unsigned char i;
unsigned char scan;
char code mes[]="2020\00006\00121\002";
char code day[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, 
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, 
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};
unsigned char code Table[]={0x3f,0x06,0x66,0x77};
unsigned char hor=23,min=59,sec=52;
unsigned char scount =0;
void showClock();
main(){


	EA=1;IT0=0;EX0=1;EX1=1;IT1=1;
	LCD_init();
	for(i=0x0;i<=0x3f;i++)  
  {
     LCD_Cmd(0x40+i);      
     LCD_Data(day[i]);   
  } 
	LCD_Cmd(0x85);
	for(i=0;i<11;i++){
		LCD_Data(mes[i]);
	}
	while(1){
		
		for(scan=0;scan<20;scan++){
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~Table[0];
			ssled0=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~Table[2];
			ssled1=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~Table[1];
			ssled2=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~Table[3];
			ssled3=0;
			Delay_ms(1);
		}
		while((sec==0)&&(min==0)&&(hor==0)){
				showClock();
				 TMOD = 0x01; 
				 TL0=65536-10; TH0=(65536-10)>>8; 
				 EA=1;ET0=1;    
				 TR0=1;         	  
		}
		showClock();
		
	}
}
void EX1_int(void) interrupt 2{
		Delay_ms(400);
	TR0=!TR0;
	if(hor==23){
		sec++;
		if(sec>59){
				sec=0;min++;
				if(min>59){
					min=0;hor++;
					if(hor>23){
						hor=0;sec=0;min=0;
					}
				}
			}
	
	}
	

}
void EX0_int (void) interrupt 0 {
	for(scan=0;scan<100;scan++){
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~(Table[0]|0x80);
			ssled0=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~(Table[2]|0x80);
			ssled1=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~(Table[1]|0x80);
			ssled2=0;
			Delay_ms(1);
			
			ssled0=ssled1=ssled2=ssled3=1;
			Data=~(Table[3]|0x80);
			ssled3=0;
			Delay_ms(1);
		}
}
void showClock(){
	LCD_Cmd(0xC0);
	LCD_Data(hor/10+'0');
	LCD_Data(hor%10+'0');
	LCD_Data(':');
	
	LCD_Data(min/10+'0');
	LCD_Data(min%10+'0');
	LCD_Data(':');
	
	LCD_Data(sec/10+'0');
	LCD_Data(sec%10+'0');
}
void T0_int(void) interrupt 1{
	TL0=65536-46080;
	TH0=(65536-46080)>>8;
	scount++;
	if(scount==20){
		scount=0;
		sec++;
		if(sec>59){
			sec=0;min++;
			if(min>59){
				min=0;hor++;
				if(hor>23){
					hor=0;sec=0;min=0;
				}
			}
		}
	}
}
	
void LCD_Data(char dat){
	Data=dat;
	RS=1;EN=1;
	Delay_ms(1);
	EN=0;
}
void LCD_Cmd(unsigned char Cmd){
	Data=Cmd;
	RS=0;EN=1;
	Delay_ms(1);
	EN=0;
}
void LCD_init(void){
	LCD_Cmd(0x38);
	LCD_Cmd(0x0c);
	LCD_Cmd(0x06);
	LCD_Cmd(0x01);
	LCD_Cmd(0x02);
}