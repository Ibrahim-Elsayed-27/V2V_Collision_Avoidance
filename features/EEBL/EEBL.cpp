//EEBL.cpp

#include "EEBL.hpp"

#include <iostream>


EEBL::EEBL(){}


bool EEBL::Run_EEBL_Controller1(){
    MyLat2 = Latest_R(GPS_Data_Ptr.get(),0).latitude;
    MyLong2 = Latest_R(GPS_Data_Ptr.get(),0).longitude;
    MyLat = Latest_R(GPS_Data_Ptr.get(),1).latitude;
    MyLong = Latest_R(GPS_Data_Ptr.get(),1).longitude;
    speed_ENR = Latest_R(ENR_Data_Ptr.get(),0).speed;
    bool ahead_check=0;
    bool controller1_check=0;
    for (const auto& mac_pair : *vehicles_map_ptr) {
        const auto& time_map=mac_pair.second;

            auto last_read = time_map.rbegin();
            const Vehicle &last_read_data=last_read->second;
            VLat2=last_read_data.latitude;
            VLong2=last_read_data.longitude;
            
            auto before_last = std:: prev(time_map.rbegin());
            const Vehicle &before_last_data=before_last->second;
            VLat=before_last_data.latitude;
            VLong=before_last_data.longitude;
            
    
        ahead_check = isAheadAndSameDirection(MyLat, MyLong, MyLat2, MyLong2, VLat, VLong, VLat2, VLong2);
        std::cout << "ahead check" << ahead_check<<std::endl;
        if(ahead_check){
            if(last_read_data.acc_y < -20 || abs(speed_ENR - last_read_data.velocity) > 30){
                controller1_check = 1;
                std::cout << "eebl check" << controller1_check<<std::endl;
                break;
            }
        }
        
    }
    return controller1_check;
    
}


void EEBL::Update_EN_Data(std::shared_ptr<std::vector<ENData>> reading){
    ENR_Data_Ptr=reading; 
}

 void EEBL::Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading){
    GPS_Data_Ptr=reading; 
}


void EEBL::Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading){
    vehicles_map_ptr = vehicles_reading;
}