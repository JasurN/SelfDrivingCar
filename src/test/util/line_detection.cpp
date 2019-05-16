#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <wiringPi.h>
#include "opencv2/highgui.hpp"

#define NO_TURN 0
#define TURN_LEFT_45D 1
#define TURN_LEFT_15D 2
#define TURN_RIGHT_15D 3
#define TURN_RIGHT_45D 4

using namespace std;
using namespace cv;

int LEFT_low_y = 56;
int LEFT_low_x = 0;

int LEFT_up_y = 34;
int LEFT_up_x = 0;

int RIGHT_low_y = 56;
int RIGHT_low_x = 0;

int RIGHT_up_y = 34;
int RIGHT_up_x = 0;

void left_lower_point(Mat left_frame);

void left_upper_point(Mat left_frame);

bool check_left_line(Mat left_frame);

double left_angle_find(const Mat &left_frame);

double right_andgle_find(const Mat &right_frame);

void right_lower_point(const Mat &right_frame);

void right_upper_point(const Mat &right_frame);

bool check_right_line(const Mat &right_frame);

int directionPrediction(double left_angle, double right_angle);

int main() {
    raspicam::RaspiCam_Cv capture;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capture.open();

    cv::Rect full_roi(0, 150, 320, 90);
    cv::Rect left_roi(0, 0, 160, 90);
    cv::Rect right_roi(160, 0, 160, 90);
    cv::Mat src;
    cv::Mat src_roi;
    cv::Mat dst;
    cv::Mat left_frame, right_frame;

//    src = imread("../12.png");
//    resize(src, src, cv::Size(320, 240));
    while (true) {
        capture.grab();
        capture.retrieve(src);
        src_roi = src(full_roi);
        cvtColor(src_roi, src_roi, COLOR_BGR2GRAY);
        GaussianBlur(src_roi, src_roi, Size(5, 5), 0);
        Canny(src_roi, dst, 50, 200, 3);

        left_frame = dst(left_roi);
        right_frame = dst(right_roi);

        directionPrediction(left_angle_find(left_frame),
                right_andgle_find(right_frame));
        imshow("full", dst);
        imshow("left", left_frame);
        imshow("right", right_frame);

        //delay(1000);
        if (cvWaitKey(20) == 'q') // waitkey
        {
            capture.release();
            break;
        }
    }


}

int directionPrediction(double left_angle, double right_angle) {
    if (left_angle > 39 &&  left_angle < 50) {
        return TURN_LEFT_45D;
    }
    if (right_angle > 39 && right_angle < 50) {
        return TURN_RIGHT_45D;
    }
}

double right_andgle_find(const Mat &right_frame) {
    right_lower_point(right_frame);
    right_upper_point(right_frame);

    if (RIGHT_low_x > RIGHT_up_x) {
        bool isLine = check_right_line(right_frame);

        if (isLine) {
            double low_point_angle = ((atan2(RIGHT_low_y, RIGHT_low_x)) * 180 / 3.1415);
            double up_point_angle = ((atan2(RIGHT_up_y, RIGHT_up_x)) * 180 / 3.1415);
//            std::cout << "low right angle: " << low_point_angle << endl;
//            std::cout << "up right angle: " << up_point_angle << endl;

            std::cout << "right difference: " << low_point_angle - up_point_angle  << endl;
            return up_point_angle - low_point_angle;
        }
    }
    return -1;
}

double left_angle_find(const Mat &left_frame) {
    left_lower_point(left_frame);
    left_upper_point(left_frame);

//    cout << endl << "low x :" << LEFT_low_x;
//    cout << endl << "LEFT_up_x :" << LEFT_up_x;
    if (LEFT_low_x > 0 && LEFT_up_x > 0) {
        bool isLine = check_left_line(left_frame);

        if (isLine) {
            double low_point_angle = ((atan2(LEFT_low_y, LEFT_low_x)) * 180 / 3.1415);
            double up_point_angle = ((atan2(LEFT_up_y, LEFT_up_x)) * 180 / 3.1415);
//            std::cout << "low point: " << low_point_angle << endl;
//            std::cout << "up point: " << up_point_angle << endl;

            std::cout << "left difference: " << low_point_angle - up_point_angle << endl;
            return low_point_angle - up_point_angle;

        }

    }
    return -1;
}

