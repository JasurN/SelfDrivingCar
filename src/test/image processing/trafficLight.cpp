//////////////////////////////////////////////////////
//Raspian version of Red & Green Light identification
//Range of RED: 170~180
//Range of GREEN: 38~75
/////////////////////////////////////////////////////
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <raspicam/raspicam_cv.h>

int main()
{

	cv::Mat3b bgr;
	raspicam::RaspiCam_Cv capture;

	capture.open();

	while (true)
	{
		capture.grab();
		capture.retrieve(bgr);
        cv::Mat3b hsv;
		cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);

        cv::Mat1b mask1, mask2;
		inRange(hsv, cv::Scalar(173, 70, 50), cv::Scalar(179, 255, 255), mask1);
		inRange(hsv, cv::Scalar(38, 70, 50), cv::Scalar(75, 255, 255), mask2);
		imshow("Original", bgr);
		imshow("RedDetect", mask1);
		imshow("GreenDetect", mask2);
		if (cvWaitKey(20) == 'q')
			break;
	}
	capture.release();
	return 0;
}

//// Compile :
/* g++ trafficLightDetect_RaspianPorted.cpp -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util `pkg-config --cflags --libs opencv` */