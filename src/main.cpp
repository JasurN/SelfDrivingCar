#include <raspicam/raspicam_cv.h>
#include "LaneDetection.h"
#include "MotorControl.h"
#include <pthread.h>
#include <signal.h>

MotorControl motorControl;
LaneDetection laneDetection;


void *leftLaneTurnThread(void *threadarg);

void *rightLaneTurnThread(void *threadarg);

void *irLineTracerThread(void *threadarg);

void my_handler(int s);

void ctrl_c_stop_motor_signal_handler();

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

    pthread_t pthreads[2];
//    src = cv::imread("../12.png");
//    resize(src, src, cv::Size(320, 240));

    //motorControl.goForward();
    motorControl.setMotorGoing(true);
    motorControl.setMotorGoingForward(true);
    ctrl_c_stop_motor_signal_handler();

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
        //left turn thread
//        if(laneDetection.getLeftDirectionCounter() >= 3
//           && !motorControl.isMotorGoingLeft()) {
//            motorControl.setMotorGoingLeft(true);
//            laneDetection.setLeftDirectionCounter(0);
//            int left_thread_result = pthread_create(&pthreads[0], nullptr, leftLaneTurnThread, (void *) 1);
//            if (left_thread_result) {
//                std::cout << "Error:unable to create left go thread," << left_thread_result << std::endl;
//            }
//            //right turn thread
//        } else if (laneDetection.getRightDirectionCounter() >= 3) {
//            laneDetection.setRightDirectionCounter(0);
//            int right_thread_result = pthread_create(&pthreads[0], nullptr, rightLaneTurnThread, (void *) 2);
//            if (right_thread_result) {
//                std::cout << "Error:unable to create right go thread," << right_thread_result << std::endl;
//            }
//        }

        int ir_line_thread_result = pthread_create(&pthreads[0], nullptr, irLineTracerThread, (void *) 3);
        if (ir_line_thread_result) {
            std::cout << "Error:unable to create left go thread," << ir_line_thread_result << std::endl;
        }
        imshow("full", dst);
        imshow("left", left_frame);
        imshow("right", right_frame);
        //cvWaitKey(200000);
        if (cvWaitKey(20) == 'q') // waitkey
        {
            motorControl.stop();
            capture.release();
            break;
        }
    }
}
//left line thread
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void *leftLaneTurnThread(void *threadarg) {
    std::cout << "turn left thread" << std::endl;
    motorControl.setMotorGoingForward(false);
    motorControl.setMotorGoingLeft(true);
    delay(400);
    motorControl.goCurve(50, 0);
    delay(1000);
    motorControl.setMotorGoingForward(true);
    motorControl.setMotorGoingLeft(false);
    motorControl.stop();
    delay(100);
    motorControl.goForward();

}

#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void *irLineTracerThread(void *threadarg) {
    int left_ir_tracer, right_ir_tracer;
    left_ir_tracer = digitalRead(LEFT_TRACER_PIN);
    right_ir_tracer = digitalRead(RIGHT_TRACER_PIN);
    while (true) {
        if (left_ir_tracer == 0 && right_ir_tracer == 1
            && !motorControl.turningIrLeft) {
            motorControl.turningIrLeft = true;
            std::cout << "go left" << std::endl;
            motorControl.goCurve(0, 50);
            delay(400);
            motorControl.goForward();
            motorControl.turningIrLeft = false;

        } else if (left_ir_tracer == 1 && right_ir_tracer == 0
                   && !motorControl.turningIrRight) {
            motorControl.turningIrRight = true;
            std::cout << "go right" << std::endl;
            motorControl.goCurve(50, 0);
            delay(400);
            motorControl.goForward();
            motorControl.turningIrRight = false;

        } else if (left_ir_tracer == 0 && right_ir_tracer == 0) {
            std::cout << "zebra" << std::endl;
        }
        printf("L = %d, R = %d\n", left_ir_tracer, right_ir_tracer);
        delay(10);
    }
}

#pragma clang diagnostic pop

//right left thread
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void *rightLaneTurnThread(void *threadarg) {
    std::cout << "turn right thread" << std::endl;
    motorControl.setMotorGoingForward(false);
    motorControl.setMotorGoingRight(true);
    delay(800);
    motorControl.goCurve(0, 50);
    delay(1000);
    motorControl.setMotorGoingForward(true);
    motorControl.setMotorGoingRight(false);
    motorControl.stop();
    delay(100);
    motorControl.goForward();
}

#pragma clang diagnostic pop

void my_handler(int s) {
    printf("Caught signal %d\n", s);
    motorControl.stop();
    exit(1);

}

void ctrl_c_stop_motor_signal_handler() {
    struct sigaction sigIntHandler{};

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);
}
