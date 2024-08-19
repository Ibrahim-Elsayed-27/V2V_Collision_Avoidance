// comm_manager.hpp

#ifndef COMM_MANAGER_HPP
#define COMM_MANAGER_HPP


#include <array>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>

#include "../lib/lib.hpp"
#include "spi/spi_hard.hpp"
#include "../sensor_manager/sensor_manager.hpp"
#include "vehicle.hpp"
#include "../Config/config.hpp"

#define MyMAC "12:AS:4S:GE:17"


#define PATH_FROM_ESP  "/media/ibrahim/6/Graduation_project/project_github/V2V-Collision-Avoidance/lib/from_esp32_data.txt"
#define PATH_TO_ESP    "/media/ibrahim/6/Graduation_project/project_github/V2V-Collision-Avoidance/lib/to_esp32_data.txt"
#define PATH_TO_STM    "/media/ibrahim/6/Graduation_project/project_github/V2V-Collision-Avoidance/lib/to_stm32_data.txt"

#define RASP_PATH_FROM_ESP  "/V2V_APP/from_esp32_data.txt"
#define RASP_PATH_TO_ESP    "/V2V_APP/to_esp32_data.txt"
#define RASP_PATH_TO_STM    "/V2V_APP/to_stm32_data.txt"




enum TransferCheck{
    TRANSFER_COMPLETE = 0,
    TRANSFER_FAILED = 1
};




class CommManager {
public:

    CommManager(std::shared_ptr<SensorManager> sensor_manager_handle,std::shared_ptr<SPI> spi_handle);//

    ~CommManager();

    std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>>  getVEHICLESData();
    TransferCheck send_frame_stm(std::string velocity);


    void send_frame_esp();
    void recieve_frame_esp();

    std::shared_ptr<SPI> spi_ptr;
    

private:



    

    void delete_idle_vehicles();

    /*send frame esp variables*/

        // Read data from sensors
    std::shared_ptr<std::vector<GPSData>> gpsData ;
    std::shared_ptr<std::vector<IMUData>> imuData ;
    std::shared_ptr<std::vector<ENData>> enData ;
   
    
    std::shared_ptr<SensorManager> sensor_manager_ptr;
    std::map<std::string, std::map<std::string, Vehicle >> vehicles_map; 
    std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>> vehicles_map_ptr; 

    mutable std::mutex comm_dataMutex_; // Mutex to synchronize access to vehicles readings


};



double safe_stod(const std::string& str);
#endif // COMM_MANAGER_HPP