//EEBL.hpp

#ifndef EEBL_HPP
#define EEBL_HPP

#include "../../lib/lib.hpp"

#include "../../Config/config.hpp"
#include "../../Sensors/EN.hpp"
#include "../../Sensors/GPS.hpp"
#include "../../comm_manager/vehicle.hpp"

//"ENL", "ENR", "GPS".

class EEBL {
public:
    EEBL();

    void Update_EN_Data(std::shared_ptr<std::vector<ENData>> reading);
    void Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading);
    void Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading);

    bool Run_EEBL_Controller1(); 

    
private:


    // local GPS data
    double MyLat ,MyLong ,MyLat2 ,MyLong2 ,VLat,VLat2,VLong,VLong2,speed_ENR;
    std::string time;

    // local Encoder data ptr
    std::shared_ptr<std::vector<ENData>> ENR_Data_Ptr; 

    // local GPS data ptr
    std::shared_ptr<std::vector<GPSData>> GPS_Data_Ptr; 

    // local vehicles data ptr
    std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_map_ptr; 


};

#endif // EEBL_HPP