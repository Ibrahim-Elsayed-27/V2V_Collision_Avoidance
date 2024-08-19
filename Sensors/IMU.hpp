// IMU.hpp

#ifndef IMU_HPP
#define IMU_HPP

#include "../Config/config.hpp"
#include "Drivers/IMUinterface.hpp" // Include MPU6050 header

#include <vector>
#include <mutex>
#include <memory>
#include <string>

class IMU  {
public:
    IMU(const std::string& name);

    void updateReadings(); // Updates IMU readings

    std::vector<IMUData> copyLatestData() const;

    const char* getName() const ;

private:
    MPU6050 mpu6050; // Private member of type MPU6050
    std::string name_; // Name of the IMU sensor
    std::vector<IMUData> readings_;
    mutable std::mutex dataMutex_; // Mutex to synchronize access to IMU readings
    
};

#endif // IMU_HPP
