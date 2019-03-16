cmake_minimum_required(VERSION 3.7.2)
project(SelfDrivingCar)

set(HEADER_FILES ${/usr/local/include})

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_PREFIX_PATH)
set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES src/main.cpp src/test/edgeDetection.cpp src/test/lineDetection.cpp
        src/test/trafficLight.cpp src/test/motorControl.cpp src/test/motorSpeedControl.cpp
        src/test/IR_sensor.cpp src/test/IR_line_tracer.cpp src/test/ultrasonic.cpp)
add_executable(SelfDrivingCar ${SOURCE_FILES} )
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(SelfDrivingCar ${OpenCV_LIBS} )
target_link_libraries(SelfDrivingCar -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
        -lopencv_core -lraspicam -lraspicam_cv -lwiringPi)