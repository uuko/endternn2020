
#include "AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit SSLED0=0x90; //P10七段顯示器個位數選擇輸出
sbit SSLED1=0x91; //P11七段顯示器十位數選擇輸出
sbit SSLED2=0x92; //P12七段顯示器百位數選擇輸出
sbit SSLED3=0x93; //P13七段顯示器千位數選擇輸出

code unsigned char Table[] //七段顯示器0~9數碼資料
={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

char hor=23,min=59,sec=52; //設定時、分、秒時間
void Display(char scan); //七段顯示器顯示時間值
unsigned char scount=0;

main()
  {
		char scan=20;
				 TMOD = 0x01; 
				 TL0=65536-10; TH0=(65536-10)>>8; 
				 EA=1;ET0=1;    
				 TR0=1; 
			while(1){
			Display(scan);
			}
				
  }
/************************************************************/
void T0_int(void) interrupt 1  //Timer0中斷函數
  {
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
	
//***************************************************	 
void Display(char scan) //四位數七段顯示器顯示步數	 
{  
  while(scan--) //重覆掃描次數 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
	 Data=~Table[sec%10];//讀取秒個位數數碼資料輸出
     SSLED0=0;      //選擇個位數顯示器
     Delay_ms(1);   //掃描延時  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒          
     Data=~Table[sec/10];//讀取秒十位數數碼資料輸出
     SSLED1=0;      //選擇十位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒                     
     Data=~Table[min%10];//讀取分個數數碼資料輸出
     SSLED2=0;      //選擇百位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
     Data=~Table[min/10];//讀取分十位數數碼資料輸出
     SSLED3=0;      //選擇千位數顯示器
     Delay_ms(1);   //掃描延時
   }	   
}