//************* LCD3.c *********************
//*�ʧ@�G�bLCD���24�p�ɹq�l�����ܤ�
//*******************************************
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
sbit   KEY=P3^2;
sbit   SPEAK=P2^6;
char i;
char hor,min,sec;
void showClock();
void showDate();
char code mes[]="2007\00007\00115\002";//2007�~07��15��
char code Table[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, //�~
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, //��
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};//��
void beep(unsigned char i); 
bit varSetup=1;
main()
{
	
	 char check=0;
   hor=23,min=59,sec=58;//�]�w�ɡB���B����
   LCD_init();           //���m�βM��LCD   
		showDate();
	 showClock();
	 EA=1;EX0=1;IT0=1;IT1=1;PX1=1;
	 while(varSetup==1){
			if((hor==0)&&(min==0)&&(sec==0))varSetup=0;
	 }
	/*while((hor!=0)||(min!=0)||(sec!=0)){
			if(KEY==0)
			{				
				sec++;
				showClock();
				beep(1);
				if (sec < 60) continue; //�Y��p��60�������   
					sec=0; min++;       //����60�h�O��=0�A���[�@
				if (min < 60) continue; //�Y���p��60�������   
					min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
				if (hor <24)  continue; //�Y�ɤp��24�������
					hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0
			
			}
	 }*/
	
   while(1)
   {
		showClock();
    
		Delay_ms(1000);
	
		sec++;              //��[�@
	  if (sec < 60) continue; //�Y��p��60�������   
		sec=0; min++;       //����60�h�O��=0�A���[�@
		if (min < 60) continue; //�Y���p��60�������   
		min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
		if (hor <24)  continue; //�Y�ɤp��24�������
		hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0 
		
		
  
   }
}
void showDate(){
	/*for(i=0x0;i<=0x3f;i++){
		LCD_Cmd(0x40+i);
		LCD_Data(Table[i]);
	}*/
	LCD_Cmd(0x80);
	for(i=0;i<11;i++)LCD_Data(mes[i]);
}

void EX0_int(void) interrupt 0{
	sec++;
	
	beep(1);
	if (sec > 59){  sec=0; min++; }    //����60�h�O��=0�A���[�@
	if (min > 59){  	min=0; hor++;}       //�Y������60�h�O��=0�A�ɥ[�@
	if (hor > 23){  hor=0;min=0; sec=0;}//�Y�ɵ���24�h�O�ɡB���B��=0
showClock();
}
void showClock(){
					LCD_Cmd(0xC5);        //�ѲĤ@��}�l��� 
					LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
					LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
					LCD_Data(':');
					
					LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
					LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
					LCD_Data(':');
					
					LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
					LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
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
