// sensor_manager.hpp

#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP


#include "../Sensors/EN.hpp"
#include "../Sensors/GPS.hpp"
#include "../Sensors/IMU.hpp"
#include "../Sensors/US.hpp"


#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#define NEN 1
#define NGPS 1
#define NIMU 1
#define NUS 6

#define ENi 0
#define GPSi ENi+NEN
#define IMUi GPSi+NGPS
#define USi IMUi+NIMU

class SensorManager {
public:
    SensorManager(); // Update data of all sensors

    void updateSensorsData();
   std::shared_ptr<std::vector<ENData>> getENData() ;
   std::shared_ptr<std::vector<GPSData>> getGPSData() ;
   std::shared_ptr<std::vector<IMUData>> getIMUData() ;
   std::shared_ptr<std::vector<USData>> getUSData(const std::string& name) ;
  

private:
   // Model model_;
   std::vector<std::string> names = {"EN", "GPS", "IMU", "US_FC", "US_FL", "US_FR", "US_RC", "US_RL", "US_RR"};
    
   std::pair<std::string, std::shared_ptr<EN>> ENPointer_;
   std::pair<std::string, std::shared_ptr<GPS>> GPSPointer_;
   std::pair<std::string, std::shared_ptr<IMU>> IMUPointer_;
   std::unordered_map<std::string, std::shared_ptr<US>> USPointers_;

};

#endif // SENSOR_MANAGER_HPP
