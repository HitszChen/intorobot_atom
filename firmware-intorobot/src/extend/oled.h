

#ifndef OLED_H_
#define OLED_H_

#include "application.h"
#include "oled_codetab.h"


/**
SCK --- 
SDA --- 
RST ---   // ֱ��IO����
DC  ---  ��������ѡ�� 1 ��ʾ�������� 0��ʾ��������
**/



#define XLevelL				0x00
#define XLevelH				0x10
#define XLevel	    		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column			128
#define Max_Row				64
#define	Brightness			0xCF 
#define X_WIDTH 			128
#define Y_WIDTH 			64

// 0.96 OLED ��Ļ SPIģ�⴫��

class OLED
{

	public:
	OLED(u16 pinDC,u16 pinRST,u16 pinSDA,u16 pinSCL);
	//OLED�����ú���
	void begin(void);
	void OLED_WrDat(unsigned char dat);//д����
	void OLED_WrCmd(unsigned char cmd);//д����
	void OLED_SetPos(unsigned char x, unsigned char y);//������ʼ������
	void OLED_Fill(unsigned char bmp_dat);//ȫ�����
	void OLED_CLS(void);//����
	void OLED_Init(void);//��ʼ��
	void OLED_6x8Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);
	void OLED_8x16Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);


	private:
	u16 DC;
	u16 RST;
	u16 SDA;
	u16 SCL;
};


#endif 

