// Sensor_manager.cpp

#include "sensor_manager.hpp"
#include <iostream>
#include "../Config/config.hpp"

// "EN", "GPS", "IMU", "US_FC", "US_FL", "US_FR", "US_RC", "US_RL", "US_RR"

SensorManager::SensorManager(){
    
      
         ENPointer_ = {names[ENi], std::make_shared<EN>()};
      
        
         GPSPointer_={names[GPSi], std::make_shared<GPS>(names[GPSi])};

         IMUPointer_={names[IMUi], std::make_shared<IMU>(names[IMUi])};
    

     
         USPointers_["US_FC"] = std::make_shared<US>("US_FC",US_FC_TRIG,US_FC_ECHO);
         USPointers_["US_FL"] = std::make_shared<US>("US_FL",US_FL_TRIG,US_FL_ECHO);
         USPointers_["US_FR"] = std::make_shared<US>("US_FR",US_FR_TRIG,US_FR_ECHO);
         USPointers_["US_RC"] = std::make_shared<US>("US_RC",US_RC_TRIG,US_RC_ECHO);
         USPointers_["US_RL"] = std::make_shared<US>("US_RL",US_RL_TRIG,US_RL_ECHO);
         USPointers_["US_RR"] = std::make_shared<US>("US_RR",US_RR_TRIG,US_RR_ECHO);

         USPointers_["US_RR"]->readings_={{20},{10},{10},{20},{15}};
         USPointers_["US_RL"]->readings_= {{20},{10},{10},{20},{15.6}};
     


}


void SensorManager::updateSensorsData() {
    static int c = 0;
    while (1){

         
              ENPointer_.second->updateReadings();
            

              //GPSPointer_.second->updateReadings();

              IMUPointer_.second->updateReadings();


         for (auto& sensorPair : USPointers_) {
               sensorPair.second->updateReadings();
            }

            //std::cout << "write completed -> " << c++ << std::endl;
    }
}

 std::shared_ptr<std::vector<ENData>> SensorManager::getENData()  {     
          return(std::make_shared<std::vector<ENData>>(ENPointer_.second->copyLatestData()));
 }


 std::shared_ptr<std::vector<GPSData>> SensorManager::getGPSData()  {
         return(std::make_shared<std::vector<GPSData>>(GPSPointer_.second->copyLatestData()));
}

 std::shared_ptr<std::vector<IMUData>> SensorManager::getIMUData()  {
         return(std::make_shared<std::vector<IMUData>>(IMUPointer_.second->copyLatestData()));
}

 std::shared_ptr<std::vector<USData>> SensorManager::getUSData(const std::string& name)  {
     auto it = USPointers_.find(name);
         return(std::make_shared<std::vector<USData>>(it->second->copyLatestData()));
 }
