//************* LCD3.c *********************
//*動作：在LCD顯示24小時電子鐘的變化
//*******************************************
#include "..\AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD
sbit   KEY=P3^2;
sbit   SPEAK=P2^6;
char i;
char hor,min,sec;
void showClock();
void showDate();
char code mes[]="2007\00007\00115\002";//2007年07月15日
char code Table[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, //年
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, //月
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};//日
void beep(unsigned char i); 
bit varSetup=1;
main()
{
	
	 char check=0;
   hor=23,min=59,sec=58;//設定時、分、秒初值
   LCD_init();           //重置及清除LCD   
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
				if (sec < 60) continue; //若秒小於60重覆顯示   
					sec=0; min++;       //秒等於60則令秒=0，分加一
				if (min < 60) continue; //若分小於60重覆顯示   
					min=0; hor++;       //若分等於60則令分=0，時加一
				if (hor <24)  continue; //若時小於24重覆顯示
					hor=0;min=0; sec=0;//若時等於24則令時、分、秒=0
			
			}
	 }*/
	
   while(1)
   {
		showClock();
    
		Delay_ms(1000);
	
		sec++;              //秒加一
	  if (sec < 60) continue; //若秒小於60重覆顯示   
		sec=0; min++;       //秒等於60則令秒=0，分加一
		if (min < 60) continue; //若分小於60重覆顯示   
		min=0; hor++;       //若分等於60則令分=0，時加一
		if (hor <24)  continue; //若時小於24重覆顯示
		hor=0;min=0; sec=0;//若時等於24則令時、分、秒=0 
		
		
  
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
	if (sec > 59){  sec=0; min++; }    //秒等於60則令秒=0，分加一
	if (min > 59){  	min=0; hor++;}       //若分等於60則令分=0，時加一
	if (hor > 23){  hor=0;min=0; sec=0;}//若時等於24則令時、分、秒=0
showClock();
}
void showClock(){
					LCD_Cmd(0xC5);        //由第一行開始顯示 
					LCD_Data(hor/10+'0'); //時的十位數到LCD顯示
					LCD_Data(hor%10+'0'); //時的個位數到LCD顯示
					LCD_Data(':');
					
					LCD_Data(min/10+'0'); //分的十位數到LCD顯示
					LCD_Data(min%10+'0'); //分的個位數到LCD顯示
					LCD_Data(':');
					
					LCD_Data(sec/10+'0'); //秒的十位數到LCD顯示
					LCD_Data(sec%10+'0'); //秒的個位數到LCD顯示
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
/***********************************************************
*函數名稱: LCD_Data
*功能描述: 傳送資料到文字型LCD
*輸入參數：dat
************************************************************/
void LCD_Data(char dat)  //傳送資料到LCD
{
    Data=dat; //資料送到BUS
    RS=1;EN=1;//資料寫入到LCD內
    Delay_ms(1);   //LCD等待寫入完成
    EN=0;          //禁能LCD    
}
/***************************************************************
*函數名稱: LCD_Cmd
*功能描述: 傳送命令到文字型LCD
*輸入參數：Cmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //傳送命令到LCD
{
    Data=Cmd;  //命令送到BUS
    RS=0;EN=1; //命令寫入到LCD內
    Delay_ms(1);    //LCD等待寫入完成     
    EN=0;           //禁能LCD
}
/***************************************************************
*函數名稱: LCD_init
*功能描述: 啟始化文字型LCD
*****************************************************************/
void LCD_init(void)    //LCD的啟始程式  
{
    LCD_Cmd(0x38);/*0011 1000,8bit傳輸,顯示2行,5*7字型
                    bit4:DL=1,8bit傳輸,
                    bit3:N=1,顯示2行
                    bit2:F=0,5*7字型*/    
    LCD_Cmd(0x0c);/*0000 1100,顯示幕ON,不顯示游標,游標不閃爍
                    bit2:D=1,顯示幕ON
                    bit1:C=0,不顯示游標
	                bit0:B=0,游標不閃爍*/
    LCD_Cmd(0x06);/*0000 0110,//顯示完游標右移,游標移位禁能 
                    bit1:I/D=1,顯示完游標右移,
                    bit0:S=0,游標移位禁能*/  
    LCD_Cmd(0x01); //清除顯示幕  
    LCD_Cmd(0x02); //游標回原位  
}
