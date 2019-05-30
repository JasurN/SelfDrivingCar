#ifndef SELFDRIVINGCAR_LANEDETECTION_H
#define SELFDRIVINGCAR_LANEDETECTION_H

#define TURN_LEFT 1
#define TURN_RIGHT 2

#include "opencv2/highgui.hpp"
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class LaneDetection {
public:
    LaneDetection();

    void left_lower_point(cv::Mat left_frame);

    void left_upper_point(cv::Mat left_frame);

    bool check_left_line(cv::Mat left_frame);

    double left_angle_find(const cv::Mat &left_frame);

    double right_angle_find(const cv::Mat &right_frame);

    void right_lower_point(const cv::Mat &right_frame);

    void right_upper_point(const cv::Mat &right_frame);

    bool check_right_line(const cv::Mat &right_frame);

    int directionPrediction(double left_angle, double right_angle);

    int getLeftDirectionCounter() const;

    void setLeftDirectionCounter(int leftDirectionCounter);

    int getRightDirectionCounter() const;

    void setRightDirectionCounter(int rightDirectionCounterInputer);

private:
    int LEFT_low_y = 55;
    int LEFT_low_x = 0;

    int LEFT_up_y = 32;
    int LEFT_up_x = 0;

    int RIGHT_low_y = 55;
    int RIGHT_low_x = 0;

    int RIGHT_up_y = 32;
    int RIGHT_up_x = 0;

    int left_directionCounter = 0;
    int rightDirectionCounter = 0;


};

#endif //SELFDRIVINGCAR_LANEDETECTION_H
