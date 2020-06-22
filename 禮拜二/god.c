#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X

sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD

sbit SSLED0=0x90; //P10�C�q��ܾ��Ӧ�ƿ�ܿ�X
sbit SSLED1=0x91; //P11�C�q��ܾ��Q��ƿ�ܿ�X
sbit SSLED2=0x92; //P12�C�q��ܾ��ʦ�ƿ�ܿ�X
sbit SSLED3=0x93; //P13�C�q��ܾ��d��ƿ�ܿ�X

code unsigned char Table[] //�C�q��ܾ�0~9�ƽX���
={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77};
sbit KEY=P3^3; //����}����P32��J
char word1=0,word2=4,word3=1,word4=10; //�]�w
void Display(char scan); //�C�q��ܾ����
void Display2(char scan); //�C�q��ܾ����

char code mes[]="2020\00006\00116\002";//2020�~06��16��
char code Table2[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, //�~
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, //��
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};//��
char  scan=50;
char hor=23,min=59,sec=58;//�]�w�ɡB���B����
char i;		 //�}�C��ƭp��
 unsigned char scount=0;
void LCD_Display();

main()
{
	EA=1;          //�P����餤�_
  EX0=1; EX1=1; //�P��~��INT0���_��INT1���_
  IT0=0; IT1=1; //�]�wINT0�}�Ǧ�Ĳ�o���_��INT1�}�t�tĲ�o���_
  //PX1=1;        //�]�wINT1���_�u��
	//PT0=1;        //�]�wTimer0���_�u��
	
	TMOD = 0x01; /*0000 0001�A�]�wTimer0��mode1�����p��
                  bit3:GATE=0,���ϥΥ~��INT0���}
			      bit2:C/T0=0,�����p�� 
			      bit1-0:MODE=01,�ϥμҦ�1�u�@*/
   TL0=65536-10; TH0=(65536-10)>>8; //�]�wTimer0�p�ƭ�
   P0=0;          //P0��X0
   EA=1;ET0=1;    //�P��Timer0���_
   TR0=1;         //�Ұ�Timer0�}�l�p��
	
	LCD_init();   //���m�βM��LCD
		for(i=0x0;i<=23;i++) //�g�J�~���r�� 
		 {
			 LCD_Cmd(0x40+i);    //���wCGRAM��}  
			 LCD_Data(Table2[i]); //�g�JCGRAM���  
		 } 
		LCD_Cmd(0x82);		 //���w�Ĥ@�����		
		for(i=0;i<11;i++) LCD_Data(mes[i]);//��ܦ~���
		
		while(1)
   {
		Display(scan);
		 LCD_Display();
		 /*
    LCD_Cmd(0xC4);        //�ѲĤ@��}�l��� 
    LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
		 */
    /*
		if(hor!=23)
		{
			Delay_ms(1000);
			sec++;              //��[�@
			if (sec < 60) continue; //�Y��p��60�������   
			sec=0; min++;       //����60�h�O��=0�A���[�@
			if (min < 60) continue; //�Y���p��60�������   
			min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
			if (hor <24)  continue; //�Y�ɤp��24�������
			hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0 
		}
		else
		{
			if(KEY==0)
			{
				
				sec++;              //��[�@
				Delay_ms(200);
				if (sec < 60) continue; //�Y��p��60�������   
				sec=0; min++;       //����60�h�O��=0�A���[�@
				if (min < 60) continue; //�Y���p��60�������   
				min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
				if (hor <24)  continue; //�Y�ɤp��24�������
				hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0 
			}
		}*/
		}
   
	
	 //��1�p�D����
	while(1){
		Display(scan);
		/*
		while(KEY==0)
		{
			Display2(scan);
		}
		*/
	}
	
}
/*********************************************/
void EX0_int(void) interrupt 0   //INT0���_���0
{
	Display2(scan);
}
/*********************************************/
void EX1_int(void) interrupt 2   //INT1���_���2
{
	if(hor==23){
			sec++;               //��[�@
			if (sec == 60) { //�Y��p��60��loop�B   
				sec=0; min++;        //����60�h�O��=0�A���[�@
				if (min == 60) { //�Y���p��60��loop�B   
					min=0; hor++;        //�Y������60�h�O��=0�A�ɥ[�@
					if (hor == 24) { //�Y�ɤp��24��loop�B
						hor=0;min=0; sec=0; //�Y�ɵ���24�h�O�ɡB���B��=0
						}
				}
			}
		}
	else{
		TR0=!TR0;
	}
}
/************************************************************/
void T0_int(void) interrupt 1  //Timer0���_���
  {
		if(hor!=23){
			TL0=65536-46080; TH0=(65536-46080)>>8; //���s�]�wTimer0�p�ƭ�
			//P0++;    //P0���[��X
			scount++;
			if(scount==20)
			{
				scount=0;
				sec++;               //��[�@
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
		//LCD_Display();
  }
//***************************************************	 
void Display(char scan) //�|��ƤC�q��ܾ���ܨB��	 
{  
  while(scan--) //���б��y���� 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
	 Data=~Table[word1];//Ū����Ӧ�ƼƽX��ƿ�X
     SSLED0=0;      //��ܭӦ����ܾ�
     Delay_ms(1);   //���y����  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S          
     Data=~Table[word2];//Ū����Q��ƼƽX��ƿ�X
     SSLED1=0;      //��ܤQ�����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S                     
     Data=~Table[word3];//Ū�����ӼƼƽX��ƿ�X
     SSLED2=0;      //��ܦʦ����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
     Data=~Table[word4];//Ū�����Q��ƼƽX��ƿ�X
     SSLED3=0;      //��ܤd�����ܾ�
     Delay_ms(1);   //���y����
   }	   
}
//***************************************************	 
void Display2(char scan) //�|��ƤC�q��ܾ���ܨB��	 
{  
  while(scan--) //���б��y���� 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
	 Data=~(Table[word1]|0x80);//Ū����Ӧ�ƼƽX��ƿ�X
     SSLED0=0;      //��ܭӦ����ܾ�
     Delay_ms(1);   //���y����  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S          
     Data=~(Table[word2]|0x80);//Ū����Q��ƼƽX��ƿ�X
     SSLED1=0;      //��ܤQ�����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S                     
     Data=~(Table[word3]|0x80);//Ū�����ӼƼƽX��ƿ�X
     SSLED2=0;      //��ܦʦ����ܾ�
     Delay_ms(1);   //���y����
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
     Data=~(Table[word4]|0x80);//Ū�����Q��ƼƽX��ƿ�X
     SSLED3=0;      //��ܤd�����ܾ�
     Delay_ms(1);   //���y����
   }	   
}
//***********************************************************
void LCD_Display()
{
		LCD_Cmd(0xC4);        //�ѲĤ@��}�l��� 
    LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
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