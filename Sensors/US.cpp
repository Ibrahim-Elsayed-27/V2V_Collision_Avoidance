// US.cpp

#include "US.hpp"

US::US(const std::string& name, int trigPin, int echoPin)
    : ultrasonicsensor(trigPin, echoPin), name_(name), readings_(US_V_length, US_init_D) {
    }


void US::updateReadings() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    // (dummy value for now) // driver will be used here
    
    USData read_data ;
    //read_data.distance = ultrasonicsensor.getUltrasonicDistance();
    std::cout << "US.cpp -> "<< name_ << " distance: " << read_data.distance  << std::endl;
    

      
    // Ensure we only keep the last 5 readings
    if (readings_.size() > US_V_length) {
        readings_.erase(readings_.begin());
    }
    readings_.push_back(read_data);
}

std::vector<USData> US::copyLatestData() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    return readings_;
}

const char* US::getName() const {
    return name_.c_str();
}
