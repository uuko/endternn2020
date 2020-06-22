#include "AT89X52.H"
sfr LED=0x80;
void Delay(unsigned char count);
main(){
	TMOD=0x10;
	TR1=1;
	LED=0;
	while(1){
		LED++;
		Delay(20);
	}
}
//0.05s
void Delay(unsigned char count){
	while(count --) {
		TL1=(65536-46080) % 256;
	TH1=(65536-46080) /256;
	while(TF1==0);
	TF1=0;
	
	}

}