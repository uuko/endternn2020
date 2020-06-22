#include "AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit SSLED0=0x90; //P10七段顯示器個位數選擇輸出
sbit SSLED1=0x91; //P11七段顯示器十位數選擇輸出
sbit SSLED2=0x92; //P12七段顯示器百位數選擇輸出
sbit SSLED3=0x93; //P13七段顯示器千位數選擇輸出

char hor=23,min=59,sec=1; //設定時、分、秒時間
sbit   KEY=P3^2; //按鍵開關由P32輸入
sbit   SPEAK=P2^6; //P26喇叭輸出
void beep(unsigned char i); 

 unsigned char code Table[] //0~F數碼資料
  ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
 main() 
{
  unsigned char scan;      //掃描次數  
  unsigned int Num=2359; //計數十進制初值 
  unsigned char i;    //擷取計數的個、十、百、千位數 

   while(1)     //重覆執行
    {
     for(scan=0;scan<250;scan++) //重覆掃描次數 
      {
				 while(KEY==0)
				 {
					beep(2);
				 }
       SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
			 i=hor % 10;   //取出個位數
       Data=~Table[i]; //讀取個位數碼資料輸出
       SSLED2=0;        //選擇個位數顯示器
       Delay_ms(1);    //掃描延時  
       
    SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒           
       i=(hor % 100)/10; //取出十位數 
       Data=~Table[i];//讀取十位數碼資料輸出
       SSLED3=0;       //選擇十位數顯示器
       Delay_ms(1);   //掃描延時
                            
       SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
    i=min % 10; //取出百位數
       Data=~Table[i]; //讀取百位數碼資料輸出
        SSLED0=0;       //選擇百位數顯示器
       Delay_ms(1);    //掃描延時
       
    SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
       i=(min % 100)/10;  //取出千位數
       Data=~Table[i]; //讀取千位數碼資料輸出
       SSLED1=0;        //選擇千位數顯示器
       Delay_ms(1);    //掃描延時
     }    
  
   sec++;                       // 秒加一
   if (sec < 60) continue;    // 若秒小於60到loop處   
   sec=0; min++;               // 秒等於60則令秒=0，分加一
   if (min < 60) continue;    // 若分小於60到loop處   
   min=0; hor++;               // 若分等於60則令分=0，時加一
   if (hor <24) continue;     // 若時小於24到loop處
   hor=0;min=0; sec=0; continue;// 若時等於24則令時、分、秒=0
   while(KEY==0)
   {
    beep(2);
   }
   } 
}
void beep(unsigned char i)
{
  unsigned int  j;//SPEAK反相次數
  while(i--)   //嗶聲次數
   {
     for(j=0;j<400;j++) //令輸出反相400次
      {
        SPEAK=!SPEAK; //SPEAK反相,令喇叭發出聲音
        Delay_ms(5);  //嗶聲音頻(100HZ)
      }
     Delay_ms(200);  //嗶聲的間隔時間
  }
}