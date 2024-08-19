#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include <mutex>
#include <memory>
#include <string>

#include "UltrasonicPins.hpp"

#define GPS_V_length  5
#define US_V_length   5
#define EN_V_length   5
#define IMU_V_length  5

#define Latest_R(vec, offset) ((vec)->at((vec)->size() - 1 - (offset)))

#define GPS_init_D  {0.0, 0.0 ,0.0,"15:32:55"}

#define US_init_D   {0}

#define EN_init_D   {0.0}

#define IMU_init_D  {0, 0, 0}


struct GPSData {
    double latitude, longitude,altitude;
    std::string time;
};


struct IMUData{
float AccX, AccY, AccZ;
};

struct USData {
     double distance;
   };


#endif