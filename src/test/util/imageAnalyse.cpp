////Raspian version of LaneDetection
//
//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <raspicam/raspicam_cv.h>
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int raspberry = false;
//
//int main() {
//    //raspicam::RaspiCam_Cv capture;
////    VideoCapture cap(0);
////
////    if (raspberry) {
//////        capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
//////        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
//////        capture.open();
////    } else {
////        cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
////        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
////    }
//
//
//    cv::Rect full_roi(0, 150, 320, 90);
//    cv::Rect left_roi(0, 0, 160, 90);
//    cv::Rect right_roi(160, 0, 160, 90);
//    cv::Mat src;
//    cv::Mat src_roi;
//    cv::Mat dst;
//    cv::Mat left_frame, right_frame;
////    while (1) {
////        if (raspberry) {
////            capture.grab();
////            capture.retrieve(src);
////        } else {
////
////        }
//    // cap >> src;
//    //src = imread("../12.png");
//    //resize(src, src, cv::Size(320, 240));
//    src = imread("../12.png");
//    resize(src, src, cv::Size(320, 240));
//
//    src_roi = src(full_roi);
//    cvtColor(src_roi, src_roi, COLOR_BGR2GRAY);
//    GaussianBlur(src_roi, src_roi, Size(5, 5), 0);
//    Canny(src_roi, dst, 50, 200, 3);
//    left_frame = dst(left_roi);
//    right_frame = dst(right_roi);
//    //cvtColor(dst, cdst, cv::COLOR_GRAY2BGR);
////    vector<cv::Vec4i> lines;
////    HoughLinesP(dst, lines, 1, CV_PI / 180, 80, 50, 20);
////    for (size_t i = 0; i < lines.size(); i++) {
////        cv::Vec4i l = lines[i];
////        line(cdst, cv::Pointleft_frame = dst(left_roi);
//    right_frame = dst(right_roi);
////    }
//    //imshow("frame", src);
//    imshow("Canny 200", dst);
//    imshow("Left Frame", left_frame);
//    imshow("Right Frame", right_frame);
////first point
//        int i = 30;
//        for (int j = 0; j < 160; j++) {
//            if((int)left_frame.at<uchar>(i, j) > 0)
//                cout <<"i: "<< i  << " j:"<< j<<endl;
//                //cout << (int)left_frame.at<uchar>(i, j) <<":";
//        }
//        cout<<endl;
//
//
//    cvWaitKey(200000);
////        if (cvWaitKey(20) == 'q') // waitkey
////        {
//////            if (raspberry) {
//////                capture.release();
//////            }
////
////            break;
////        }
////    }
//
//    return 0;
//}
