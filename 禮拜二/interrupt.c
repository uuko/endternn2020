/********** 5_4.c ******************************
* �ʧ@�GP0���[�W�L6�|�i�J�ٹq�Ҧ��A�������A�b
*    INT0(P32)�}��J�t�tĲ�o�ɡA�|����{�{5����A�~�^�D�{��
************************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
main()    //�D�{��
{
  char i=0; //�w�q�ܼ�=0
  EA=1;      //�P����餤�_
  EX0=1;     //�P��~��INT0�_
  IT0=1;     //�]�wINT0�}���t�tĲ�o��J   
  while(1)   //���_�`��
   {
      for(i=0;i<6;i++)  //�p��0~5
       {
          P0=i;   //�ܼƥ�P0��X
	      Delay_ms(1000);
       }
      //PCON=IDL;  //�i�JIDEL�ٹq�Ҧ��A���ݥ~�����_
     PCON=PD;  //�i�JPower Down�ٹq�Ҧ��A���ݭ��m
   }
}
//*******INT1���_���0�A�ϥμȦs���w1*******
void EX1_int(void) interrupt 0 using 1  
{
  char i=0;        //�w�q�{�{�p���ܼ�
  unsigned int dly;
  for(i=0;i<5;i++) //�{�{�p��0~4
   {
     P0=0x00; for(dly=0;dly<20000;dly++); 
     P0=0xff; for(dly=0;dly<20000;dly++); 
   }
}
