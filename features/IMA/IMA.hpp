//IMA.hpp

#ifndef IMA_HPP
#define IMA_HPP

#include "../../lib/lib.hpp"
#include "../../Config/config.hpp"
#include "../../Sensors/GPS.hpp"
#include "../../comm_manager/vehicle.hpp"

#define ALT_THRESH 5

struct IMA_CARS
{
    std :: string drirection;
    double distance ;
};


class IMA {
public:
    IMA();
    // GPS data Consumer
    void Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading);
    void Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading);
    bool Run_IMA_Controller1(); 
    IMA_CARS Run_IMA_Controller2();
    

    
    
private:


    // local GPS and vehicle data
    double MyLat ,MyLong,MyAlt ,MyLat2 ,MyLong2 ,VLat,VLat2,VLong,VLong2,VAlt;
    
    // local GPS data ptr
    std::shared_ptr<std::vector<GPSData>> GPS_Data_Ptr; 
    // local vehicle data ptr 
    std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_map_ptr; 

    std::map<double ,std::string> imaMap;

    IMA_CARS  is_ima(double latA_1,double lonA_1,double latA_2,double lonA_2,double latB_1,double lonB_1,double latB_2,double lonB_2) ;



};

#endif // IMA_HPP