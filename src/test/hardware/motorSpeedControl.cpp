#include <cstdio>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6
#define MAX_SPEED  40
#define MIN_SPEED   0

void initDCMotor();

void go();

void stop();
void my_handler(int s);
void ctrl_c_stop_motor_signal_handler();

int gCnt = 3;
int gSpeed = MIN_SPEED;

int main(void) {
    ctrl_c_stop_motor_signal_handler();
    int nLevel = 0;

    if (wiringPiSetup() == -1){
        return 0;
    }

    initDCMotor();

    while (gCnt >= 0) {
        printf("gCnt = %d\n", gCnt);
        if (gCnt == 0) {
            gSpeed = MIN_SPEED;
            stop();
            delay(1000);
        } else {
            for (nLevel = 30; nLevel <= MAX_SPEED; ) {
                gSpeed = nLevel;
                go();
                delay(1000);
            }
        }
        gCnt--;
    }
    return 0;
}


//-Motor Initialize-------------------------------------------------------------
void initDCMotor() {
    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);
    softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

//-DC motor go-----------------------------------------------------------------------------------------------
void go() {
    softPwmWrite(IN1_PIN, gSpeed);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, gSpeed);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("go\n");
}

//-DC motor stop------------------------------------------------------------------------------------------------------------------------
void stop() {
    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Stop\n");
}

void my_handler(int s){
    printf("Caught signal %d\n",s);
    stop();
    exit(1);

}

void ctrl_c_stop_motor_signal_handler(){
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
}


