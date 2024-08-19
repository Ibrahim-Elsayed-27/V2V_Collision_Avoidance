//DNPW.hpp


#ifndef DNPW_HPP
#define DNPW_HPP


#include "../../Config/config.hpp"
#include "../../Sensors/GPS.hpp"
#include "../../Sensors/US.hpp"
#include "../../comm_manager/vehicle.hpp"
#include "../../lib/lib.hpp"

// "ENL", "ENR", "GPS", "IMU", "US_FC", "US_FL", "US_FR", "US_RC", "US_RL", "US_RR"

class DNPW {
public:
    DNPW();

    // GPS data Consumer
    void Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading);


    void Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading);

    bool Run_DNPW_Status_Front(); 
    bool Run_DNPW_Status_Cross(); 

    double distance_FC;

private: 
    // local GPS data
    double my_lat1 ,my_lon1 ,my_lat2 ,my_lon2;
    std::string time;

    // local GPS data ptr
   std::shared_ptr<std::vector<GPSData>> GPS_Data_Ptr;  
  

    



    std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_map_ptr; 

   double distance_th_Front = 60;  // [cm]
   double speed_th_Front = 40; //  [m/s]

   double distance_th_Cross = 0; // [cm]
   double speed_th_Cross = 65; //  [m/s]

   double vehicle_front_speed;

   double vehicle_front_lat1; 
   double vehicle_front_lon1;
   double vehicle_front_lat2; 
   double vehicle_front_lon2;

   double vehicle_cross_speed;
   double distance_diff;

   double vehicle_cross_lat1; 
   double vehicle_cross_lon1;
   double vehicle_cross_lat2; 
   double vehicle_cross_lon2;

};

#endif // DNPW_HPP



