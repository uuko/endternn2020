#include "AT89X52.H"
sfr Data=0x80;
sbit SSLED0=0x90;
sbit SSLED1=0x91;
sbit SSLED2=0x92;
sbit SSLED3=0x93;
sbit KEY=0xB2;
sbit speak=0xA6;
unsigned int Num =5900;
unsigned char i;
unsigned char code Table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void beep(unsigned char k);
void main()
{
	unsigned char scan;
	while(1)
	{
		for(scan=0;scan<250;scan++)
		{
				while(KEY==0) //����KEY(P3.2)�O�_�Q���U
			 {
					beep(1); //�i�J���ﾹ�Ƶ{��
					scan=0; //�NSCAN�k�s�T�O��ƫ�p���I����
			 }
				SSLED0=SSLED1=SSLED2=SSLED3=1; //�N�C�q��ܾ���������
				i=Num % 10; //��X�Ӧ��
				Data=~Table[i]; //��Ӧ�ƹ������C�q��ܾ��}�C��DATA
				SSLED0=0; //��Ĥ@�ӤC�q��ܾ�(�Ӧ��)���}
				Delay_ms(1); //����1ms
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=(Num % 100)/10; //��X�Q���
				Data=~Table[i]; //��Q��ƹ������C�q��ܾ��}�C��DATA
				SSLED1=0; //��ĤG�ӤC�q��ܾ�(�Q���)���}
				Delay_ms(1);
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=(Num % 1000)/100; //��X�ʦ��
				Data=~Table[i]; //��ʦ�ƹ������C�q��ܾ��}�C��DATA
				SSLED2=0; //��ĤT�ӤC�q��ܾ�(�ʦ��)���}
				Delay_ms(1);
				SSLED0=SSLED1=SSLED2=SSLED3=1;
				i=Num / 1000; //��X�d���
				Data=~Table[i]; //��d��ƹ������C�q��ܾ��}�C��DATA
				SSLED3=0; //��ĥ|�ӤC�q��ܾ�(�d���)���}
				Delay_ms(1);
		}
		Num++; //�p�ƾ��Ʀr�[�@
		if ( Num%100==60 )
		{
			Num=Num+100;
			Num=Num-60;
		}
		if (Num>6000) Num=0; //�p�ƾ���6000���k�s
	}
}
void beep(unsigned char k) //���ﾹ�Ƶ{���bP3.2���U�ɭp�ƾ��@�˥[�@
{
		unsigned int j;
		while(k--)
		{
				for(j=0;j<100;j++)
				{
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num % 10;
					Data=~Table[i];
					SSLED0=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 100)/10;
					Data=~Table[i];
					SSLED1=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 1000)/100;
					Data=~Table[i];
					SSLED2=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num / 1000;
					Data=~Table[i];
					SSLED3=0;
					Delay_ms(1);
					speak=!speak;
				}
				for(j=0;j<150;j++)
				{
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num % 10;
					Data=~Table[i];
					SSLED0=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 100)/10;
					Data=~Table[i];
					SSLED1=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=(Num % 1000)/100;
					Data=~Table[i];
					SSLED2=0;
					Delay_ms(1);
					SSLED0=SSLED1=SSLED2=SSLED3=1;
					i=Num / 1000;
					Data=~Table[i];
					SSLED3=0;
					Delay_ms(1);
					speak=!speak;
				}
			Num++;
		}
}