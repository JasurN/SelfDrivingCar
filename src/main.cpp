#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <opencv/cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <signal.h>


using namespace cv;
using namespace std;

#define LEFT_TRACER_PIN                10            //- IRTracer
#define RIGHT_TRACER_PIN            11
#define TRIG_PIN                28                //Ultrasonic
#define ECHO_PIN                29
#define IN1_PIN        1                            // left motor
#define IN2_PIN        4                            // left motor
#define IN3_PIN        5                            // right motor
#define IN4_PIN        6                            // right motor
#define LIMIT_DISTANCE  20                        //Ultra limit distance for stop
#define NORMAL_SPEED   50                            //Speed limit

#define MIN_SPEED   0

void my_handler(int s);

void ctrl_c_stop_motor_signal_handler();

bool motorGoing = false;

void initSensorsDCMotor();

int counter = 0;

//motor Control
void goForward();

void goLeft();

void goRight();

void stopDCMotor();

//ultrasonic
void *checkControl(void *threadarg);

int getDistance();

void obstacleAvoid();

//thread function
int main() {
    if (wiringPiSetup() == -1)
        return 0;

    ctrl_c_stop_motor_signal_handler();

    pthread_t pthreads[2];
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);

    initSensorsDCMotor();

    stopDCMotor();
    int sensor_control = pthread_create(&pthreads[0], nullptr, checkControl, (void *) 1);
    if (sensor_control) {
        std::cout << "Error:unableq to create sensor  thread," << sensor_control << std::endl;
    }
    while (true) {

    }
    pthread_exit(nullptr);
    return 0;
}

void initSensorsDCMotor() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);

    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);

    softPwmCreate(IN1_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN2_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN3_PIN, MIN_SPEED, NORMAL_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, NORMAL_SPEED);
}

//Go FmotorGoingorward
void goForward() {

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    // printf("Forward\n");
}

//Go Backward
void goBackward() {
    softPwmWrite(IN1_PIN, MIN_SPEED);

    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, NORMAL_SPEED);

    printf("Back\n");
}

//Go Left
void goLeft() {

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    // printf("Left\n");
}

//Go Right
void goRight() {

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, NORMAL_SPEED);

    // printf("Right\n");
}

//Stop DC Motor
void stopDCMotor() {

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    //printf("Stop\n");
}

//Get distance from ultrasonic
int getDistance() {
    int start_time = 0, end_time = 0;
    float distance = 0;

    digitalWrite(TRIG_PIN, LOW);
    delay(5);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    while (digitalRead(ECHO_PIN) == 0);
    start_time = micros();

    while (digitalRead(ECHO_PIN) == 1);
    end_time = micros();

    distance = (end_time - start_time) / 29. / 2.;

    return (int) distance;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void *checkControl(void *threadarg) {
    while (true) {
        int nLValue = digitalRead(LEFT_TRACER_PIN);
        int nRValue = digitalRead(RIGHT_TRACER_PIN);
        int dis = getDistance();
        pthread_t pthreadCounter;
        if ((nLValue == HIGH) && (nRValue == HIGH)) {

            if (dis <= LIMIT_DISTANCE) {
                //printf("distance - %d cm\n", dis);
                stopDCMotor();
                motorGoing = false;

                while (motorGoing == false) {
                    std::cout << "it is here" << std::endl;

                    int dis = getDistance();
                    if (counter > 1) {
                        std::cout << "counter:  " << counter;
                        obstacleAvoid();
                    }
                    if (dis >= LIMIT_DISTANCE) {
                        std::cout << "inside if" << std::endl;
                        counter++;
                        motorGoing = true;
                        goForward();
                    }
                }
            } else {
                goForward();
            }
        } else if (nLValue == HIGH && nRValue == LOW) {
            // printf(" LEFT detect ~!!! MOVE  ");
            goLeft();
        } else if (nRValue == HIGH && nLValue == LOW) {
            // printf(" RIGHT detect ~!!! MOVE  ");
            goRight();
        } else if ((nLValue == LOW) && (nRValue == LOW)) {
            goForward();
        } else {
            stopDCMotor();
        }
        delay(10);
        //printf("left value: %d  right value: %d\n", nLValue, nRValue);
    }
}

void obstacleAvoid() {
    stopDCMotor();
    std::cout << "STOPED BY OBSTACLE AVOID";
    exit(-1);
}

void my_handler(int s) {
    printf("Caught signal1 %d\n", s);
    stopDCMotor();
    exit(1);

}

void ctrl_c_stop_motor_signal_handler() {
    struct sigaction sigIntHandler{};

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);
}

#pragma clang diagnostic pop



