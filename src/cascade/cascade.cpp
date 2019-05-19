#include <opencv2/core.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <raspicam/raspicam_cv.h>

using namespace cv;
using namespace std;

int main() {
    raspicam::RaspiCam_Cv capture;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capture.open();
    //Initialise the image as a matrix container
    Mat bgr;
    // Initialise the cascade classifier containers and load them with the .xml file you obtained from the training
    CascadeClassifier cascade_becareful, cascade_circle, cascade_left,
            cascade_stop, cascade_parking, cascade_right, cascade_forward;
    cascade_becareful.load("cas_becareful.xml");
    cascade_circle.load("cas_circle.xml");
    cascade_left.load("cas_left.xml");
    cascade_stop.load("cas_stop.xml");
    cascade_parking.load("cas_parking.xml");
    cascade_right.load("cas_right.xml");
    cascade_forward.load("cas_forward.xml");



    // Container of signs
    vector<Rect> becareful;
    vector<Rect> circle;
    vector<Rect> left_;
    vector<Rect> stop_;
    vector<Rect> parking;
    vector<Rect> right_;
    vector<Rect> forward;
    while (1) {
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
        for (const auto & i : becareful)
            rectangle(bgr, i, Scalar(255, 0, 0), 2, 1);

//        for (const auto & j : circle)
//            rectangle(bgr, j, Scalar(255, 0, 0), 2, 1);
//
//        for (const auto & k : left_)
//            rectangle(bgr, k, Scalar(255, 0, 0), 2, 1);

        for (const auto & l : stop_)
            rectangle(bgr, l, Scalar(255, 255, 255), 2, 1);

//        for (const auto & m : parking)
//            rectangle(bgr, m, Scalar(255, 0, 0), 2, 1);
//
//        for (const auto & n : right_)
//            rectangle(bgr, n, Scalar(255, 0, 0), 2, 1);

//        for (const auto & o : forward)
//            rectangle(bgr, o, Scalar(255, 0, 0), 2, 1);

        imshow("original", bgr);

        if (cvWaitKey(20) == 'q') // waitkey
        {
            capture.release();
            break;
        }

    }
    // release the raspicam frame grabbing

    return 0;
}


//// Compile :
/* g++ cascade_based_traffic_sign_raspicam.cpp -o cascade_based_traffic_signs -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib
-lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util `pkg-config --cflags --libs opencv` */



