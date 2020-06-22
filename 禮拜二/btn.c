#include "AT89X52.H"
sbit key=0xB2;
sbit speak=0xA6;
void main(){
  unsigned char dly=1;
	while(1){
		speak=!speak;
		Delay_ms(dly);
		if(key=0)dly++;
	}

}