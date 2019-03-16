//#include <cstdio>
//#include <wiringPi.h>
//
//#define IN1_PIN 1
//#define IN2_PIN 4
//#define IN3_PIN 5
//#define IN4_PIN 6
///**
//#define MOTOR_INIT digitalWrite(1, HIGH); digitalWrite(4,HIGH); digitalWrite(5, HIGH); digitalWrite(6,HIGH)
//#define MOTOR_GO_FORWARD digitalWrite(1,HIGH); digitalWrite(4,LOW); digitalWrite(5,HIGH); digitalWrite(6,LOW)
//#define MOTOR_GO_BACK digitalWrite(4,HIGH); digitalWrite(1,LOW); digitalWrite(6,HIGH); digitalWrite(5,LOW)
//#define MOTOR_GO_RIGHT #define MOTOR_GO_LEFT digitalWrite(4,HIGH); digitalWrite(1,LOW); digitalWrite(5,HIGH); digitalWrite(6,LOW)
//#define MOTOR_GO_STOP digitalWrite(1, LOW); digitalWrite(4,LOW); digitalWrite(5, LOW); digitalWrite(6,LOW)
//digitalWrite(1,HIGH); digitalWrite(4,LOW); digitalWrite(6,HIGH); digitalWrite(5,LOW)
//*/
//
//int gCnt = 3;
//
//
//
//void initDCMotor();
//
//void goForward();
//
//void goBackward();
//
//void goLeft();
//
//void goRight();
//
//void stopDCMotor();
//
//
//int main(void) {
//    if (wiringPiSetup() == -1)
//        return 0;
//    pinMode(IN1_PIN, OUTPUT);
//    pinMode(IN2_PIN, OUTPUT);
//    pinMode(IN3_PIN, OUTPUT);
//    pinMode(IN4_PIN, OUTPUT);
//    initDCMotor();
//    while (gCnt > 0) {
//        goLeft();
//        delay(500);
//        goLeft();
//        delay(500);
//        stopDCMotor();
//        gCnt--;
//    }
//    return 0;
//}
//
//void initDCMotor() {
//    digitalWrite(IN1_PIN, HIGH);
//    digitalWrite(IN2_PIN, HIGH);
//    digitalWrite(IN3_PIN, HIGH);
//    digitalWrite(IN4_PIN, HIGH);
//}
//
//void goForward() {
//    digitalWrite(IN1_PIN, HIGH);
//    digitalWrite(IN2_PIN, LOW);
//    digitalWrite(IN3_PIN, HIGH);
//    digitalWrite(IN4_PIN, LOW);
//    printf("Forward\n");
//}
//
//void goBackward() {
//    digitalWrite(IN1_PIN, LOW);
//    digitalWrite(IN2_PIN, HIGH);
//    digitalWrite(IN3_PIN, LOW);
//    digitalWrite(IN4_PIN, HIGH);
//    printf("Back\n");
//}
//
//void goLeft() {
//    digitalWrite(IN1_PIN, LOW);
//    digitalWrite(IN2_PIN, HIGH);
//    digitalWrite(IN3_PIN, HIGH);
//    digitalWrite(IN4_PIN, LOW);
//    printf("Left\n");
//}
//
//void goRight() {
//    digitalWrite(IN1_PIN, HIGH);
//    digitalWrite(IN2_PIN, LOW);
//    digitalWrite(IN3_PIN, LOW);
//    digitalWrite(IN4_PIN, HIGH);
//    printf("Right\n");
//}
//
//void stopDCMotor() {
//    digitalWrite(IN1_PIN, LOW);
//    digitalWrite(IN2_PIN, LOW);
//    digitalWrite(IN3_PIN, LOW);
//    digitalWrite(IN4_PIN, LOW);
//    printf("Stop\n");
//}
//
//
//
//
//
//
//
//
//
//
//
//
