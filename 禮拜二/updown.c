/***** DOT7.c ****�I�x�}��ܾ���î�U�Ԧr��**************
*�ʧ@�G��ܥ�î�U����r��
*���u�GScan�C�q�챽�y��X�A��Data�C�q���X���
**********************************************************/
#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80; //P0���BUS��X
sfr  Scan=0x90; //P1�I�x�}LED���y��X
#include "font.h"  //�r��A�����
main() 
{ 
  unsigned char i;      //�w�q�}�C��ƭp��
  unsigned char repeat; //�w�q���б��y����		 
  unsigned char mask;   //�w�q�B����� 

  Scan=0x7F;   //��com1�}�l����   
  while(1)
  {
    mask=0xFF;   //�����B��
    for(repeat=0;repeat<20;repeat++) //���б��˦���
     {
       for(i=0;i<8;i++)  //Ū��8����Ʊ���8��
       {
        Data=font[i] | mask;//Ū���}�C��ơA�þB����X
        Delay_ms(30);   //����
        Data=0xff;     //���t
	    Scan=RR8(Scan);//�����ˤU�@��
       }
     mask=mask << 1;//��֭n�B������
    }
		  mask=0x7F; 
		  for(repeat=0;repeat<20;repeat++) //���б��˦���
     {
       for(i=0;i<8;i++)  //Ū��8����Ʊ���8��
       {
        Data=font[i] | mask;//Ū���}�C��ơA�þB����X
        Delay_ms(30);   //����
        Data=0xff;     //���t
				Scan=RR8(Scan);//�����ˤU�@��
				 }
			 mask=mask >> 1;//��֭n�B������
    }
  } 
}