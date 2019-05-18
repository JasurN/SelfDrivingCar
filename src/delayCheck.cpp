#include "MotorControl.h"
#include <iostream>
#include <wiringPi.h>

#define IN1_PIN		1							// left motor
#define IN2_PIN		4							// left motor
#define IN3_PIN		5							// right motor
#define IN4_PIN		6

#define NORMAL_SPEED   50							//Speed limit
#define MIN_SPEED   0


void testDelay();
MotorControl motorControl;
int main() {
    testDelay();
    return 0;
}
void goLeft()
{

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    printf("Left\n");
}

void testDelay() {
    int delayTime = 0;
    std::cin >> delayTime;
    goLeft();
    delay(delayTime);
    motorControl.stop();
    testDelay();
}