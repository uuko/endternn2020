
#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit SSLED0=0x90; //P10�C�q��ܾ��Ӧ�ƿ�ܿ�X
sbit SSLED1=0x91; //P11�C�q��ܾ��Q��ƿ�ܿ�X
sbit SSLED2=0x92; //P12�C�q��ܾ��ʦ�ƿ�ܿ�X
sbit SSLED3=0x93; //P13�C�q��ܾ��d��ƿ�ܿ�X

code unsigned char Table[] //�C�q��ܾ�0~9�ƽX���
={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

char hor=23,min=59,sec=52; //�]�w�ɡB���B��ɶ�
void Display(char scan); //�C�q��ܾ���ܮɶ���
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
void T0_int(void) interrupt 1  //Timer0���_���
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
void Display(char scan) //�|��ƤC�q��ܾ���ܨB��	 
{  
  while(scan--) //���б��y���� 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
	 Data=~Table[sec%10];//Ū����Ӧ�ƼƽX��ƿ�X
     SSLED0=0;      //��ܭӦ����ܾ�
     Delay_ms(1);   //���y����  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S          
     Data=~Table[sec/10];//Ū����Q��ƼƽX��ƿ�X
     SSLED1=0;      //��ܤQ�����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S                     
     Data=~Table[min%10];//Ū�����ӼƼƽX��ƿ�X
     SSLED2=0;      //��ܦʦ����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
     Data=~Table[min/10];//Ū�����Q��ƼƽX��ƿ�X
     SSLED3=0;      //��ܤd�����ܾ�
     Delay_ms(1);   //���y����
   }	   
}