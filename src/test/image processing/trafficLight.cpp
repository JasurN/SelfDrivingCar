////////////////////////////////////////////////////////
////! Comanda team
////! IUT
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
//using namespace std;
//using namespace cv;
//
//void initDCMotor();
//void goForward();
//void stop();
//void my_handler(int s);
//void ctrl_c_stop_motor_signal_handler();
//int gSpeed = 30;
//
//int main() {
//    if (wiringPiSetup() == -1){
//        return -1;
//    }
//
//    initDCMotor();
//    ctrl_c_stop_motor_signal_handler();
//    bool motorRedStop = false;
//    bool motorGoing = false;
//
//    cv::Mat3b bgr;
//    raspicam::RaspiCam_Cv capture;
//    capture.set(CV_CAP_PROP_FPS, 5);
//    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
//    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
//    capture.open();
//    while (true) {
//        capture.grab();
//        capture.retrieve(bgr);
//        if (bgr.empty()) {
//            printf("empty\n");
//            break;
//        }
//        cv::Mat3b hsv;
//        cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);
//
//        cv::Mat1b green_mask, gaussianBlur_green, gaussianBlur_red;
//
//        Mat1b mask1, mask2;
//        inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
//        inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);
//
//        Mat1b red_mask = mask1 | mask2;
//
//        inRange(hsv, cv::Scalar(45, 100, 100), cv::Scalar(75, 255, 255), green_mask);
//        GaussianBlur(green_mask, gaussianBlur_green, cv::Size(9, 9), 2, 2);
//        GaussianBlur(red_mask, gaussianBlur_red, cv::Size(9, 9), 2, 2);
//
//        vector<Vec3f> circles_green;
//        vector<Vec3f> circles_red;
//
//        HoughCircles(gaussianBlur_green, circles_green, cv::HOUGH_GRADIENT, 1,
//                     10,  // change this value to detect circles_green with different distances to each other
//                     50, 20, 0, 0);
//        HoughCircles(gaussianBlur_red, circles_red, cv::HOUGH_GRADIENT, 1,
//                     10,  // change this value to detect circles_green with different distances to each other
//                     100, 20, 0, 0);
//
//        if(motorGoing == false && motorRedStop == false) {
//            goForward();
//            printf("motor start init\n");
//            motorGoing = true;
//        }
//
//        if(circles_red.size() == 1 && motorRedStop == false) {
//            motorRedStop = true;
//            motorGoing = false;
//            stop();
//            printf("red stop\n");
//
//        }
//
//        if(circles_green.size() == 1 && motorRedStop == true) {
//            motorRedStop = false;
//            motorGoing = true;
//            goForward();
//            printf("green goForward");
//
//        }
//        //printf("green size: %lu\n", circles_green.size());
//        //printf("red size: %lu\n", circles_red.size());
//        imshow("Original", bgr);
//        imshow("GaussianBlue Green", gaussianBlur_green);
//        imshow("GaussianBlue Red", gaussianBlur_red);
//        if (cvWaitKey(20) == 'q')
//            break;
//    }
//    capture.release();
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
////-DC motor goForward-----------------------------------------------------------------------------------------------
//void goForward() {
//    softPwmWrite(IN1_PIN, gSpeed);
//    softPwmWrite(IN2_PIN, MIN_SPEED);
//    softPwmWrite(IN3_PIN, gSpeed);
//    softPwmWrite(IN4_PIN, MIN_SPEED);
//    printf("goForward\n");
//}
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
////// Compile :
///* g++ trafficLightDetect_RaspianPorted.cpp -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib -lwiring -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util `pkg-config --cflags --libs opencv` */
//
//
//
