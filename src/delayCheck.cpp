#include "MotorControl.h"
#include <iostream>
#include <wiringPi.h>

#define IN1_PIN        1                            // left motor
#define IN2_PIN        4                            // left motor
#define IN3_PIN        5                            // right motor
#define IN4_PIN        6

#define NORMAL_SPEED   50                            //Speed limit
#define MIN_SPEED   0

void testDelay();

void initSensorsDCMotor() {
    if (wiringPiSetup() == -1)
        return;

    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);

    softPwmCreate(IN1_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN2_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN3_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, NORMAL_SPEED);
}

int main() {
    initSensorsDCMotor();
    testDelay();
    return 0;
}

void goLeft() {

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    printf("Left\n");
}

void stopDCMotor() {

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    //printf("Stop\n");
}

//Go Right
void goRight() {

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, NORMAL_SPEED);

    // printf("Right\n");
}

void goForward() {

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    // printf("Forward\n");
}

void testDelay() {
    int delayTime = 0;

    //one 1000
    std::cin >> delayTime;
    goLeft();
    std::cout << delayTime << std::endl;
    delay(delayTime);
    stopDCMotor();
//two 650

    std::cin >> delayTime;
    goForward();
    delay(delayTime);
    stopDCMotor();
//three 900
    std::cin >> delayTime;
    goRight();
    delay(delayTime);
    stopDCMotor();
//four 1800
    std::cin >> delayTime;
    goForward();
    delay(delayTime);
    stopDCMotor();

// five 900
    std::cin >> delayTime;
    goRight();
    delay(delayTime);
    stopDCMotor();

    //six 650
    std::cin >> delayTime;
    goForward();
    delay(delayTime);
    stopDCMotor();

    //seven 1000
    std::cin >> delayTime;
    goLeft();
    std::cout << delayTime << std::endl;
    delay(delayTime);
    stopDCMotor();

    //six 3000
    std::cin >> delayTime;
    goForward();
    delay(delayTime);
    stopDCMotor();


    testDelay();
}