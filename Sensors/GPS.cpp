// GPS.cpp

#include "GPS.hpp"

GPS::GPS(const std::string& name)
    : readings_(GPS_V_length, GPS_init_D), name_(name), gps_("/dev/ttyS0", 9600) {

}

void GPS::updateReadings() {
    //GPSData data ;
    data = gps_.getGPSData(); // Fetch GPS data using GPSInterface
    
    std::cout << "GPS.cpp(updateReadings) ->  Latitude: " << data.latitude << ", Longitude: " << data.longitude << ", Time: " << data.time << std::endl;

    if (!data.time.empty()) {
        if (data.latitude != 0.0 || data.longitude != 0.0) { // Check if data was successfully read
            std::lock_guard<std::mutex> lock(dataMutex_);
            readings_.push_back(data);
        
            // Ensure we only keep the last 5 readings
            if (readings_.size() > GPS_V_length) {
                readings_.erase(readings_.begin());
            }
        } else {
            std::cout << "read not successful" << std::endl;
        }
    }
}




std::vector<GPSData> GPS::copyLatestData() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    //std::cout << "GPS.cpp(copyLatestData) -> latitude: " << readings_.back().latitude<< ", Longitude: " << readings_.back().longitude << ", Time: " << readings_.back().time << std::endl;
    return readings_;
}

const char* GPS::getName() const {
    return name_.c_str();
}
