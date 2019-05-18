////////////////////////////////////////////////////////
////! Comanda team
///////////////////////////////////////////////////////
//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <wiringPi.h>
//#include <iostream>
//#include <raspicam/raspicam_cv.h>
//#include <softPwm.h>
//#include <csignal>
//
//#define IN1_PIN 1
//#define IN2_PIN 4
//#define IN3_PIN 5
//#define IN4_PIN 6
//
//#define NORMAL_SPEED   50
//#define MIN_SPEED   0
//
//void initSensorsDCMotor();
//
//void goForward();
//
//void stop();
//
//void my_handler(int s);
//
//void ctrl_c_stop_motor_signal_handler();
//
//int gSpeed = 30;
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    if (wiringPiSetup() == -1) {
//        return -1;
//    }
//
//    initSensorsDCMotor();
//    ctrl_c_stop_motor_signal_handler();
//
//    int rectangle_counter = 0;
//    Mat src;
//    bool zebraStoped = false;
//    bool motorGoing = false;
//    raspicam::RaspiCam_Cv capture;
//    capture.set(CV_CAP_PROP_FPS, 5);
//    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
//    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
//    capture.open();
//
//    while (true) {
//        capture.grab();
//        capture.retrieve(src);
//        if (src.empty()) {
//            printf("camera empty\n");
//            break;
//        }
//        rectangle_counter = 0;
//        Mat src_gray;
//        Mat canny_output;
//
//        cvtColor(src, src_gray, COLOR_BGR2GRAY);
//        blur(src_gray, src_gray, Size(3, 3));
//
//
//        Canny(src_gray, canny_output, 100, 150, 3);
//        //dilate(canny_output, canny_output, 1);
//        //erode(canny_output, canny_output, 1);
//        vector<vector<Point>> countours;
//        findContours(canny_output, countours, RETR_TREE, CHAIN_APPROX_SIMPLE);
//        vector<Point> approx;
//        Mat dst = src_gray.clone();
//        for (int i = 0; i < countours.size(); i++) {
//            approxPolyDP(Mat(countours[i]), approx, arcLength(Mat(countours[i]), true) * 0.01, true);
//
//            if (approx.size() >= 4 && (approx.size() <= 6) && contourArea(countours[i]) > 5) {
//                rectangle_counter++;
//
//            }
//        }
//        if (rectangle_counter > 6 && zebraStoped == false && rectangle_counter < 15) {
//            printf("zebra Stop\n");
//            stop();
//            delay(5000);
//            goForward();
//
//        }
//
//        if (motorGoing == false && zebraStoped == false) {
//            goForward();
//        }
//        printf("rectangle counter: %d\n", rectangle_counter);
//        imshow("canny", canny_output);
//
//        if (cvWaitKey(20) == 'q') {
//            break;
//        }
//    }
//    capture.release();
//
//    return 0;
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
//
////-DC motor go-----------------------------------------------------------------------------------------------
//void goForward() {
//    softPwmWrite(IN1_PIN, gSpeed);
//    softPwmWrite(IN2_PIN, MIN_SPEED);
//    softPwmWrite(IN3_PIN, gSpeed);
//    softPwmWrite(IN4_PIN, MIN_SPEED);
//    printf("goForward\n");
//}
//
////-Motor Initialize-------------------------------------------------------------
//void initSensorsDCMotor() {
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
//void my_handler(int s) {
//    printf("Caught signal %d\n", s);
//    stop();
//    exit(1);
//
//}
//
//void ctrl_c_stop_motor_signal_handler() {
//    struct sigaction sigIntHandler;
//
//    sigIntHandler.sa_handler = my_handler;
//    sigemptyset(&sigIntHandler.sa_mask);
//    sigIntHandler.sa_flags = 0;
//
//    sigaction(SIGINT, &sigIntHandler, NULL);
//}
