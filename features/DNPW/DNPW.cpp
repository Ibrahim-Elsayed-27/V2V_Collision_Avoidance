//DNPW.cpp

#include "DNPW.hpp"

#include <iostream>


DNPW::DNPW(){}    

bool DNPW::Run_DNPW_Status_Front(){
    static int counter = 0;
    double temp_distance;

    my_lat2 = Latest_R(GPS_Data_Ptr.get(),0).latitude;
    my_lon2 = Latest_R(GPS_Data_Ptr.get(),0).longitude;
    my_lat1 = Latest_R(GPS_Data_Ptr.get(),1).latitude;
    my_lon1 = Latest_R(GPS_Data_Ptr.get(),1).longitude;

    double min_distance_front = std::numeric_limits<double>::max(); 

    

if (counter == 40000 || counter == 0){
    //std::cout<<counter<<std::endl;
    for (const auto& mac_pair : *vehicles_map_ptr) {
        const std::string& mac = mac_pair.first;
        const auto& time_map = mac_pair.second;

            auto last_read = time_map.rbegin();
            const std::string &time = last_read->first;
            const Vehicle  &last_read_vehicle = last_read->second;
            vehicle_front_lat2 = last_read_vehicle.latitude;
            vehicle_front_lon2 = last_read_vehicle.longitude;

            auto prev_read = std::prev(last_read);
            if (prev_read != time_map.rend()) {   // Ensure there is a previous reading
                const std::string &prev_time = prev_read->first;
                const Vehicle &prev_read_vehicle = prev_read->second;
                vehicle_front_lat1 = prev_read_vehicle.latitude;
                vehicle_front_lon1 = prev_read_vehicle.longitude;
            }
            if(isAheadAndSameDirection(my_lat1 ,my_lon1 ,my_lat2 ,my_lon2 ,vehicle_front_lat1 ,vehicle_front_lon1 ,vehicle_front_lat2 ,vehicle_front_lon2)){
                temp_distance = distance(my_lat1,my_lon1,vehicle_front_lat1,vehicle_front_lon1);
                if( temp_distance < min_distance_front){ //to get the nearest front car
                    min_distance_front = temp_distance;
                    distance_FC = temp_distance;
                    vehicle_front_speed = last_read_vehicle.velocity;   //Front vehicole encoder data
                }
            }
    }
    
}



    counter++;
    if (counter > 40000){
        //std::cout<<counter<<"\n\n\n";
        counter=1;
        //std::cout<<counter<<"\n\n\n";
    }
      // write the code that checks the readings and make calculations
    if(distance_FC <  distance_th_Front && vehicle_front_speed <= speed_th_Front){
      return 1;
    }
    else {
      return 0;
    }


      
}

   

bool DNPW::Run_DNPW_Status_Cross(){

    static int counter = 0;
    double temp_distance;
      
    //double time = Latest_R(GPS_Data_Ptr.get(),0).time;
      
    // get GPS data of my vehicle
    my_lat2 = Latest_R(GPS_Data_Ptr.get(),0).latitude;
    my_lon2 = Latest_R(GPS_Data_Ptr.get(),0).longitude;
    my_lat1 = Latest_R(GPS_Data_Ptr.get(),1).latitude;
    my_lon1 = Latest_R(GPS_Data_Ptr.get(),1).longitude;

    double min_distance_opposite = std::numeric_limits<double>::max(); 


if (counter == 40000 || counter == 0){
    // get GPS of Cross vehicle
    for (const auto& mac_pair : *vehicles_map_ptr) {
        const std::string& mac = mac_pair.first;
        const auto& time_map = mac_pair.second;

            auto last_read = time_map.rbegin();
            const std::string &time = last_read->first;
            const Vehicle  &last_read_vehicle = last_read->second;
            vehicle_cross_lat2 = last_read_vehicle.latitude;
            vehicle_cross_lon2 = last_read_vehicle.longitude;
            
            auto prev_read = std::prev(last_read);
            if (prev_read != time_map.rend()) { // Ensure there is a previous reading
                const std::string &prev_time = prev_read->first;
                const Vehicle &prev_read_vehicle = prev_read->second;
                vehicle_cross_lat1 = prev_read_vehicle.latitude;
                vehicle_cross_lon1 = prev_read_vehicle.longitude;
            }

            if(isAheadAndOppositeDirection(my_lat1 ,my_lon1 ,my_lat2 ,my_lon2 ,vehicle_cross_lat1 ,vehicle_cross_lon1 ,vehicle_cross_lat2 ,vehicle_cross_lon2)){
                
                temp_distance = distance(my_lat1,my_lon1,vehicle_cross_lat1,vehicle_cross_lon1);  //calculate distance            }
                if (temp_distance < min_distance_opposite){
                    min_distance_opposite = temp_distance;
                    distance_diff = temp_distance;
                    vehicle_cross_speed = last_read_vehicle.velocity;   //cross vehicole encoder data
                }
            }

    }
}

counter++;
if (counter > 40000) counter=1;
// write the code that checks the readings and make calculations
if((distance_diff <= distance_th_Cross) || ((distance_diff >= distance_th_Cross) && (vehicle_cross_speed >= speed_th_Cross))){
    return 1;
}
else {
    return 0;    
}

}


void DNPW::Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading){
    GPS_Data_Ptr=reading; 
}


void DNPW::Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading){
    vehicles_map_ptr = vehicles_reading;
}
