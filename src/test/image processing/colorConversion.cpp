////////////////////////////////////////////////////////
////Color_Conversion_Using_RaspiCam
///////////////////////////////////////////////////////
//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <raspicam/raspicam_cv.h>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//
//    //Initialise the image as a matrix container
//    Mat bgr;
//    raspicam::RaspiCam_Cv capture; // initialise the raspicam object
//
//    capture.open(); // activate the raspicam object
//
//    while (1) {
//        capture.grab(); //grab the scene using raspicam
//        capture.retrieve(bgr); // retrieve the captured scene as an image and store it in matrix container
//        Mat gray; //Initialise the matrix container for gray color image
//        cvtColor(bgr, gray, COLOR_BGR2GRAY); //OpenCV code line for converting COLOR to GRAY scale image
//        Mat hsv; //Initialise the matrix container for hsv color image
//        cvtColor(bgr, hsv, COLOR_BGR2HSV); //OpenCV code line for converting COLOR to HSV scale image
//
//        //TO DO: HOMEWORK
//        //1. Write the code to convert RGB --> YCrCb
//        //2. Write the code to convert RGB --> HSV and take that HSV --> GRAY [Is this possible: If Yes --> do it]
//        //3. Write the code to convert RGB --> GRAY and ttake that GRAY --> HSV [Is this possible: If Yes --> do it]
//
//        //TO DO: HOMEWORK
//        //Write the code to display the above 1,2,3 OUTPUTS
//
//        imshow("Original RGB frame", bgr);//displaying original frame
//        imshow("Gray scale converted frame", gray);//displaying Gray scale converted frame
//        imshow("HSV converted frame", hsv);//displaying HSV converted frame
//
//        if (cvWaitKey(20) == 'q') // waitkey
//            break;
//    }
//    capture.release(); // release the raspicam frame grabbing
//    return 0;
//}
//
////// Compile using the below command :
///* g++ Color_Conversion_Using_RaspiCam.cpp -o opencv_color_convert -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util `pkg-config --cflags --libs opencv` */
//
