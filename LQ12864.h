/************************************************************************************
*  Copyright (c), 2013, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: LQ12864.h
* Project  : OLED
* Processor: STC89C52
* Compiler : Keil C51 Compiler
* 
* Author : С��
* Version: 1.00
* Date   : 2013.8.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64����OLEDģ�������ļ���������heltec.taobao.com���۲�Ʒ
*
* Others: none;
*
* Function List:
*
* 1. void delay(unsigned int z) -- ��ʱ����,����
* 2. void IIC_Start() -- ����I2C����
* 3. void IIC_Stop() -- �ر�I2C����
* 4. void Write_IIC_Byte(unsigned char IIC_Byte) -- ͨ��I2C����дһ��byte������
* 5. void OLED_WrDat(unsigned char dat) -- ��OLED��д����
* 6. void OLED_WrCmd(unsigned char cmd) -- ��OLED��д����
* 7. void OLED_Set_Pos(unsigned char x, unsigned char y) -- ������ʾ����
* 8. void OLED_Fill(unsigned char bmp_dat) -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
* 9. void OLED_CLS(void) -- ��λ/����
* 10. void OLED_Init(void) -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
* 11. void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]) -- 6x8������������ʾASCII�����С���У���̫����
* 12. void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]) -- 8x16������������ʾASCII�룬�ǳ�����
* 13.void OLED_P16x16Ch(unsigned char x, y, N) -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
* 14.void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ��128x64���ص�BMPλͼ��ȡ������������ֱ���Ȼ���Ƶ�codetab�У��˺������ü���
*
* History: none;
*
*************************************************************************************/
#include "hbird_sdk_soc.h"
#include "iic.h"

#include "codetab.h"


// // ------------------------------------------------------------
// // IO��ģ��I2Cͨ��
// // SCL��P1^3
// // SDA��P1^2
// // ------------------------------------------------------------
// sbit SCL=P1^3; //����ʱ��
// sbit SDA=P1^2; //��������

// #define high 1
// #define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
// /*********************OLED���������õ���ʱ����************************************/
// void delay(unsigned int z)
// {
// 	unsigned int x,y;
// 	for(x=z;x>0;x--)
// 		for(y=110;y>0;y--);
// }

// /**********************************************
// //IIC Start
// **********************************************/
// void IIC_Start()
// {
//    i2c_send_command(IIC_CHANNEL, I2C_START);
// }

// /**********************************************
// //IIC Stop
// **********************************************/
// void IIC_Stop()
// {
//    SCL = low;
//    SDA = low;
//    SCL = high;
//    SDA = high;
// }


void delay(uint32_t cnt)
{
    uint32_t i = 0, j = 0;

    // when SystemCoreClock is 16Mhz, 1/16 us
    for(i=0; i<cnt; i++)
    {
		for(j=110;j>0;j--)
		{
        	__NOP();
		}
    }

}

/**********************************************
// ͨ��I2C����дһ���ֽ�
**********************************************/
void Write_IIC_First_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	i2c_send_data(IIC_CHANNEL, IIC_Byte);
	// i2c_send_command(IIC_CHANNEL, I2C_START);
	// i2c_send_command(IIC_CHANNEL, I2C_WRITE);
	i2c_send_command(IIC_CHANNEL, I2C_START_WRITE);

	i = i2c_get_ack(IIC_CHANNEL);
}

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;

	i2c_send_data(IIC_CHANNEL, IIC_Byte);
	i2c_send_command(IIC_CHANNEL, I2C_WRITE);
	i = i2c_get_ack(IIC_CHANNEL);
}

void Write_IIC_Last_Byte(unsigned char IIC_Byte)
{
	unsigned char i;

	i2c_send_data(IIC_CHANNEL, IIC_Byte);
	i2c_send_command(IIC_CHANNEL, I2C_STOP_WRITE);
	// i2c_send_command(IIC_CHANNEL, I2C_WRITE);
	i = i2c_get_ack(IIC_CHANNEL);
	// i2c_send_command(IIC_CHANNEL, I2C_STOP);
}

/*********************OLEDд����************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	// IIC_Start();
	Write_IIC_First_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Last_Byte(IIC_Data);
	// IIC_Stop();
}
/*********************OLEDд����************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	// IIC_Start();
	Write_IIC_First_Byte(0x78);            //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Last_Byte(IIC_Command);
	// IIC_Stop();
}
/*********************OLED ��������************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y); // 设置 PAGE对应的位置, 即0-7一共8页, 对应8个大行
	OLED_WrCmd(((x&0xf0)>>4)|0x10); // Set Lower Column Start Address for Page Addressing Mode, column的起始列
	OLED_WrCmd((x&0x0f)|0x01); //Set Higher Column Start Address for Page Addressing Mode, column的起始列
} 
/*********************OLEDȫ��************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED��λ************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED��ʼ��************************************/
void OLED_Init(void)
{
	delay(50000);//��ʼ��֮ǰ����ʱ����Ҫ��
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x01); //��ʼ����
	OLED_Set_Pos(0,0);
} 
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void OLED_P16x16Ch(unsigned char x, unsigned char y,unsigned char  N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	} 	  	
}

/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void OLED_P16x16Ch_gp(unsigned char x, unsigned char y,unsigned char  N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_group_name[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16_group_name[adder]);
		adder += 1;
	} 	  	
}

/*****************������������ʾ16*8����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void OLED_P16x8Ch_gp(unsigned char x, unsigned char y,unsigned char  N)
{
	unsigned char wm=0;
	unsigned int adder=16*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 8;wm++)
	{
		OLED_WrDat(F16x16_group_name[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 8;wm++)
	{
		OLED_WrDat(F16x16_group_name[adder]);
		adder += 1;
	} 	  	
}


/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1,unsigned char  y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WrDat(BMP[j++]);
	    }
	}
}
