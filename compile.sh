#!/bin/bash
# Script to compile OpenCv c++ file. Pass file name as first argument.

g++ $1 -I/usr/local/include -L/usr/local/lib -L/opt/vc/lib  -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lraspicam -lraspicam_cv -lwiringPi -lpthread `pkg-config --cflags --libs opencv`
