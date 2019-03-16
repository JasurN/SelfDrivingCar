/////////////////////////////////////////////////////
//Edge_Detection_Using_RaspiCam
/////////////////////////////////////////////////////
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <raspicam/raspicam_cv.h>
using namespace cv;
using namespace std;
int main()
{
    //Initialise the image as a matrix container
    Mat src;
    raspicam::RaspiCam_Cv capture; // initialise the raspicam object
    capture.open(); // activate the raspicam object
    while (1)
    {

    capture.grab(); //grab the scene using raspicam
    capture.retrieve(src); // retrieve the captured scene as an image and store it in matrix container
    Mat gray, edge; //Initialise the matrix container for gray color image, edge image
    cvtColor(src, gray, COLOR_BGR2GRAY); //OpenCV code line for converting COLOR to GRAY scale image
    Canny( gray, edge, 50, 150, 3);
    imshow("Original frame", src); //displaying original frame
    imshow("edge detected frame", edge); //displaying edge detected frame
    if (cvWaitKey(20) == 'q') // waitkey
        break;
    }
capture.release(); // release the raspicam frame grabbing
return 0;
}
