

/**********
����ʪ�ȴ�����
**********/

#ifndef YL38_H_
#define YL38_H_

#include "application.h"


// ����ʪ�ȴ����� AD�ɼ�

class YL38
{
	public:
		
	YL38(u16 pin);
	void begin(void);
	u32 Read(void);
	u8 CalculateHumidity(void);

	private:
	u16 _pin;
	u32 soilHumidity;
};


#endif 

