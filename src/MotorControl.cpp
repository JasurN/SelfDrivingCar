#include "MotorControl.h"



#define PWM_INIT_VAL       	0
#define PWM_RANGE          	100

#define MAX_SPEED       	100
#define NORM_SPEED       	50
#define TURN_SPEED       	50 // 50
#define MIN_SPEED       	0

#define MOTOR_START_DELAY	5 // 5


MotorControl::MotorControl()
{
	IN1_PIN = 1; // left
	IN2_PIN = 4; // left
	IN3_PIN = 5; // right
	IN4_PIN = 6; // right
    motorGoing = false;
    motorGoingForward = false;
    motorGoingBackward = false;
    motorGoingLeft = false;
    motorGoingRight = false;
	init();
}

void MotorControl::init()
{   
	if(wiringPiSetup() == -1)
		//return 0;
	pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
	pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
	pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
	pinMode(IN4_PIN, SOFT_PWM_OUTPUT);

	softPwmCreate(IN1_PIN, PWM_INIT_VAL, PWM_RANGE);
	softPwmCreate(IN2_PIN, PWM_INIT_VAL, PWM_RANGE);
	softPwmCreate(IN3_PIN, PWM_INIT_VAL, PWM_RANGE);
	softPwmCreate(IN4_PIN, PWM_INIT_VAL, PWM_RANGE);
}

void MotorControl::goForward()
{
	softPwmWrite(IN1_PIN, MAX_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, NORM_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, NORM_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	//delay(MOTOR_START_DELAY);
    printf("Go Forward\n");
}

void MotorControl::goBack()
{
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, MAX_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, MAX_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, NORM_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, NORM_SPEED);
	delay(MOTOR_START_DELAY);
	printf("Go Backward \n");
}

void MotorControl::goCurve(int leftSpeed, int rightSpeed)
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    delay(MOTOR_START_DELAY);
    softPwmWrite(IN1_PIN, leftSpeed);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, rightSpeed);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("LeftCurve\n");
}

void MotorControl::stop()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Stop Car\n");
}

void MotorControl::goLeftSwing()
{
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, TURN_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	//delay(MOTOR_START_DELAY);
	printf("LeftSwing\n");
}

void MotorControl::goRightSwing()
{
	softPwmWrite(IN1_PIN, MAX_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, TURN_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	//delay(MOTOR_START_DELAY);
	printf("RightSwing\n");
}

void MotorControl::goLeftPoint()
{
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, MAX_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, MIN_SPEED);
	softPwmWrite(IN2_PIN, NORM_SPEED);
	softPwmWrite(IN3_PIN, NORM_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	printf("LeftPoint\n");
}

void MotorControl::goRightPoint()
{
	softPwmWrite(IN1_PIN, MAX_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, MAX_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, NORM_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MIN_SPEED);
	softPwmWrite(IN4_PIN, NORM_SPEED);
	printf("RightPoint\n");
}

void MotorControl::goRightCurve(int leftVal, int rightVal)
{
	softPwmWrite(IN1_PIN, MAX_SPEED);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	delay(MOTOR_START_DELAY);
	softPwmWrite(IN1_PIN, leftVal);
	softPwmWrite(IN2_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, rightVal);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	printf("RightPoint\n");
}

bool MotorControl::isMotorGoing() const {
    return motorGoing;
}

void MotorControl::setMotorGoing(bool motorGoingParam) {
    MotorControl::motorGoing = motorGoingParam;
}

bool MotorControl::isMotorGoingForward() const {
    return motorGoingForward;
}

void MotorControl::setMotorGoingForward(bool motorGoingForwardParam) {
    MotorControl::motorGoingForward = motorGoingForwardParam;
}

bool MotorControl::isMotorGoingBackward() const {
    return motorGoingBackward;
}

void MotorControl::setMotorGoingBackward(bool motorGoingBackwardParam) {
    MotorControl::motorGoingBackward = motorGoingBackwardParam;
}

bool MotorControl::isMotorGoingLeft() const {
    return motorGoingLeft;
}

void MotorControl::setMotorGoingLeft(bool motorGoingLeftParam) {
    MotorControl::motorGoingLeft = motorGoingLeftParam;
}

bool MotorControl::isMotorGoingRight() const {
    return motorGoingRight;
}

void MotorControl::setMotorGoingRight(bool motorGoingRightParam) {
    MotorControl::motorGoingRight = motorGoingRightParam;
}


