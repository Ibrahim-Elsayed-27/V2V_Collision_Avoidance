 // US.hpp

#ifndef US_HPP
#define US_HPP


#include "../Config/config.hpp"
#include "Drivers/USinterface.hpp"

#include <vector>
#include <mutex>
#include <memory>
#include <string>


class US  {
public:
    US(const std::string& name, int trigPin, int echoPin);

    void updateReadings(); // Updates US readings

    std::vector<USData> copyLatestData() const;

    const char* getName() const ;

    std::vector<USData> readings_;

private:
    UltrasonicSensor ultrasonicsensor;
    std::string name_; // Name of the US sensors
    
    mutable std::mutex dataMutex_; // Mutex to synchronize access to US readings
    
};


 #endif // US_HPP
