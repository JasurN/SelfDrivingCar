#include "MotorControl.h"
#include <iostream>
#include <wiringPi.h>
void testDelay();
MotorControl motorControl;
int main() {
    testDelay();
    return 0;
}

void testDelay() {
    int delayTime = 0;
    std::cin >> delayTime;
    motorControl.goCurve(50, 0);
    delay(delayTime);
    motorControl.stop();
    testDelay();
}