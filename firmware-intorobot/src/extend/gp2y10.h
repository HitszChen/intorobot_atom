

#ifndef GP2Y10_H_
#define GP2Y10_H_

#include "application.h"

// ��������ʱ����10 ms  LED����ʱ����320us ���в��� 280us 40us
#define		SAMPLE_TIME		280 // us
#define 	SAMPLE_TIME_2	40
#define     PLUSE_TIME		9680


// �����ҳ������� AD�ɼ�

class GP2Y10
{
	public:
	GP2Y10(u16 dustPin,u16 ledPin);
	void begin(void);
	void Read(void);
	
	u16 CalculatedConcentration(void);

	private:
	u16 _dustPin;
	u16 _ledPin;
	u32 dustVoltage;
	
};


#endif 

