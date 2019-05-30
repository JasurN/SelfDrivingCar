#include "LaneDetection.h"

int LaneDetection::directionPrediction(double left_angle, double right_angle) {
    std::cout << "left angle:   " << left_angle << std::endl;
    std::cout << "right angle:  " << right_angle << std::endl;

    if (left_angle > 10) {
        left_directionCounter++;
    }
    else if (right_angle > 10) {
        rightDirectionCounter++;
    }
}

double LaneDetection::right_angle_find(const cv::Mat &right_frame) {
    right_lower_point(right_frame);
    right_upper_point(right_frame);

    if (RIGHT_low_x > RIGHT_up_x) {
        bool isLine = check_right_line(right_frame);

        if (isLine) {
            double low_point_angle = ((atan2(RIGHT_low_y, RIGHT_low_x)) * 180 / 3.1415);
            double up_point_angle = ((atan2(RIGHT_up_y, RIGHT_up_x)) * 180 / 3.1415);
            double right_angle = up_point_angle - low_point_angle;
            return right_angle;
        }
    }
    return -1;
}

double LaneDetection::left_angle_find(const cv::Mat &left_frame) {
    left_lower_point(left_frame);
    left_upper_point(left_frame);

    if (LEFT_low_x > 0 && LEFT_up_x > 0) {
        bool isLine = check_left_line(left_frame);

        if (isLine) {
            double low_point_angle = ((atan2(LEFT_low_y, 90 - LEFT_low_x)) * 180 / 3.1415);
            double up_point_angle = ((atan2(LEFT_up_y, 90 - LEFT_up_x)) * 180 / 3.1415);

            double left_angle = up_point_angle - low_point_angle;
            return left_angle;

        }

    }
    return -1;
}


void LaneDetection::right_upper_point(const cv::Mat &right_frame) {
    RIGHT_up_x = 0;

    for (int i = 0; i < 160; i++) {
        if ((int) right_frame.at<uchar>(RIGHT_up_y, i) > 0) {
            RIGHT_up_x = i;
            break;
        }
    }

}

void LaneDetection::right_lower_point(const cv::Mat &right_frame) {
    RIGHT_low_x = 0;

    for (int i = 0; i < 160; i++) {
        if ((int) right_frame.at<uchar>(RIGHT_low_y, i) > 0) {
            RIGHT_low_x = i;
            break;
        }
    }
    //cout << endl << "low x :" << RIGHT_low_x;

}

bool LaneDetection::check_right_line(const cv::Mat &right_frame) {
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
    //std::cout << "right counter" << true_count << std::endl;

    return true_count > 2;
}

bool LaneDetection::check_left_line(cv::Mat left_frame) {
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
    //std::cout << "left counter" << true_count << std::endl;
    return true_count > 2;
}

void LaneDetection::left_lower_point(cv::Mat left_frame) {
    LEFT_low_x = 0;

    for (int i = 159; i > 0; i--) {
        if ((int) left_frame.at<uchar>(LEFT_low_y, i) > 0) {
            LEFT_low_x = i;
            break;
        }
    }
    // cout << endl << "low x :" << LEFT_low_x;
}

void LaneDetection::left_upper_point(cv::Mat left_frame) {
    LEFT_up_x = 0;

    for (int i = 159; i > 0; i--) {
        if ((int) left_frame.at<uchar>(LEFT_up_y, i) > 0) {
            LEFT_up_x = i;
            break;
        }
    }
    // cout << endl << "LEFT_up_x :" << LEFT_up_x;
}

int LaneDetection::getLeftDirectionCounter() const {
    return left_directionCounter;
}

void LaneDetection::setLeftDirectionCounter(int leftDirectionCounter) {
    left_directionCounter = leftDirectionCounter;
}

int LaneDetection::getRightDirectionCounter() const {
    return rightDirectionCounter;
}

void LaneDetection::setRightDirectionCounter(int rightDirectionCounterInputer) {
    LaneDetection::rightDirectionCounter = rightDirectionCounterInputer;
}


