#include <raspicam/raspicam_cv.h>
#include "LaneDetection.h"

int main() {

    raspicam::RaspiCam_Cv capture;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capture.open();

    LaneDetection laneDetection;

    cv::Rect full_roi(0, 150, 320, 90);
    cv::Rect left_roi(0, 0, 160, 90);
    cv::Rect right_roi(160, 0, 160, 90);
    cv::Mat src;
    cv::Mat src_roi;
    cv::Mat dst;
    cv::Mat left_frame, right_frame;

//    src = cv::imread("../12.png");
//    resize(src, src, cv::Size(320, 240));
    while (true) {
        capture.grab();
        capture.retrieve(src);
        src_roi = src(full_roi);
        cvtColor(src_roi, src_roi, cv::COLOR_BGR2GRAY);
        GaussianBlur(src_roi, src_roi, cv::Size(5, 5), 0);
        Canny(src_roi, dst, 50, 200, 3);

        left_frame = dst(left_roi);
        right_frame = dst(right_roi);

        laneDetection.directionPrediction(laneDetection.left_angle_find(left_frame),
                                          laneDetection.right_angle_find(right_frame));
        imshow("full", dst);
        imshow("left", left_frame);
        imshow("right", right_frame);
        //cvWaitKey(200000);
        if (cvWaitKey(20) == 'q') // waitkey
        {
            capture.release();
            break;
        }
    }


}


