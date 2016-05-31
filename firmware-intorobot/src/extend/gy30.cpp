

#include "gy30.h"

/**********
����ʪ�ȴ�����
**********/


GY30::GY30()
{
    devAddress = GY30_ADDRESS;
}

void GY30::begin(void)
{
  	Write(0x01);
}

float GY30::Read(void)
{
	u8 i;

	Write(0x01);
	Write(0x10);

	delay(180);
	
    Wire.beginTransmission(devAddress); // ID

    //Wire.write(regAddress); // �Ĵ�����ַ

    //Wire.endTransmission(0); // ������ֹͣλ ���Ƿ��� ID �ͼĴ�����ַ

    //Wire.beginTransmission(devAddr);

    Wire.requestFrom(devAddress, 2);

    for(i = 0; i < 2; i++)
    {
        dat[i] = Wire.read();
    }
    
 	lxData = dat[0];
 	
    lxData=(lxData << 8)+dat[1];//�ϳ����� 
    
    return (float)lxData/1.2;
}

void GY30::Write(u8 regAddress)
{
    Wire.beginTransmission(devAddress);

    Wire.write(regAddress); // send address

    Wire.endTransmission();
}





