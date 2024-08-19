// GPS.hpp

#ifndef GPS_HPP
#define GPS_HPP

#include "../Config/config.hpp"
#include "Drivers/GPSInterface.hpp" // Include GPSInterface header


#include <vector>
#include <mutex>
#include <memory>
#include <string>
#include <iostream>

class GPS {
public:
    GPS(const std::string& name);

    void updateReadings(); // Updates GPS readings

    std::vector<GPSData> copyLatestData() const;

    const char* getName() const;

private:
    std::vector<GPSData> readings_;
    mutable std::mutex dataMutex_; // Mutex to synchronize access to GPS readings
    std::string name_; // Name of the GPS sensor
    GPSInterface gps_; // GPSInterface member
};

#endif // GPS_HPP
