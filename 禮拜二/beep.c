#include "..\AT89X52.H"
sfr led=0x80;
sbit   KEY=P3^2;
sbit   SPEAK=P2^6;
char i=1;
char flag=0xFF;
void beep(unsigned char i);
void main(){
	
	EA=1;
	EX0=1;IT0=1;
	PX1=1;
	EX1=1;IT1=1;
	led=0x01;
	while(1){
		Delay_ms(200);
	}
} 
void EX0_int(void) interrupt 0{
		led++;
		beep(1);
		while(led>=5){
			led=0x00;
			Delay_ms(500);
			led=0xff;
			Delay_ms(500);
		}
}

void EX1_int(void) interrupt 2{
	
	led=0x01;
}
void beep(unsigned char i)
{
  unsigned int  j;//SPEAK�Ϭۦ���
  while(i--)   //���n����
   {
     for(j=0;j<400;j++) //�O��X�Ϭ�400��
      {
        SPEAK=!SPEAK; //SPEAK�Ϭ�,�O��z�o�X�n��
        Delay_ms(1);  //���n���W(100HZ)
      }
     
  }
}