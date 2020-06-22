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
TMOD=0x10; /*0000 0000 �]�wTimer0��mode0�����p��
bit3:GATE=0,���ϥ�INT0�}����
bit2:C/T=0,�����p��
bit1-0:MODE=00�A�Ҧ�0 */
TR1=1; //�Ұ�Timer0
EA=1;
ET1=1;
P0=0;
while(1)
{
}
}
void Delay(void) interrupt 3 //5000uS���ɨ��
{
TL1= (65536-46080) % 256; //11.0592MHZ 1��
TH1= (65536-46080) / 256; //�N��8-bit�p�ƭȦs�JTH0
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
void display(unsigned char scan) //���ﾹ�Ƶ{���bP3.2���U�ɭp�ƾ��@�˥[�@
{
while(scan--)
{
SSLED0=SSLED1=SSLED2=SSLED3=1; //�N�C�q��ܾ���������
i=sec % 10; //��X�Ӧ��
Data=~Table[i]; //��Ӧ�ƹ������C�q��ܾ��}�C��DATA
SSLED0=0; //��Ĥ@�ӤC�q��ܾ�(�Ӧ��)���}
Delay_ms(1); //����1ms
SSLED0=SSLED1=SSLED2=SSLED3=1;
i=(sec% 100)/10; //��X�Q���
Data=~Table[i]; //��Q��ƹ������C�q��ܾ��}�C��DATA
SSLED1=0; //��ĤG�ӤC�q��ܾ�(�Q���)���}
Delay_ms(1);
SSLED0=SSLED1=SSLED2=SSLED3=1; //�N�C�q��ܾ���������
i=min % 10; //��X�Ӧ��
Data=~Table[i]; //��Ӧ�ƹ������C�q��ܾ��}�C��DATA
SSLED2=0; //��Ĥ@�ӤC�q��ܾ�(�Ӧ��)���}
Delay_ms(1); //����1ms
SSLED0=SSLED1=SSLED2=SSLED3=1;
i=(min% 100)/10; //��X�Q���
Data=~Table[i]; //��Q��ƹ������C�q��ܾ��}�C��DATA
SSLED3=0; //��ĤG�ӤC�q��ܾ�(�Q���)���}
Delay_ms(1);
}
}