//#include <cstdio>
//#include <wiringPi.h>
//
//#define LEFT_TRACER_PIN 10
//#define RIGHT_TRACER_PIN 11
//
//int main() {
//    int nLValue = -1, nRValue = -1;
//    if (wiringPiSetup() == -1)
//        return 0;
//
//    pinMode(LEFT_TRACER_PIN, INPUT);
//    pinMode(RIGHT_TRACER_PIN, INPUT);
//
//    while (true) {
//        nLValue = digitalRead(LEFT_TRACER_PIN);
//        nRValue = digitalRead(RIGHT_TRACER_PIN);
//        printf("R = %d, L = %d\n", nRValue, nLValue);
//    }
//    return 0;
//}
