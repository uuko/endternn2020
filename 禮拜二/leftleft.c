
#include "..\AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80; //P0資料BUS輸出
sfr  Scan=0x90; //P1點矩陣LED掃描輸出
sbit Data1=0x80;
sbit Data2=0x81;
sbit Data3=0x82;
sbit Data4=0x83;
sbit Data5=0x84;
sbit Data6=0x85;
sbit Data7=0x86;
sbit Data8=0x87;
#include "fuck.h"  //字型A資料檔
main() 
{ 
	char temp;
  unsigned char scan=0x80;//定義掃瞄變數
  unsigned char i;       //定義陣列資料計數
  unsigned char repeat;  //定義重覆掃描次數	
  unsigned char shift;   //定義移位計數  
 while(1)
 {
   for(shift=7;shift>0;shift--) //移位計數=7~0
    {
    for(repeat=0;repeat<10;repeat++)//重覆掃瞄次數
     {
      for(i=0;i<8;i++)   //讀取8筆資料掃瞄8次
       {
        Data=fuck[i]; //讀取陣列資料輸出

temp=Data8;
Data8=Data1;
Data1=temp;
temp=Data7;
Data7=Data2;
Data2=temp;
temp=Data6;
Data6=Data3;
Data3=temp;
temp=Data5;
Data5=Data4;
Data4=temp;

         Delay_ms(1);    //延時
		 Data=0xff;      //全暗
         scan=RR8(scan); //換掃瞄下一行
		 Scan=~(scan<<shift); //掃瞄右移後輸出
       }
     } 
    }
  //----------------------------------------------   
   for(shift=0;shift<7;shift++)	 //移位計數=0~7
    {
     for(repeat=0;repeat<10;repeat++)//重覆掃瞄次數
     {										   
      for(i=0;i<8;i++)   //讀取8筆資料掃瞄8次
       {
         Data=fuck[i];   //讀取陣列資料輸出
				 temp=Data8;
Data8=Data1;
Data1=temp;
temp=Data7;
Data7=Data2;
Data2=temp;
temp=Data6;
Data6=Data3;
Data3=temp;
temp=Data5;
Data5=Data4;
Data4=temp;
         Delay_ms(1);    //延時
		 Data=0xff;      //全暗
         scan=RR8(scan); //換掃瞄下一行
		 Scan=~(scan>>shift);//掃瞄左移後輸出
       }
     }    
    }      			  
  } 
}