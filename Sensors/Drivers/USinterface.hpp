#ifndef USINTERFACE_HPP
#define USINTERFACE_HPP

#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <stdexcept>

//#define TRIG 0  // GPIO pin for trigger
//#define ECHO 1  // GPIO pin for echo

class UltrasonicSensor {
public:
    UltrasonicSensor(int trigPin, int echoPin); // Constructor with pin arguments
    ~UltrasonicSensor();
    int getUltrasonicDistance();

private:
    static void echoCallback(int gpio, int level, uint32_t tick);
    int getDistance() const;
    static volatile int lastRange;

    int trigPin_; // Private member to store trigger pin
    int echoPin_;  // Private member to store echo pin
};

#endif // USINTERFACE_HPP
