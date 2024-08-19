// main.cpp


#include "../features/feature_manager.hpp"
#include "../sensor_manager/sensor_manager.hpp"
#include "../comm_manager/comm_manager.hpp"


#include <thread>   
#include <chrono>
#include <iostream>

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void printAllVehiclesData(std::map<std::string, std::map<std::string, Vehicle >> vehicles_map) ;


int main() {
    
    std::shared_ptr<SensorManager> sensorManager_Sptr = std::make_shared<SensorManager>();
    std::shared_ptr<SensorManager> sensorManager_Sptr2 = std::make_shared<SensorManager>();
    std::shared_ptr<SPI> spi_Uptr= std::make_shared<SPI>("/dev/spidev0.0", SPI_MODE_0, 50000, 8);
    std::shared_ptr<CommManager> commManager_Sptr = std::make_shared<CommManager>(sensorManager_Sptr2,spi_Uptr);
    Feature_manager feature_manager(sensorManager_Sptr,commManager_Sptr);

    


      std::thread SensorsThread(&SensorManager::updateSensorsData, sensorManager_Sptr.get());
      SensorsThread.detach();   //Detach the thread to run independently

      // std::thread send_thread(&CommManager::send_frame_esp, commManager_Sptr.get());
      // send_thread.detach();  // Detach the thread to run independently 

      // std::thread receive_thread(&CommManager::recieve_frame_esp, commManager_Sptr.get());
      // receive_thread.detach();  // Detach the thread to run independently 
 

       std::thread featuresThread(&Feature_manager::Run_Features, &feature_manager);
       featuresThread.detach();  // Detach the thread to run independently 
      



    //  while(1){
    //   printAllVehiclesData(*(commManager_Sptr->getVEHICLESData()));
    //   delay(2000);
    // }
      

     /*
     while(1){
        commManager_Sptr->send_frame_stm("1");
        commManager_Sptr->spi_ptr->spi_loop();
        //commManager_Sptr->recieve_frame_esp();
       //printAllVehiclesData(commManager_Sptr->getVEHICLESData());
      }
      */

      
    

    //Wait for user input to terminate the program
     std::string input;
     std::cout << "Press Enter to exit." << std::endl;
     std::getline(std::cin, input);
    
     
    
    return 0;
}



void printAllVehiclesData(std::map<std::string, std::map<std::string, Vehicle >> vehicles_map)  {
    //const auto& GPS_LAST = gpsData->back(); 

        for (const auto& mac_pair : vehicles_map) {
            const std::string& mac = mac_pair.first;
            const auto& time_map = mac_pair.second;

            for (const auto& time_pair : time_map) {
                const std::string& time = time_pair.first;
                const Vehicle& vehicle = time_pair.second;
                
                std::cout << "MAC Address: " << mac << ", Time: " << time << std::endl;
                std::cout << "  Latitude: " << vehicle.latitude << std::endl;
                std::cout << "  Longitude: " << vehicle.longitude << std::endl;
                std::cout << "  Acceleration X: " << vehicle.acc_x << std::endl;
                std::cout << "  Acceleration Y: " << vehicle.acc_y << std::endl;
                std::cout << "  Acceleration Z: " << vehicle.acc_z << std::endl;
                std::cout << "  Velocity: " << vehicle.velocity << std::endl;


            }


        
    }
    
}