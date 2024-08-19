// comm_manager.cpp

#include "comm_manager.hpp"


CommManager::CommManager(std::shared_ptr<SensorManager> sensor_manager_handle,std::shared_ptr<SPI> spi_handle)
        : sensor_manager_ptr(sensor_manager_handle),spi_ptr(spi_handle){
            

        }

CommManager::~CommManager(){}

void CommManager::send_frame_esp(){
    while(1){

        // Read data from sensors using shared pointer to vector
        gpsData = sensor_manager_ptr->getGPSData();//gps
        imuData = sensor_manager_ptr->getIMUData();//IMU
        //imuData = IMU_init_D;
        enData = sensor_manager_ptr->getENData();//encoder
    
        // accesssing the last struct in the given vector 
        const auto& IMU_LAST = Latest_R(imuData.get(),0);
        const auto& GPS_LAST = Latest_R(gpsData.get(),0);
        const auto& EN_LAST = Latest_R(enData.get(),0);
        
    
        std::ostringstream oss;
        oss << "@" << "@" << "@" << MyMAC <<","<< GPS_LAST.latitude <<","<< GPS_LAST.longitude <<"," << GPS_LAST.altitude <<","<< GPS_LAST.time <<","<< IMU_LAST.AccX << "," << IMU_LAST.AccY<< "," << IMU_LAST.AccZ << "," << EN_LAST.speed << "%"<< "%"<< "%";
    
        //std::cout<<oss.str()<<std::endl;
    
        // Code to append sensorFrame to "from esp.txt" 
        std::vector<unsigned char> send_esp(oss.str().begin(), oss.str().end());
    
        appendDataToFile(RASP_PATH_TO_ESP, send_esp);
        spi_ptr->spi_loop();

    }
}

void CommManager::recieve_frame_esp() {


while(1){
    std::vector<unsigned char> all_readings_vec = readDataFromFile(RASP_PATH_FROM_ESP);




    // Create an empty string
    std::string  vechicle_read;
    int start_ind=0;
    for (int i=2; i<all_readings_vec.size();i++){
        
        if (all_readings_vec[i]== '@' && all_readings_vec[i-1]== '@' && all_readings_vec[i-2]== '@' ){
            start_ind = i;
        }

        if (all_readings_vec[i]== '%' && all_readings_vec[i-1]== '%' && all_readings_vec[i-2]== '%' ){
            vechicle_read.assign(all_readings_vec.begin() + start_ind + 1, all_readings_vec.begin() + i - 2);

            std::istringstream ss(vechicle_read); // Skip the '@' at the beginning
            std::string mac_address, part, time;
            double latitude, longitude,altitude, velocity, acc_x, acc_y, acc_z;

            std::getline(ss, mac_address, ','); // Read MAC address up to the first comma
            std::getline(ss, part, ',');
            latitude = safe_stod(part);
            std::getline(ss, part, ',');
            longitude = safe_stod(part);
            std::getline(ss, part, ',');
            altitude = safe_stod(part);
            std::getline(ss, time, ',');
            std::getline(ss, part, ',');
            acc_x = safe_stod(part);
            std::getline(ss, part, ',');
            acc_y = safe_stod(part);
            std::getline(ss, part, ',');
            acc_z = safe_stod(part);
            std::getline(ss, part, '%');
            velocity=safe_stod(part);


            Vehicle  new_vehicle{
                    latitude,
                    longitude,
                    altitude,
                    acc_x,
                    acc_y,
                    acc_z,
                    velocity
            };

            std::lock_guard<std::mutex> lock(comm_dataMutex_);
            vehicles_map[mac_address].insert({time,new_vehicle});
            
        }


    }

    
    std::lock_guard<std::mutex> lock(comm_dataMutex_);
    delete_idle_vehicles();
}
    
}


TransferCheck CommManager::send_frame_stm(std::string velocity){
    std::vector<unsigned char> send_stm(velocity.begin(), velocity.end());
    appendDataToFile(RASP_PATH_TO_STM, send_stm);
}



void CommManager::delete_idle_vehicles(){
        std::map<std::string, std::map<std::string, Vehicle >> copy_vehicles_map = vehicles_map; 
        for (const auto& mac_pair : copy_vehicles_map) {
            const std::string& mac = mac_pair.first;
            const auto& time_map = mac_pair.second;
            if(mac.length() != 17){
                vehicles_map.erase(mac_pair.first);
                continue;
            }

            auto last_element_it = time_map.rbegin(); // Get reverse iterator to the last element
            const std::string& last_time = last_element_it->first; // Access the key of the last element
            int seconds = timeDifferenceInSeconds(last_time,"22:19:50");
            if (seconds>=10 ){
                    vehicles_map.erase(mac_pair.first);

                }
            


        }
}






std::shared_ptr<std::map<std::string, std::map<std::string, Vehicle >>>   CommManager::getVEHICLESData(){
    std::lock_guard<std::mutex> lock(comm_dataMutex_);
    return std::make_shared<std::map<std::string, std::map<std::string, Vehicle>>>(vehicles_map);
}



double safe_stod(const std::string& str) {
    try {
        return std::stod(str);
    } catch (const std::invalid_argument& e) {
        //std::cerr << "Invalid argument for stod: " << str << " - returning 0.0" << std::endl;
        return 0.0;  // Default fallback value
    } catch (const std::out_of_range& e) {
        //std::cerr << "Out of range error for stod: " << str << " - returning 0.0" << std::endl;
        return 0.0;  // Default fallback value
    }
}