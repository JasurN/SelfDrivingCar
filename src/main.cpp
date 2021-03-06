#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <opencv/cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <signal.h>
#include <raspicam/raspicam_cv.h>

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

void initSensorsDCMotor();

void goForward();

void goLeft();

void goRight();

void stopDCMotor();

void *checkControl(void *threadarg);

int getDistance();

void obstacleAvoid();

void *enable_cascading(void *threadArg);

bool checkpoint1 = false;
bool checkpoint2 = false;

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
    delay(2000);
    int sensor_thread_result = pthread_create(&pthreads[0], nullptr, checkControl, (void *) 1);
    if (sensor_thread_result) {
        std::cout << "Error:unable to create sensor  thread," << sensor_thread_result << std::endl;
    }

    int cascade_thread_result = pthread_create(&pthreads[1], nullptr, enable_cascading, (void *) 2);
    if (cascade_thread_result) {
        std::cout << "Error:unable to create sensor  thread," << cascade_thread_result << std::endl;
    }

    while (true) {

    }
    pthread_exit(nullptr);
    return 0;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void *enable_cascading(void *threadArg) {
    raspicam::RaspiCam_Cv capture;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capture.open();
    Mat bgr;


    CascadeClassifier cascade_becareful, cascade_circle, cascade_left,
            cascade_stop, cascade_parking, cascade_right, cascade_forward;
    cascade_becareful.load("cascade/cas_becareful.xml");
    cascade_circle.load("cascade/cas_circle.xml");
    cascade_left.load("cascade/cas_left.xml");
    cascade_stop.load("cascade/cas_stop.xml");
    cascade_parking.load("cascade/cas_parking.xml");
    cascade_right.load("cascade/cas_right.xml");
    cascade_forward.load("cascade/cas_forward.xml");
    vector<Rect> becareful;
    vector<Rect> circle;
    vector<Rect> left_;
    vector<Rect> stop_;
    vector<Rect> parking;
    vector<Rect> right_;
    vector<Rect> forward;

    while (true) {
        capture.grab(); //grab the scene using raspicam
        capture.retrieve(bgr); // retrieve the captured scene as an image and store it in matrix container
        if (bgr.empty()) {
            std::cout << "EMPTY";
        }
        // These are detection function where you invoke the classifiers on to the frame to detect the trained elements
        cascade_becareful.detectMultiScale(bgr, becareful, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_circle.detectMultiScale(bgr, circle, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_left.detectMultiScale(bgr, left_, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_stop.detectMultiScale(bgr, stop_, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_parking.detectMultiScale(bgr, parking, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_right.detectMultiScale(bgr, right_, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        cascade_forward.detectMultiScale(bgr, forward, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(100, 100));
        // To draw rectangles around detected objects accordingly
        for (const auto &i : becareful) {
            rectangle(bgr, i, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & j : circle) {
            rectangle(bgr, j, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & k : left_) {
            rectangle(bgr, k, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & l : stop_) {
            rectangle(bgr, l, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & m : parking) {
            rectangle(bgr, m, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & n : right_) {
            rectangle(bgr, n, Scalar(255, 0, 0), 2, 1);
        }

        for (const auto & o : forward) {
            rectangle(bgr, o, Scalar(255, 0, 0), 2, 1);
        }
        imshow("original", bgr);
    }
}

#pragma clang diagnostic pop

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
        if ((nLValue == HIGH) && (nRValue == HIGH)) {
            if (dis <= LIMIT_DISTANCE) {
                printf("distance - %d cm\n", dis);
                stopDCMotor();
                delay(100);
                checkpoint1 = true;
                if (checkpoint2) {
                    obstacleAvoid();
                }
            } else {
                goForward();
                if (checkpoint1) {
                    checkpoint2 = true;
                }
            }
        } else if (nLValue == HIGH && nRValue == LOW) {

            goLeft();
        } else if (nRValue == HIGH && nLValue == LOW) {
            goRight();
        } else if ((nLValue == LOW) && (nRValue == LOW)) {
            goForward();
        }
    }
}

void obstacleAvoid() {
    std::cout << "STOPED BY OBSTACLE AVOID";
    goLeft();
    delay(1000);
    stopDCMotor();

    goForward();
    delay(600);
    stopDCMotor();

    goRight();
    delay(950);
    stopDCMotor();

    goForward();
    delay(1700);
    stopDCMotor();

    goRight();
    delay(900);
    stopDCMotor();

    goForward();
    delay(600);
    stopDCMotor();

    goLeft();
    delay(900);
    stopDCMotor();

    //eight 3000
    goForward();
    delay(2500);
    stopDCMotor();

    goLeft();
    delay(900);
    stopDCMotor();

    goForward();
    delay(2500);
    stopDCMotor();

    stopDCMotor();
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



