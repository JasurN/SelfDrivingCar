//Raspian version of LaneDetection

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <raspicam/raspicam_cv.h>

using namespace std;

int main() {

    cv::Mat src;
    raspicam::RaspiCam_Cv capture;

    capture.open();

    while (1) {
        capture.grab();
        capture.retrieve(src);
        resize(src, src, cv::Size(320, 240));
        cv::Rect roi(70, 150, 200, 135);
        cv::Mat src_roi = src(roi);
        cv::Mat dst, cdst;
        Canny(src_roi, dst, 50, 200, 3);
        cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
        vector<cv::Vec4i> lines;
        HoughLinesP(dst, lines, 1, CV_PI / 180, 80, 80, 20);
        for (size_t i = 0; i < lines.size(); i++) {
            cv::Vec4i l = lines[i];
            line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 225), 3, 2);
        }
        imshow("frame", src);
        imshow("LaneDetect", cdst);

        if (cvWaitKey(20) == 'q') // waitkey
        {
            break;
        }
    }

    return 0;
}

//// Compile :
/* g++ LaneDetect_RaspianPorted.cpp -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util `pkg-config --cflags --libs opencv` */