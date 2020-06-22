#include "AT89X52.H" //暫存器及組態定義
sfr Data=0x80; //P0資料BUS輸出
sbit Data1=0x80;
sbit Data2=0x81;
sbit Data3=0x82;
sbit Data4=0x83;
sbit Data5=0x84;
sbit Data6=0x85;
sbit Data7=0x86;
sbit Data8=0x87;
sfr Scan=0x90; //P1點矩陣LED掃描輸出
#include "fuck.h" //字型資料檔
main()
{
char i; //定義陣列資料計數
char temp;
Scan=0x7F; //由com1開始掃瞄輸出
while(1)
{
for(i=0;i<8;i++) //讀取8筆資料掃瞄8次
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

Delay_ms(1); //延時
Data=0xFF; //全暗
Scan=RR8(Scan); //換掃瞄下一行
}
}
}