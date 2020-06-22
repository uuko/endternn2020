
#include "..\AT89X52.H"   
sfr  Data=0x80;
sbit SSLED0=0x90; 
sbit SSLED1=0x91; 
sbit SSLED2=0x92; 
sbit SSLED3=0x93; 
unsigned char scount;
unsigned char  hor=23,min=59,sec=58;//�]�w�ɡB���B����
unsigned char code Table[] 
	={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
char code mes[]="2020\00006\00116\002";
char code day[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, 
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, 
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};
unsigned char i;  
unsigned char scan;  //���y����
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
                 //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
void showClock();
main() 
{
	EA=1;IT0=0;EX0=1;
  EX1=1;IT1=1;
 	scan=10;
  LCD_init();    //���m�βM��LCD  
  LCD_Cmd(0x85); //��ХѲĤ@���5�Ӧr�}�l���  
  for(i=0x0;i<=23;i++) //�g�J�~���r�� 
  {
     LCD_Cmd(0x40+i);    //���wCGRAM��}  
     LCD_Data(day[i]); //�g�JCGRAM���  
  } 
  LCD_Cmd(0x80);		 //���w�Ĥ@�����		
  for(i=0;i<11;i++) LCD_Data(mes[i]);//��ܦ~���
  while(1)     //���а���
	{
		for(scan=0;scan<50;scan++) //���б��y���� 
		{
			 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
			 Data=~Table[0];//Ū���Ӧ�ƽX��ƿ�X
			 SSLED0=0;       //��ܭӦ����ܾ�
			 Delay_ms(1);   //���y����  
				
			 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S          
			 Data=~Table[4];//Ū���Q��ƽX��ƿ�X
			 SSLED1=0;       //��ܤQ�����ܾ�
			 Delay_ms(1);   //���y����
				
			 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S                     
			 Data=~Table[1];//Ū���ʦ�ƽX��ƿ�X
			 SSLED2=0;       //��ܦʦ����ܾ�
			 Delay_ms(1);   //���y����
			 
			 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
			 Data=~Table[10];//Ū���d��ƽX��ƿ�X
			 SSLED3=0;       //��ܤd�����ܾ�
			 Delay_ms(1);   //���y����
		}	   
		while((sec==0)&&(hor==0)&&(min==0)){		
				showClock();
				TMOD = 0x01; /*0000 0001�A�]�wTimer0��mode1�����p��
                  bit3:GATE=0,���ϥΥ~��INT0���}
			      bit2:C/T0=0,�����p�� 
			      bit1-0:MODE=01,�ϥμҦ�1�u�@*/
				 TL0=65536-10; TH0=(65536-10)>>8; //�]�wTimer0�p�ƭ�
				 P0=0;          //P0��X0
				 EA=1;ET0=1;    //�P��Timer0���_
				 TR0=1;         //�Ұ�Timer0�}�l�p��
		}	
		LCD_Cmd(0xC5); //��ХѲĤG���5�Ӧr�}�l���  
		LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
			    
    if (sec < 60) continue; //�Y��p��60�������   
    sec=0; min++;       //����60�h�O��=0�A���[�@
    if (min < 60) continue; //�Y���p��60�������   
    min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
    if (hor <24)  continue; //�Y�ɤp��24�������
    hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0 
			
   } 
}
void showClock(){
	
		LCD_Cmd(0xC5); //��ХѲĤG���5�Ӧr�}�l���  
		LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���

}
void T0_int(void) interrupt 1  //Timer0���_���
{
    TL0=(65536-46080)%256; TH0=(65536-46080)/256; //���s�]�wTimer0�p�ƭ�
    //P0++;    //P0���[��X
		scount++;
		if(scount==20)
		{
			scount=0;
	    sec++;          //��[�@
			if (sec == 60) { //�Y��p��60��loop�B   
				sec=0; min++;        //����60�h�O��=0�A���[�@
				if (min == 60) { //�Y���p��60��loop�B   
					min=0; hor++;        //�Y������60�h�O��=0�A�ɥ[�@
					if (hor ==24) { //�Y�ɤp��24��loop�B
						hor=0;min=0; sec=0; //�Y�ɵ���24�h�O�ɡB���B��=0
					}
				}
			}
		}
}
void EX1_int(void) interrupt 2 {
	 TR0=!TR0;   
	 if(hor==23){
		LCD_Cmd(0xC5); //��ХѲĤG���5�Ӧr�}�l���  
		sec++;      
		Delay_ms(50);
		if(sec>59){
			sec=0;min++;
			if(min>59){
				hor++;min=0;
				if(hor>23){
					hor=0;min=0;sec=0;
				}
			}
		}
	}
}
/***********************************************************
*��ƦW��: LCD_Data
*�\��y�z: �ǰe��ƨ��r��LCD
*��J�ѼơGdat
************************************************************/
void LCD_Data(char dat)  //�ǰe��ƨ�LCD
{
    Data=dat; //��ưe��BUS
    RS=1;EN=1;//��Ƽg�J��LCD��
    Delay_ms(1);   //LCD���ݼg�J����
    EN=0;          //�T��LCD    
}
/***************************************************************
*��ƦW��: LCD_Cmd
*�\��y�z: �ǰe�R�O���r��LCD
*��J�ѼơGCmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //�ǰe�R�O��LCD
{
    Data=Cmd;  //�R�O�e��BUS
    RS=0;EN=1; //�R�O�g�J��LCD��
    Delay_ms(1);    //LCD���ݼg�J����     
    EN=0;           //�T��LCD
}
/***************************************************************
*��ƦW��: LCD_init
*�\��y�z: �ҩl�Ƥ�r��LCD
*****************************************************************/
void LCD_init(void)    //LCD���ҩl�{��  
{
    LCD_Cmd(0x38);/*0011 1000,8bit�ǿ�,���2��,5*7�r��
                    bit4:DL=1,8bit�ǿ�,
                    bit3:N=1,���2��
                    bit2:F=0,5*7�r��*/    
    LCD_Cmd(0x0c);/*0000 1100,��ܹ�ON,����ܴ��,��Ф��{�{
                    bit2:D=1,��ܹ�ON
                    bit1:C=0,����ܴ��
	                bit0:B=0,��Ф��{�{*/
    LCD_Cmd(0x06);/*0000 0110,//��ܧ���Хk��,��в���T�� 
                    bit1:I/D=1,��ܧ���Хk��,
                    bit0:S=0,��в���T��*/  
    LCD_Cmd(0x01); //�M����ܹ�  
    LCD_Cmd(0x02); //��Ц^���  
}

void EX0_int(void) interrupt 0 {
	
	
     for(scan=0;scan<10;scan++) //���б��y���� 
      {
       SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
			
       Data=~(Table[0]|0x80);//Ū���Ӧ�ƽX��ƿ�X
       SSLED0=0;       //��ܭӦ����ܾ�
       Delay_ms(1);   //���y����  
       
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S          

       Data=~(Table[4]|0x80);//Ū���Q��ƽX��ƿ�X
       SSLED1=0;       //��ܤQ�����ܾ�
       Delay_ms(1);   //���y����
       
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S                     

       Data=~(Table[1]|0x80);//Ū���ʦ�ƽX��ƿ�X
       SSLED2=0;       //��ܦʦ����ܾ�
       Delay_ms(1);   //���y����
       
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
       Data=~(Table[10]|0x80);//Ū���d��ƽX��ƿ�X
       SSLED3=0;       //��ܤd�����ܾ�
       Delay_ms(1);   //���y����
     }	   
}

