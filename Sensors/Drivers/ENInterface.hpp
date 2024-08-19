#ifndef ENINTERFACE_HPP
#define ENINTERFACE_HPP

#include <pigpio.h>
#include <chrono>
#include <thread>

// Define GPIO pins and wheel properties
#define ENC_A 27
#define ENC_B 24
#define WHEEL_DIAMETER 0.065 // 10 cm diameter wheel
#define PULSES_PER_REVOLUTION 11.0

class Encoder {
public:
    Encoder();
    ~Encoder();

    void setup();
    double getSpeed();

private:
    static void encoderCallback(int gpio, int level, uint32_t tick);

    double wheelCircumference;

    static volatile int encoderCount;
    std::chrono::high_resolution_clock::time_point startTime;
    int lastEncoderCount;
};

#endif // ENINTERFACE_HPP
