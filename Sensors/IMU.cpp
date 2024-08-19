// IMU.cpp

#include "IMU.hpp"

IMU::IMU(const std::string& name)
    : mpu6050(0x68), name_(name), readings_(IMU_V_length, IMU_init_D) {
    }


void IMU::updateReadings() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    // Read accelerometer data from MPU6050
    data = mpu6050.readAccelData();

    // Push the read struct into the readings vector

    std::cout << "IMU.cpp -> AccX  " << data.AccX  << std::endl;
    std::cout << "IMU.cpp -> AccY  " << data.AccY  << std::endl;
    std::cout << "IMU.cpp -> AccZ  " << data.AccZ  << std::endl;
     
    readings_.push_back(data);

    // Ensure we only keep the last 5 readings
    if (readings_.size() > IMU_V_length) {
        readings_.erase(readings_.begin());
    }
}

std::vector<IMUData> IMU::copyLatestData() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    return readings_;
}

const char* IMU::getName() const {
    return name_.c_str();
}
