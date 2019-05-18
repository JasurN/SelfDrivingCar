#ifndef _MotorControl_H__
#define _MotorControl_H__
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

class MotorControl
{
public:
#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11
    MotorControl();
	
	void init();

    void initIrLineTracer();

	void goForward();

	void goBack();

	void goLeftSwing();

	void goRightSwing();

	void goLeftPoint();

	void goRightPoint();

	void goCurve(int leftSpeed, int rightSpeed);

	void goRightCurve(int, int);

	void stop();

    bool isMotorGoing() const;

    void setMotorGoing(bool motorGoingParam);

    bool isMotorGoingForward() const;

    void setMotorGoingForward(bool motorGoingForwardParam);

    bool isMotorGoingBackward() const;

    void setMotorGoingBackward(bool motorGoingBackwardParam);

    bool isMotorGoingLeft() const;

    void setMotorGoingLeft(bool motorGoingLeftParam);

    bool isMotorGoingRight() const;

    void setMotorGoingRight(bool motorGoingRightParam);

private:
    int IN1_PIN;
    int IN2_PIN;
    int IN3_PIN;
    int IN4_PIN;
    bool motorGoing;
    bool motorGoingForward;
	bool motorGoingBackward;
	bool motorGoingLeft;
	bool motorGoingRight;
};

#endif // _MotorControl_H__
