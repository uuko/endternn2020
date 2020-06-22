#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit SSLED0=0x90; //P10�C�q��ܾ��Ӧ�ƿ�ܿ�X
sbit SSLED1=0x91; //P11�C�q��ܾ��Q��ƿ�ܿ�X
sbit SSLED2=0x92; //P12�C�q��ܾ��ʦ�ƿ�ܿ�X
sbit SSLED3=0x93; //P13�C�q��ܾ��d��ƿ�ܿ�X

char hor=23,min=59,sec=1; //�]�w�ɡB���B��ɶ�
sbit   KEY=P3^2; //����}����P32��J
sbit   SPEAK=P2^6; //P26��z��X
void beep(unsigned char i); 

 unsigned char code Table[] //0~F�ƽX���
  ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
 main() 
{
  unsigned char scan;      //���y����  
  unsigned int Num=2359; //�p�ƤQ�i���� 
  unsigned char i;    //�^���p�ƪ��ӡB�Q�B�ʡB�d��� 

   while(1)     //���а���
    {
     for(scan=0;scan<250;scan++) //���б��y���� 
      {
				 while(KEY==0)
				 {
					beep(2);
				 }
       SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
			 i=hor % 10;   //���X�Ӧ��
       Data=~Table[i]; //Ū���Ӧ�ƽX��ƿ�X
       SSLED2=0;        //��ܭӦ����ܾ�
       Delay_ms(1);    //���y����  
       
    SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S           
       i=(hor % 100)/10; //���X�Q��� 
       Data=~Table[i];//Ū���Q��ƽX��ƿ�X
       SSLED3=0;       //��ܤQ�����ܾ�
       Delay_ms(1);   //���y����
                            
       SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
    i=min % 10; //���X�ʦ��
       Data=~Table[i]; //Ū���ʦ�ƽX��ƿ�X
        SSLED0=0;       //��ܦʦ����ܾ�
       Delay_ms(1);    //���y����
       
    SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
       i=(min % 100)/10;  //���X�d���
       Data=~Table[i]; //Ū���d��ƽX��ƿ�X
       SSLED1=0;        //��ܤd�����ܾ�
       Delay_ms(1);    //���y����
     }    
  
   sec++;                       // ��[�@
   if (sec < 60) continue;    // �Y��p��60��loop�B   
   sec=0; min++;               // ����60�h�O��=0�A���[�@
   if (min < 60) continue;    // �Y���p��60��loop�B   
   min=0; hor++;               // �Y������60�h�O��=0�A�ɥ[�@
   if (hor <24) continue;     // �Y�ɤp��24��loop�B
   hor=0;min=0; sec=0; continue;// �Y�ɵ���24�h�O�ɡB���B��=0
   while(KEY==0)
   {
    beep(2);
   }
   } 
}
void beep(unsigned char i)
{
  unsigned int  j;//SPEAK�Ϭۦ���
  while(i--)   //���n����
   {
     for(j=0;j<400;j++) //�O��X�Ϭ�400��
      {
        SPEAK=!SPEAK; //SPEAK�Ϭ�,�O��z�o�X�n��
        Delay_ms(5);  //���n���W(100HZ)
      }
     Delay_ms(200);  //���n�����j�ɶ�
  }
}