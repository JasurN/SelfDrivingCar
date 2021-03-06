cmake_minimum_required(VERSION 3.7.2)
project(SelfDrivingCar)

set(HEADER_FILES ${/usr/local/include})

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_PREFIX_PATH)
set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES "src/test/image processing/edgeDetection.cpp"
        "src/test/image processing/trafficLight.cpp" src/test/hardware/motorControl.cpp src/test/hardware/motorSpeedControl.cpp
        src/test/hardware/IR_sensor.cpp src/test/hardware/IR_line_tracer.cpp src/test/hardware/ultrasonic.cpp
        "src/test/image processing/colorConversion.cpp" "src/test/image processing/shapeDetection.cpp"
        src/test/hmw3/task1.cpp src/test/util/tangent_angle.cpp "src/test/image processing/zebraPatern.cpp" "src/test/image processing/trafficLight.cpp"
        src/test/util/imageAnalyse.cpp src/LandeBasedDetection.cpp
        src/test/util/test.cpp
        src/MotorControl.cpp src/MotorControl.h src/LaneDetection.h src/LaneDetection.cpp src/test/util/thread.cpp src/test/hardware/working_ir.cpp src/test/util/delayCheck.cpp src/cascade/cascade.cpp src/main.cpp)
add_executable(SelfDrivingCar ${SOURCE_FILES} )
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(SelfDrivingCar ${OpenCV_LIBS} )
target_link_libraries(SelfDrivingCar -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
        -lopencv_core -lraspicam -lraspicam_cv -lwiringPi -lcrypt -lpthread)