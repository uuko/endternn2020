#include "AT89X52.H" //�Ȧs���βպA�w�q
sfr Data=0x80; //P0���BUS��X
sbit Data1=0x80;
sbit Data2=0x81;
sbit Data3=0x82;
sbit Data4=0x83;
sbit Data5=0x84;
sbit Data6=0x85;
sbit Data7=0x86;
sbit Data8=0x87;
sfr Scan=0x90; //P1�I�x�}LED���y��X
#include "fuck.h" //�r�������
main()
{
char i; //�w�q�}�C��ƭp��
char temp;
Scan=0x7F; //��com1�}�l���˿�X
while(1)
{
for(i=0;i<8;i++) //Ū��8����Ʊ���8��
{
Data=fuck[i]; //Ū���}�C��ƿ�X

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

Delay_ms(1); //����
Data=0xFF; //���t
Scan=RR8(Scan); //�����ˤU�@��
}
}
}