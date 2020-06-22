#include "AT89X52.h"
sfr data1=0x80;
sfr scan=0x90;
#include "font4.h"
main(){
unsigned char i;
unsigned char repeat;
unsigned char start;
scan=0x7f;
	while(1){
		for(start=0;start<24;start++){
			for(repeat=0;repeat<10;repeat++){
				for(i=0;i<8;i++){
					data1=font4[start+i];
					Delay_ms(1);
					data1=0xff;
					scan=RR8(scan);
				
				}
			}		
		}
		for(start=24;start>0;start++){
			for(repeat=0;repeat<10;repeat++){
				for(i=0;i<8;i++){
					data1=font4[start+i];
					Delay_ms(1);
					data1=0xff;
					scan=RR8(scan);
				
				}
			}		
		}
		
		

	
	
	}
}