//#include <cstdio>
//#include <signal.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <wiringPi.h>
//#include <softPwm.h>
//#include <stdio.h>
//#include <iostream>
//#define IN1_PIN 1
//#define IN2_PIN 4
//#define IN3_PIN 5
//#define IN4_PIN 6
//
//#define LEFT_IR_PIN 27
//#define RIGHT_IR_PIN 26
//
//#define NORMAL_SPEED   50
//#define MIN_SPEED   0
//
//void initDCMotor();
//
//void go();
//
//void stop();
//
//void goBack();
//
//void goRight();
//
//void goLeft();
//
//void my_handler(int s);
//void ctrl_c_stop_motor_signal_handler();
//
//int gSpeed = 40;
//
//int main() {
//
//    bool isGoingForward = true;
//    int nLValue = 0, nRValue = 0;
//    if (wiringPiSetup() == -1) {
//        return 0;
//    }
//    ctrl_c_stop_motor_signal_handler();
//    initDCMotor();
//    pinMode(LEFT_IR_PIN, INPUT);
//    pinMode(RIGHT_IR_PIN, INPUT);
//
//    go();
//
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wmissing-noreturn"
//    while (true) {
//        nLValue = digitalRead(LEFT_IR_PIN);
//        nRValue = digitalRead(RIGHT_IR_PIN);
//
//        if (nLValue == 0 && nRValue == 0) {
//            printf("go back");
//            goBack();
//            delay(1000);
//            isGoingForward = false;
//            goRight();
//            delay(650);
//            stop();
//            continue;
//        } else if (nRValue == 0) {
//            goBack();
//            delay(400);
//            printf("go left");
//            goLeft();
//            delay(700);
//            stop();
//            isGoingForward = false;
//        } else if (nLValue == 0) {
//            goBack();
//            delay(400);
//            printf("go right");
//            goRight();
//            delay(650);
//            stop();
//            isGoingForward = false;
//        } else if (!isGoingForward) {
//            printf("go forward againt");
//            isGoingForward = true;
//            go();
//        }
//        else {
//            printf("R = %d, L = %d\ngoing forward", nRValue, nLValue);
//            delay(200);
//
//        }
//
//    }
//#pragma clang diagnostic pop
//
//
//    return 0;
//}
//
//
////-Motor Initialize-------------------------------------------------------------
//void initDCMotor() {
//    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
//    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
//    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
//    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);
//    softPwmCreate(IN1_PIN, MIN_SPEED, NORMAL_SPEED);
//    softPwmCreate(IN2_PIN, MIN_SPEED, NORMAL_SPEED);
//    softPwmCreate(IN3_PIN, MIN_SPEED, NORMAL_SPEED);
//    softPwmCreate(IN4_PIN, MIN_SPEED, NORMAL_SPEED);
//}
//
////-DC motor go-----------------------------------------------------------------------------------------------
//void go() {
//    softPwmWrite(IN1_PIN, gSpeed);
//    softPwmWrite(IN2_PIN, MIN_SPEED);
//    softPwmWrite(IN3_PIN, gSpeed);
//    softPwmWrite(IN4_PIN, MIN_SPEED);
//    printf("go\n");
//}
//
////-DC motor stop------------------------------------------------------------------------------------------------------------------------
//void stop() {
//    softPwmWrite(IN1_PIN, MIN_SPEED);
//    softPwmWrite(IN2_PIN, MIN_SPEED);
//    softPwmWrite(IN3_PIN, MIN_SPEED);
//    softPwmWrite(IN4_PIN, MIN_SPEED);
//    printf("Stop\n");
//}
//
////-DC motor back------------------------------------------------------------------------------------------------------------------------
//void goBack() {
//    softPwmWrite(IN1_PIN, MIN_SPEED);
//    softPwmWrite(IN2_PIN, gSpeed);
//    softPwmWrite(IN3_PIN, MIN_SPEED);
//    softPwmWrite(IN4_PIN, gSpeed);
//    printf("Go Back\n");
//}
//
////-DC motor right------------------------------------------------------------------------------------------------------------------------
//void goRight() {
//    softPwmWrite(IN1_PIN, 80);
//    softPwmWrite(IN2_PIN, MIN_SPEED);
//    softPwmWrite(IN3_PIN, MIN_SPEED);
//    softPwmWrite(IN4_PIN, 30);
//    printf("Go Right\n");
//}
//
////-DC motor left------------------------------------------------------------------------------------------------------------------------
//void goLeft() {
//    softPwmWrite(IN1_PIN, MIN_SPEED);
//    softPwmWrite(IN2_PIN, 30);
//    softPwmWrite(IN3_PIN, 80);
//    softPwmWrite(IN4_PIN, MIN_SPEED);
//    printf("Go Left\n");
//}
//
//void my_handler(int s){
//    printf("Caught signal %d\n",s);
//    stop();
//    exit(1);
//
//}
//
//void ctrl_c_stop_motor_signal_handler(){
//    struct sigaction sigIntHandler;
//
//    sigIntHandler.sa_handler = my_handler;
//    sigemptyset(&sigIntHandler.sa_mask);
//    sigIntHandler.sa_flags = 0;
//
//    sigaction(SIGINT, &sigIntHandler, NULL);
//}
//
//
//
//
//
//
