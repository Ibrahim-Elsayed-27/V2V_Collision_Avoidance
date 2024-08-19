// feature_manager.cpp

#include "feature_manager.hpp"

#include <iostream>

//default constructor
Feature_manager::Feature_manager(){} 

//initialization constructor
Feature_manager::Feature_manager(std::shared_ptr<SensorManager> sensor_manager_handle,std::shared_ptr<CommManager> comm_manager_handle)  
: sensor_manager_ptr(sensor_manager_handle), comm_manager_ptr(comm_manager_handle) {}


//default deconstructor
Feature_manager::~Feature_manager(){}



//"EN", "GPS", "IMU", "US_FC", "US_FL", "US_FR", "US_RC", "US_RL", "US_RR"


// function to run all features
void Feature_manager::Run_Features(){

    while (1){
        static int c = 0;

        // run all features
        Run_BSW();
        Run_DNPW();
        Run_FCW();
        Run_EEBL();
        Run_IMA();



        std::cout << "Run_features Done! -> " << c++ << std::endl;
    }
}

void Feature_manager:: Run_BSW(){

    //update needed sensors
    bsw.Update_US_RL_Data(sensor_manager_ptr.get()->getUSData("US_RL"));
    bsw.Update_US_RR_Data(sensor_manager_ptr.get()->getUSData("US_RR"));
    //std::cout << "read US completed\n";
    
    int out=bsw.Run_BSW_Controller1();
    switch(out)
    {
        case 1:
        std::cout << "there is car in right  \n";
        break;

        case 2:
        std::cout << "there is car in left  \n";
        break;

        case 3:  
        std::cout << "there is car in left and right  \n";
        break;

        default:
        break;
                  
    }
  
}


void Feature_manager:: Run_DNPW(){
    
    
    dnpw.Update_Vehicles_Data(comm_manager_ptr.get()->getVEHICLESData());

    dnpw.Update_GPS_Data(sensor_manager_ptr.get()->getGPSData());

    // if US condition true continue the rest of code 
     if(dnpw.Run_DNPW_Status_Front()){
           std::cout << "\n DNBW SYSTEM IS ON \n";

            dnpw.Update_GPS_Data(sensor_manager_ptr.get()->getGPSData());
            //std::cout << "read GPS completed\n";

            // if GPS condition true continue the rest of code
            if(dnpw.Run_DNPW_Status_Cross()){   //checks GPS & speed data
            //std::cout << "\nStatus_Cross True!\n";
            
            // warning
            std::cout << "\n Don't Pass Warning! \n";
            //std::cout<< dnpw.distance_FC << "\n";
            }          
    }
    // no warning
    // else leave
    // more than one controller could be more effiecint
    // if u wanna split controllers depending on the sensor used
    
}

void Feature_manager:: Run_EEBL(){

    //update needed sensors
    eebl.Update_GPS_Data(sensor_manager_ptr.get()->getGPSData());
    eebl.Update_EN_Data(sensor_manager_ptr.get()->getENData());
    eebl.Update_Vehicles_Data(comm_manager_ptr.get()->getVEHICLESData());
    // if GPS condition true continue the rest of code 

    if(eebl.Run_EEBL_Controller1()){
        std::cout<<"Warning: EEBL"<<std::endl;
    }          
  
    
}

void Feature_manager:: Run_FCW(){

    //update needed sensors
    fcw.Update_US_FC_Data(sensor_manager_ptr.get()->getUSData("US_FC"));
    //fcw.Update_US_FL_Data(sensor_manager_ptr.get()->getUSData("US_FL"));
    //fcw.Update_US_FR_Data(sensor_manager_ptr.get()->getUSData("US_FR"));
    //std::cout << "read US completed\n";    
     
    if(fcw.Run_FCW_Controller1()){
       // std::cout << "\n Forward Collision Warning \n";
    }
   
}


void Feature_manager:: Run_IMA(){

    IMA_CARS ima_possible_car;

    //update needed sensors
    ima.Update_GPS_Data(sensor_manager_ptr.get()->getGPSData());
    ima.Update_Vehicles_Data(comm_manager_ptr.get()->getVEHICLESData());
    //std::cout << "reading sensors completed\n";

    if(ima.Run_IMA_Controller1()){
        ima_possible_car = ima.Run_IMA_Controller2();
        //std::cout<< ima_possible_car.drirection << " at distance : " << ima_possible_car.distance << std::endl;
    }
    
}
