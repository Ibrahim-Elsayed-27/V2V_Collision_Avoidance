#ifndef VEHICLE_HPP
#define VEHICLE_HPP


#include <map>


struct Vehicle {
    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    double acc_x = 0.0;
    double acc_y = 0.0;
    double acc_z = 0.0;
    double velocity = 0.0;

    // Default constructor initializes all members to default values
    Vehicle() = default;
};

#endif