bool check_right_line(const Mat &right_frame) {
    int true_count = 0;

    int low_check_y1 = RIGHT_low_y - 3;
    int low_check_y2 = RIGHT_low_y - 7;
    int low_check_y3 = RIGHT_low_y - 13;

    int low_check_x1 = RIGHT_low_x - 18;
    int low_check_x2 = RIGHT_low_x - 25;
    int low_check_x3 = RIGHT_low_x - 35;

    for (int i = low_check_x1; i < RIGHT_low_x; i++) {
        if ((int) right_frame.at<uchar>(low_check_y1, i) > 0) {
//            std::cout << endl << "1 point" << i;
            true_count++;
            break;
        }
    }
    for (int i = low_check_x2; i < RIGHT_low_x; i++) {
        if ((int) right_frame.at<uchar>(low_check_y2, i) > 0) {
//            std::cout << endl << "2 point" << i;
            true_count++;
            break;
        }
    }
    for (int i = low_check_x3; i < RIGHT_low_x; i++) {
        if ((int) right_frame.at<uchar>(low_check_y3, i) > 0) {
//            std::cout << endl << "3 point" << i;
            true_count++;
            break;
        }
    }
    return true_count > 1;
}

void right_upper_point(const Mat &right_frame) {
    RIGHT_up_x = 0;

    for (int i = 0; i < 160; i++) {
        if ((int) right_frame.at<uchar>(RIGHT_up_y, i) > 0) {
            RIGHT_up_x = i;
            break;
        }
    }
    //cout << endl << "up x :" << RIGHT_up_x;

}

void right_lower_point(const Mat &right_frame) {
    RIGHT_low_x = 0;

    for (int i = 0; i < 160; i++) {
        if ((int) right_frame.at<uchar>(RIGHT_low_y, i) > 0) {
            RIGHT_low_x = i;
            break;
        }
    }
    //cout << endl << "low x :" << RIGHT_low_x;

}

bool check_left_line(Mat left_frame) {
    int true_count = 0;

    int low_check_y1 = LEFT_low_y - 3;
    int low_check_y2 = LEFT_low_y - 7;
    int low_check_y3 = LEFT_low_y - 13;

    int low_check_x1 = LEFT_low_x + 18;
    int low_check_x2 = LEFT_low_x + 20;
    int low_check_x3 = LEFT_low_x + 30;

    for (int i = low_check_x1; i > LEFT_low_x; i--) {
        if ((int) left_frame.at<uchar>(low_check_y1, i) > 0) {
//            std::cout << endl << "first true count";
//            std::cout << endl << "1 point" << i;
            true_count++;
            break;
        }
    }

    for (int i = low_check_x2; i > LEFT_low_x; i--) {
        if ((int) left_frame.at<uchar>(low_check_y2, i) > 0) {
//            std::cout << endl << "second true count";
//            std::cout << endl << "2 point" << i;
            true_count++;
            break;
        }
    }

    for (int i = low_check_x3; i > LEFT_low_x; i--) {
        if ((int) left_frame.at<uchar>(low_check_y3, i) > 0) {
//            std::cout << endl << "third true count";
//            std::cout << endl << "3 point" << i;
            true_count++;
            break;
        }
    }

    return true_count > 1;
}

void left_lower_point(Mat left_frame) {
    LEFT_low_x = 0;

    for (int i = 159; i > 0; i--) {
        if ((int) left_frame.at<uchar>(LEFT_low_y, i) > 0) {
            LEFT_low_x = i;
            break;
        }
    }
    // cout << endl << "low x :" << LEFT_low_x;
}

void left_upper_point(Mat left_frame) {
    LEFT_up_x = 0;

    for (int i = 159; i > 0; i--) {
        if ((int) left_frame.at<uchar>(LEFT_up_y, i) > 0) {
            LEFT_up_x = i;
            break;
        }
    }
    // cout << endl << "LEFT_up_x :" << LEFT_up_x;
}

