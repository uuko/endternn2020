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
	

	
	/*while(KEY==0){
		if(i<5){
			i++;
			led=i;
		}
		else{
			led=flag;
			flag=!flag;
		}
		
		beep(1);
	}*/

} 
void EX0_int(void) interrupt 0{	
		while(i>=5){
				led=0xFF;
				Delay_ms(500);
				led=0x00;
				Delay_ms(500);			
		}
			i++;
			led=i;
			beep(1);
	
}

void EX1_int(void) interrupt 2{
	led=0x01;
	if(i==5){i=0;}

}
void beep(unsigned char i)
{
  unsigned int  j;//SPEAK反相次數
  while(i--)   //嗶聲次數
   {
     for(j=0;j<400;j++) //令輸出反相400次
      {
        SPEAK=!SPEAK; //SPEAK反相,令喇叭發出聲音
        Delay_ms(1);  //嗶聲音頻(100HZ)
      }
     
  }
}