#include <cstdio.h>
#include <wiringPi.h>

#define TRIG_PIN 28
#define ECHO_PIN 29

double getDistance();

int main() {
    if (wiringPiSetup() == -1) {
        return -1;
    }

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    while (true) {
        printf("distance %f cm", getDistance());
        delay(100);
    }
    return 0;
}

double getDistance() {
    int start_time = 0;
    int end_time = 0;
    double distance = 0;

    digitalWrite(TRIG_PIN, LOW);
    delay(500);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    while (digitalRead(ECHO_PIN) == 0);
    start_time = micros();

    while (digitalRead(ECHO_PIN) == 1);
    end_time = micros();

    distance = (end_time - start_time) / 29. / 2.;
    return distance;
}
