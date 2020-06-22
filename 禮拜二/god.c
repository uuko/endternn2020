#include "AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出

sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD

sbit SSLED0=0x90; //P10七段顯示器個位數選擇輸出
sbit SSLED1=0x91; //P11七段顯示器十位數選擇輸出
sbit SSLED2=0x92; //P12七段顯示器百位數選擇輸出
sbit SSLED3=0x93; //P13七段顯示器千位數選擇輸出

code unsigned char Table[] //七段顯示器0~9數碼資料
={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77};
sbit KEY=P3^3; //按鍵開關由P32輸入
char word1=0,word2=4,word3=1,word4=10; //設定
void Display(char scan); //七段顯示器顯示
void Display2(char scan); //七段顯示器顯示

char code mes[]="2020\00006\00116\002";//2020年06月16日
char code Table2[]={
 0x10,0x1f,0x02,0x0f,0x0a,0xff,0x02,0x00, //年
 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x13,0x00, //月
 0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00};//日
char  scan=50;
char hor=23,min=59,sec=58;//設定時、分、秒初值
char i;		 //陣列資料計數
 unsigned char scount=0;
void LCD_Display();

main()
{
	EA=1;          //致能整體中斷
  EX0=1; EX1=1; //致能外部INT0中斷及INT1中斷
  IT0=0; IT1=1; //設定INT0腳準位觸發中斷及INT1腳負緣觸發中斷
  //PX1=1;        //設定INT1中斷優先
	//PT0=1;        //設定Timer0中斷優先
	
	TMOD = 0x01; /*0000 0001，設定Timer0為mode1內部計時
                  bit3:GATE=0,不使用外部INT0接腳
			      bit2:C/T0=0,內部計時 
			      bit1-0:MODE=01,使用模式1工作*/
   TL0=65536-10; TH0=(65536-10)>>8; //設定Timer0計數值
   P0=0;          //P0輸出0
   EA=1;ET0=1;    //致能Timer0中斷
   TR0=1;         //啟動Timer0開始計時
	
	LCD_init();   //重置及清除LCD
		for(i=0x0;i<=23;i++) //寫入年月日字型 
		 {
			 LCD_Cmd(0x40+i);    //指定CGRAM位址  
			 LCD_Data(Table2[i]); //寫入CGRAM資料  
		 } 
		LCD_Cmd(0x82);		 //指定第一行顯示		
		for(i=0;i<11;i++) LCD_Data(mes[i]);//顯示年月日
		
		while(1)
   {
		Display(scan);
		 LCD_Display();
		 /*
    LCD_Cmd(0xC4);        //由第一行開始顯示 
    LCD_Data(hor/10+'0'); //時的十位數到LCD顯示
    LCD_Data(hor%10+'0'); //時的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //分的十位數到LCD顯示
    LCD_Data(min%10+'0'); //分的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //秒的十位數到LCD顯示
    LCD_Data(sec%10+'0'); //秒的個位數到LCD顯示
		 */
    /*
		if(hor!=23)
		{
			Delay_ms(1000);
			sec++;              //秒加一
			if (sec < 60) continue; //若秒小於60重覆顯示   
			sec=0; min++;       //秒等於60則令秒=0，分加一
			if (min < 60) continue; //若分小於60重覆顯示   
			min=0; hor++;       //若分等於60則令分=0，時加一
			if (hor <24)  continue; //若時小於24重覆顯示
			hor=0;min=0; sec=0;//若時等於24則令時、分、秒=0 
		}
		else
		{
			if(KEY==0)
			{
				
				sec++;              //秒加一
				Delay_ms(200);
				if (sec < 60) continue; //若秒小於60重覆顯示   
				sec=0; min++;       //秒等於60則令秒=0，分加一
				if (min < 60) continue; //若分小於60重覆顯示   
				min=0; hor++;       //若分等於60則令分=0，時加一
				if (hor <24)  continue; //若時小於24重覆顯示
				hor=0;min=0; sec=0;//若時等於24則令時、分、秒=0 
			}
		}*/
		}
   
	
	 //第1小題部分
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
void EX0_int(void) interrupt 0   //INT0中斷函數0
{
	Display2(scan);
}
/*********************************************/
void EX1_int(void) interrupt 2   //INT1中斷函數2
{
	if(hor==23){
			sec++;               //秒加一
			if (sec == 60) { //若秒小於60到loop處   
				sec=0; min++;        //秒等於60則令秒=0，分加一
				if (min == 60) { //若分小於60到loop處   
					min=0; hor++;        //若分等於60則令分=0，時加一
					if (hor == 24) { //若時小於24到loop處
						hor=0;min=0; sec=0; //若時等於24則令時、分、秒=0
						}
				}
			}
		}
	else{
		TR0=!TR0;
	}
}
/************************************************************/
void T0_int(void) interrupt 1  //Timer0中斷函數
  {
		if(hor!=23){
			TL0=65536-46080; TH0=(65536-46080)>>8; //重新設定Timer0計數值
			//P0++;    //P0遞加輸出
			scount++;
			if(scount==20)
			{
				scount=0;
				sec++;               //秒加一
				if (sec == 60) { //若秒小於60到loop處   
					sec=0; min++;        //秒等於60則令秒=0，分加一
					if (min == 60) { //若分小於60到loop處   
						min=0; hor++;        //若分等於60則令分=0，時加一
						if (hor ==24) { //若時小於24到loop處
							hor=0;min=0; sec=0; //若時等於24則令時、分、秒=0
							}
					}
				}
			}
		}
		//LCD_Display();
  }
//***************************************************	 
void Display(char scan) //四位數七段顯示器顯示步數	 
{  
  while(scan--) //重覆掃描次數 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
	 Data=~Table[word1];//讀取秒個位數數碼資料輸出
     SSLED0=0;      //選擇個位數顯示器
     Delay_ms(1);   //掃描延時  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒          
     Data=~Table[word2];//讀取秒十位數數碼資料輸出
     SSLED1=0;      //選擇十位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒                     
     Data=~Table[word3];//讀取分個數數碼資料輸出
     SSLED2=0;      //選擇百位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
     Data=~Table[word4];//讀取分十位數數碼資料輸出
     SSLED3=0;      //選擇千位數顯示器
     Delay_ms(1);   //掃描延時
   }	   
}
//***************************************************	 
void Display2(char scan) //四位數七段顯示器顯示步數	 
{  
  while(scan--) //重覆掃描次數 
   {
     SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
	 Data=~(Table[word1]|0x80);//讀取秒個位數數碼資料輸出
     SSLED0=0;      //選擇個位數顯示器
     Delay_ms(1);   //掃描延時  
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒          
     Data=~(Table[word2]|0x80);//讀取秒十位數數碼資料輸出
     SSLED1=0;      //選擇十位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒                     
     Data=~(Table[word3]|0x80);//讀取分個數數碼資料輸出
     SSLED2=0;      //選擇百位數顯示器
     Delay_ms(1);   //掃描延時
       
	 SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
     Data=~(Table[word4]|0x80);//讀取分十位數數碼資料輸出
     SSLED3=0;      //選擇千位數顯示器
     Delay_ms(1);   //掃描延時
   }	   
}
//***********************************************************
void LCD_Display()
{
		LCD_Cmd(0xC4);        //由第一行開始顯示 
    LCD_Data(hor/10+'0'); //時的十位數到LCD顯示
    LCD_Data(hor%10+'0'); //時的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //分的十位數到LCD顯示
    LCD_Data(min%10+'0'); //分的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //秒的十位數到LCD顯示
    LCD_Data(sec%10+'0'); //秒的個位數到LCD顯示
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