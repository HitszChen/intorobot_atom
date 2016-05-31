/**
 *******************************************************************************
 * @file:       application.cpp
 * @author:  robin
 * @version: V1.0.0
 * @date:     30-November-2014
 * @brief:     the header of application.cpp
 *******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */
#include "application.h"


int ControlTemperature(String paraString);
int ControlHumidity(String paraString);
int ControlLeftSpeed(String paraString);
int ControlRightSpeed(String paraString);
int ControlLight(String paraString);

void setup()
{
	//Register all the datastreams
	IntoRobot.adddatastream("d_temperature", INT);   //�¶�����
	IntoRobot.adddatastream("d_humidity", INT);      //ʪ������
	IntoRobot.adddatastream("d_letfspeed", INT);      //�����ٶ�����
	IntoRobot.adddatastream("d_rightspeed", INT);     //�����ٶ�����
	IntoRobot.adddatastream("d_light", BOOLEAN);      //�ƹ⿪������

	//Register all the commandstreams
	IntoRobot.addcommandstream("c_temperature", INT, ControlTemperature); //�����¶�
	IntoRobot.addcommandstream("c_humidity", INT, ControlHumidity);       //����ʪ��
	IntoRobot.addcommandstream("c_letfspeed", INT, ControlLeftSpeed);     //���������ٶ�
	IntoRobot.addcommandstream("c_rightspeed", INT, ControlRightSpeed);   //���������ٶ�
    IntoRobot.addcommandstream("c_light", BOOLEAN, ControlLight);         //���Ƶƹ⿪��
}

void loop()
{
	//This will run in a loop
    IntoRobot.senddata("d_temperature", 23.5);  //�¶�����
    IntoRobot.senddata("d_humidity", 80);       //ʪ������
    IntoRobot.senddata("d_letfspeed", 100);     //�����ٶ�����
    IntoRobot.senddata("d_rightspeed", 100);    //�����ٶ�����
    IntoRobot.senddata("d_light", true);        //�ƹ⿪������
}

/*********************************************************************************
  *Function:       GraphDigitalRead
  *Description�r read digital  status 
  *Input:            string pin
  *Output:        
  *Return:          digital status
  *author:          robin
  *date:             2014-12-01          
  *Others:        
**********************************************************************************/
int ControlTemperature(String paraString)
{
    return 0;
}

/*********************************************************************************
  *Function:       GraphDigitalWrite
  *Description�r write digital  status 
  *Input:            string pin
  *Output:        
  *Return:          set status
  *author:          robin
  *date:             2014-12-01          
  *Others:        
**********************************************************************************/
int ControlHumidity(String paraString)
{
    return 0;
}

/*********************************************************************************
  *Function:       GraphAnalogRead
  *Description�r read anolog  value 
  *Input:            string pin
  *Output:        
  *Return:          analog value
  *author:          robin
  *date:             2014-12-01          
  *Others:        
**********************************************************************************/
int ControlLeftSpeed(String paraString)
{
    return 0;
}

/*********************************************************************************
  *Function:       GraphAnalogWrite
  *Description�r output pwm
  *Input:            command
  *Output:        
  *Return:          set status
  *author:          robin
  *date:             2014-12-01          
  *Others:        
**********************************************************************************/
int ControlRightSpeed(String paraString)
{
    return 0;
}

/*********************************************************************************
  *Function:       GraphAnalogWrite
  *Description�r output pwm
  *Input:            command
  *Output:        
  *Return:          set status
  *author:          robin
  *date:             2014-12-01          
  *Others:        
**********************************************************************************/
int ControlLight(String paraString)
{
    return 0;
}


