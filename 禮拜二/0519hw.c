#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80; //P0���BUS��X
sfr  Scan=0x90; //P1�I�x�}LED���y��X
#include "A001.h"  //�r��A�����
main() 
{ 
  unsigned char scan=0x80;//�w�q�����ܼ�
  unsigned char i;       //�w�q�}�C��ƭp��
  unsigned char repeat;  //�w�q���б��y����	
  unsigned char shift;   //�w�q����p��  
 while(1)
 {
   for(shift=7;shift>0;shift--) //����p��=7~0
    {
    for(repeat=0;repeat<10;repeat++)//���б��˦���
     {
      for(i=0;i<8;i++)   //Ū��8����Ʊ���8��
       {
				  Scan=~(scan<<shift); //���˥k�����X ��o�~�O�諸
         Data=A001[i];   //Ū���}�C��ƿ�X
         Delay_ms(1);    //����
		 Data=0xff;      //���t
         scan=RR8(scan); //�����ˤU�@��
		
       }
     } 
	 }
		 for(shift=0;shift<7;shift++)	 //����p��=0~7
    {
     for(repeat=0;repeat<10;repeat++)//���б��˦���
     {										   
      for(i=0;i<8;i++)   //Ū��8����Ʊ���8��
       {
         Data=A001[i];   //Ū���}�C��ƿ�X
         Delay_ms(1);    //����
		 Data=0xff;      //���t
         scan=RR8(scan); //�����ˤU�@��
		 Scan=~(scan>>shift);//���˥������X
       }
     }    
    }   
		
		 for(shift=0;shift<7;shift++)	 //����p��=0~7
    {
     for(repeat=0;repeat<10;repeat++)//���б��˦���
     {										   
      for(i=0;i<8;i++)   //Ū��8����Ʊ���8��
       {
         Data=A001[i];   //Ū���}�C��ƿ�X
         Delay_ms(1);    //����
		 Data=0xff;      //���t
         scan=RR8(scan); //�����ˤU�@��
		 Scan=~(scan<<shift);//���˥������X
       }
     }    
    }
		
		for(shift=0;shift<7;shift++)	 //����p��=0~7
    {
     for(repeat=0;repeat<10;repeat++)//���б��˦���
     {										   
      for(i=0;i<8;i++)   //Ū��8����Ʊ���8��
       {
         Data=A001[i];   //Ū���}�C��ƿ�X
         Delay_ms(1);    //����
		 Data=0xff;      //���t
         scan=RR8(scan); //�����ˤU�@��
		 Scan=~(scan<<shift);//���˥������X
       }
     }    
    }
}
	}