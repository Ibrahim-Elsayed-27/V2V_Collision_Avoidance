//IMA.cpp

#include "IMA.hpp"

#include <iostream>


IMA::IMA(){}


bool IMA::Run_IMA_Controller1(){
    
    MyLat2 = Latest_R(GPS_Data_Ptr.get(),0).latitude;
    MyLong2 = Latest_R(GPS_Data_Ptr.get(),0).longitude;
    MyLat = Latest_R(GPS_Data_Ptr.get(),1).latitude;
    MyLong = Latest_R(GPS_Data_Ptr.get(),1).longitude;
    MyAlt = Latest_R(GPS_Data_Ptr.get(),0).altitude;

    std::map<double ,std::string>  last_possible_ima;
    IMA_CARS car;
    for (const auto& mac_pair : *vehicles_map_ptr) {
        const auto& time_map=mac_pair.second;

            auto last_read = time_map.rbegin();
            const Vehicle &last_read_data=last_read->second;
            VLat2=last_read_data.latitude;
            VLong2=last_read_data.longitude;
            VAlt = last_read_data.altitude;
            
            auto before_last = std:: prev(time_map.rbegin());
            const Vehicle &before_last_data=before_last->second;
            VLat=before_last_data.latitude;
            VLong=before_last_data.longitude;

            
        if(abs(MyAlt - VAlt) < ALT_THRESH){
            car = is_ima(MyLat, MyLong, MyLat2, MyLong2, VLat, VLong, VLat2, VLong2);
            //std::cout<<car.distance<< "  "<<car.drirection<<std::endl;
            if(car.distance != 0){
                last_possible_ima[car.distance] = car.drirection;
                std::cout<<last_possible_ima.begin()->first<< "  "<<last_possible_ima.begin()->second<<std::endl;
            }
        }
        
    }
    if(last_possible_ima.empty()){
        return false;
    }else{
        imaMap = last_possible_ima;
        return true;
    }


}

IMA_CARS IMA::Run_IMA_Controller2(){
   //std::cout<<"HIMA"<<std::endl;
    IMA_CARS car;
    car.distance = imaMap.begin()->first;
    car.drirection = imaMap.begin()->second;
    //std::cout<< imaMap.begin()->first << imaMap.begin()->second <<"  " << imaMap.size()<<std::endl;
    return car;

}


void IMA::Update_GPS_Data(std::shared_ptr<std::vector<GPSData>> reading){
    GPS_Data_Ptr=reading; 
}

void IMA::Update_Vehicles_Data(std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_reading){
    vehicles_map_ptr = vehicles_reading;
}

IMA_CARS  IMA::is_ima(double latA_1,double lonA_1,double latA_2,double lonA_2,double latB_1,double lonB_1,double latB_2,double lonB_2) {
    /*
    std::cout<<"VE DATA\n"<<std::endl;
    std::cout<<latB_1<<std::endl;
    std::cout<<lonB_1<<std::endl;
    std::cout<<latB_2<<std::endl;
    std::cout<<lonB_2<<std::endl;
    std::cout<<"\n"<<std::endl;
    */
    IMA_CARS MY_IMA;
    MY_IMA.distance = 0;
    MY_IMA.drirection = "NONE";

    double headingA;
    headingA = calculateHeading(latA_1, lonA_1, latA_2, lonA_2); // Heading of car 1
    //std:: cout << "My Heading  "<< headingA  << std::endl;
    double headingB;
    headingB = calculateHeading(latB_1, lonB_1, latB_2, lonB_2); // Heading of car 1
    //std::cout <<"Others Heading " << headingB <<  std::endl;
    double difference = calculateHeadingDifference(headingA, headingB);
    //std::cout << "The diffrence is "<< difference  << std::endl;
    double dis = distance(latB_2, lonB_2, latA_2, lonA_2);

    //std::cout << "Distance in meter is "<< dis<< "  heading_diff  "<< difference<< std::endl;
    //std::cout<<"\n"<<std::endl;

    bool relative_position = determineRelativePosition(latA_1, lonA_1, latA_2, lonA_2,latB_1, lonB_1);
    if(dis<100 ){
        if ((difference > 45) && (difference < 135) && relative_position==0) {
            MY_IMA.drirection="Right";
            MY_IMA.distance=dis;
        }
            
        else if  ((difference > 225) && (difference < 315) && relative_position==1){
            MY_IMA.drirection="Left";
            MY_IMA.distance=dis;
        }
    }

        
    return MY_IMA;
}