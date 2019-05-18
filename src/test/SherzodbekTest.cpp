#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <softPwm.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <opencv/cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <raspicam/raspicam_cv.h>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;


#define LEFT_TRACER_PIN				10			//- IRTracer
#define RIGHT_TRACER_PIN			11
#define TRIG_PIN				28				//Ultrasonic
#define ECHO_PIN				29
#define IN1_PIN		1							// left motor
#define IN2_PIN		4							// left motor
#define IN3_PIN		5							// right motor
#define IN4_PIN		6							// right motor
#define LIMIT_DISTANCE  20						//Ultra limit distance for stop
#define NORMAL_SPEED   50							//Speed limit

#define MIN_SPEED   0



void initDCMotor();
void goForward();
void goLeft();
void goRight();
void stopDCMotor();
void checkControl();
int getDistance();

//Declaration of functions Hardware
void setup();

//GV for line detect

// Global variables for traffic light detection
raspicam::RaspiCam_Cv capture;
static unsigned char LINE[] = {21,22,26};



int main(void)
{
    if(wiringPiSetup() == -1)
        return 0;

    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);

    initDCMotor();


    setup();

    cout<<"\nCamera Started\n";
    stopDCMotor();

    while(1)
    {
        checkControl();
    }

    capture.release();


    return 0;
}

void initDCMotor()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LEFT_TRACER_PIN,   INPUT);
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

//Go Forward
void goForward()
{

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    printf("Forward\n");
}

//Go Backward
void goBackward()
{
    softPwmWrite(IN1_PIN, MIN_SPEED);

    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, NORMAL_SPEED);

    printf("Back\n");
}

//Go Left
void goLeft()
{

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, NORMAL_SPEED);
    softPwmWrite(IN3_PIN, NORMAL_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    printf("Left\n");
}

//Go Right
void goRight()
{

    softPwmWrite(IN1_PIN, NORMAL_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, NORMAL_SPEED);

    printf("Right\n");
}

//Stop DC Motor
void stopDCMotor()
{

    softPwmWrite(IN1_PIN, MIN_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MIN_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);

    printf("Stop\n");
}

//Get distance from ultrasonic
int getDistance()
{
    int 		start_time=0, end_time=0;
    float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(5) ;
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;

    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;

    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;

    distance = (end_time - start_time) / 29. / 2. ;

    return (int)distance;
}


//IR tracker
void checkControl()
{
    int  nLValue = digitalRead(LEFT_TRACER_PIN);
    int  nRValue = digitalRead(RIGHT_TRACER_PIN);
    int dis = getDistance();

    if( (nLValue == HIGH) && (nRValue == HIGH))
    {
        if( dis <= LIMIT_DISTANCE){
            printf("distance - %d cm\n", dis) ;

            stopDCMotor();
        }else{
            goForward();



        }
    }else if( nLValue == HIGH){
        printf(" LEFT detect ~!!! MOVE  ");
        goLeft();
    }else if(nRValue == HIGH){
        printf(" RIGHT detect ~!!! MOVE  ");
        goRight();
    }else{
        stopDCMotor();
    }
}

void setup(){
    wiringPiSetup();
    int i;
    for(i=0; i<sizeof(LINE); i++){
        pinMode(LINE[i], INPUT);
    }
}


