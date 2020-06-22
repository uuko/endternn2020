#include "AT89X52.H"
sfr Data=0x80;
sbit SSLED0=0x90;
sbit SSLED1=0x91;
sbit SSLED2=0x92;
sbit SSLED3=0x93;
sbit KEY=0xB2;
sbit speak=0xA6;
unsigned char scount,sec,hour,min;
unsigned char i;
unsigned char code Table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void display(unsigned char scan);
void main()
{
sec=01;
min=59;
hour=23;
TMOD=0x10; /*0000 0000 設定Timer0為mode0內部計時
bit3:GATE=0,不使用INT0腳控制
bit2:C/T=0,內部計時
bit1-0:MODE=00，模式0 */
TR1=1; //啟動Timer0
EA=1;
ET1=1;
P0=0;
while(1)
{
}
}
void Delay(void) interrupt 3 //5000uS延時函數
{
TL1= (65536-46080) % 256; //11.0592MHZ 1秒
TH1= (65536-46080) / 256; //將高8-bit計數值存入TH0
display(20);
scount++;
if (scount==12){
scount=0;
sec++;
if(sec==60){
sec=0;
min++;
}
if(min==60){
min=0;
hour++;
}
if(hour==24){
hour=0;
}
}
}
void display(unsigned char scan) //蜂鳴器副程式在P3.2按下時計數器一樣加一
{
while(scan--)
{
SSLED0=SSLED1=SSLED2=SSLED3=1; //將七段顯示器全數關閉
i=sec % 10; //抽出個位數
Data=~Table[i]; //把個位數對應的七段顯示器陣列給DATA
SSLED0=0; //把第一個七段顯示器(個位數)打開
Delay_ms(1); //延遲1ms
SSLED0=SSLED1=SSLED2=SSLED3=1;
i=(sec% 100)/10; //抽出十位數
Data=~Table[i]; //把十位數對應的七段顯示器陣列給DATA
SSLED1=0; //把第二個七段顯示器(十位數)打開
Delay_ms(1);
SSLED0=SSLED1=SSLED2=SSLED3=1; //將七段顯示器全數關閉
i=min % 10; //抽出個位數
Data=~Table[i]; //把個位數對應的七段顯示器陣列給DATA
SSLED2=0; //把第一個七段顯示器(個位數)打開
Delay_ms(1); //延遲1ms
SSLED0=SSLED1=SSLED2=SSLED3=1;
i=(min% 100)/10; //抽出十位數
Data=~Table[i]; //把十位數對應的七段顯示器陣列給DATA
SSLED3=0; //把第二個七段顯示器(十位數)打開
Delay_ms(1);
}
}