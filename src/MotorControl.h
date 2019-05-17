#ifndef _MotorControl_H__
#define _MotorControl_H__
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

class MotorControl
{
public:
    // Constructor:
    MotorControl();
	
	// Functions:
	void init(void);
	void goForward(void);
	void goBack(void);
	void goLeftSwing(void);
	void goRightSwing(void);
	void goLeftPoint(void);
	void goRightPoint(void);
	void goCurve(int, int);
	void goRightCurve(int, int);
	void stop(void);


private:	
	int IN1_PIN;
	int IN2_PIN;
	int IN3_PIN;
	int IN4_PIN;	
};

#endif // _MotorControl_H__
