#include "AT89X52.H"
void beep(unsigned char i);
sbit speak=0xA6;
void main(){
		while(1){
			beep(3);
			Delay_ms(100000);
			beep(1);
		}
	
}
void beep(unsigned char i){
	unsigned int j;
	while(i){
		for(j=0;j<400;j++){
			speak=!speak;
			Delay_ms(1);
		}
		i--;
		Delay_ms(200);
	}
}