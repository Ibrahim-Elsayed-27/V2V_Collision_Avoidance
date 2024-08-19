#include "EN.hpp"

EN::EN()
    : readings_(EN_V_length, {EN_init_D}), encoder_() {
    
}

void EN::updateReadings() {
    std::lock_guard<std::mutex> lock(dataMutex_);

    // Get the latest speed from the encoder
    double speed = encoder_.getSpeed();

    std::cout << "EN.cpp -> " << " speed: " << speed  << "m/s  "<< std::endl;

    // Create an ENData struct with the speed
    ENData data{speed};

    // Add the new reading to the vector
    readings_.push_back(data);

    // Ensure we only keep the last 5 readings
    if (readings_.size() > EN_V_length) {
        readings_.erase(readings_.begin());
    }
}

std::vector<ENData> EN::copyLatestData() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    return readings_;
}

const char* EN::getName() const {
    return name_.c_str();
}
