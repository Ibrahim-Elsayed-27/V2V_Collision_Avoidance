#include "ENInterface.hpp"
#include <iostream>


// Define static member
volatile int Encoder::encoderCount = 0;

Encoder::Encoder()
    : wheelCircumference(3.141592653589793 * WHEEL_DIAMETER), lastEncoderCount(0) {
    setup();
}

Encoder::~Encoder() {

    gpioTerminate();
    
}

void Encoder::setup() {

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        exit(1);
    }

    gpioSetMode(ENC_A, PI_INPUT);
    gpioSetMode(ENC_B, PI_INPUT);
    gpioSetPullUpDown(ENC_A, PI_PUD_UP);
    gpioSetPullUpDown(ENC_B, PI_PUD_UP);

    // Set up callbacks for encoder pins
    gpioSetAlertFunc(ENC_A, encoderCallback);
    gpioSetAlertFunc(ENC_B, encoderCallback);

    startTime = std::chrono::high_resolution_clock::now();
    
}

void Encoder::encoderCallback(int gpio, int level, uint32_t tick) {

    if (gpio == ENC_A) {
        if (gpioRead(ENC_A) == gpioRead(ENC_B)) {
            encoderCount++;
        } else {
            encoderCount--;
        }
    } else if (gpio == ENC_B) {
        if (gpioRead(ENC_A) != gpioRead(ENC_B)) {
            encoderCount++;
        } else {
            encoderCount--;
       }
    }
    
}

double Encoder::getSpeed() {

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;

    int count = encoderCount - lastEncoderCount;
    double revolutions = count / PULSES_PER_REVOLUTION;
    double revolutionsPerSecond = revolutions / elapsedSeconds.count();
    double speedMps = revolutionsPerSecond * wheelCircumference;

    std::cout << "rpm: " << revolutionsPerSecond << std::endl;
    std::cout << "Speed: " << speedMps << " m/s" << std::endl;


    startTime = endTime;
    lastEncoderCount = encoderCount;

    return speedMps;
    
}


/*
int main() {
    // Create an Encoder object
    Encoder encoder;

    while (true) {
        // Wait for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Get the speed in meters per second
        double speed = encoder.getSpeed();

        // Print the speed
        std::cout << "Speed: " << speed << " m/s" << std::endl;
    }

    return 0;
}
*/