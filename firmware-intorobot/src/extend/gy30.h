

#ifndef GY30_H_
#define GY30_H_

// ����ǿ�� 

#include "application.h"


#define   GY30_ADDRESS 	0x46 >> 1


// ����ǿ�ȴ����� IICͨѶ D8(SDA) D9(SCL)

class GY30
{
	public:
	GY30();
	void begin(void);
	float Read(void);

	void Write(u8 regAddress);

	private:
	u8 devAddress;
	u8 dat[2];
	u16 lxData;
};


#endif 

