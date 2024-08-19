#ifndef GPSINTERFACE_HPP
#define GPSINTERFACE_HPP

#include <string>
#include "../../Config/config.hpp"


class GPSInterface {
public:
    GPSInterface(const char* device, int baudrate);
    ~GPSInterface();
    GPSData getGPSData();

private:
    int setup_serial(const char* device, int baudrate);
    bool parse_gps(const std::string& line, double& latitude, double& longitude, double& altitude, std::string& time);

    int fd_;
};

#endif // GPSINTERFACE_HPP