#include "USinterface.hpp"

volatile int UltrasonicSensor::lastRange = 0; // Definition outside guard

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin) {
    
    trigPin_ = trigPin;
    echoPin_ = echoPin;

    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize GPIO" << std::endl;
        throw std::runtime_error("GPIO initialization failed");
    }

    gpioSetMode(trigPin_, PI_OUTPUT);
    gpioSetMode(echoPin_, PI_INPUT);

    // Register callback for echo pin
    gpioSetAlertFunc(echoPin_, &UltrasonicSensor::echoCallback);
    
}

UltrasonicSensor::~UltrasonicSensor() {
    
    gpioTerminate();
    
}

int UltrasonicSensor::getUltrasonicDistance() {
    
    // Trigger a measurement
    gpioWrite(trigPin_, PI_OFF);
    usleep(5);
    gpioWrite(trigPin_, PI_ON);
    usleep(10);
    gpioWrite(trigPin_, PI_OFF);

    // Wait for the echo response
    usleep(5000);  // 10ms(3.4 meter) (adjust as needed) 

    // Get the distance measured by the sensor
    return getDistance();
    
}

void UltrasonicSensor::echoCallback(int gpio, int level, uint32_t tick) {
    
    static uint32_t startTick;
    uint32_t diffTick;

    if (level == PI_ON) {
        startTick = tick;
    } else if (level == PI_OFF) {
        diffTick = tick - startTick;
        lastRange = diffTick / 58;  // Convert tick difference to distance in cm
    }
    
}

int UltrasonicSensor::getDistance() const {
    
    return lastRange;
    
}

/*
int main(){
return 0;
}*/