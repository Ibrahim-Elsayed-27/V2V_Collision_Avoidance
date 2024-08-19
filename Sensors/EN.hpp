#ifndef EN_HPP
#define EN_HPP

#include <string>
#include <vector>
#include <mutex>
#include <iostream>


#include "../Config/config.hpp"
#include "../Drivers/ENInterface.hpp"



struct ENData {
    double speed;
};

class EN {
public:
    EN();

    void updateReadings();
    std::vector<ENData> copyLatestData() const;
    const char* getName() const;

private:
    std::string name_;
    std::vector<ENData> readings_;
    mutable std::mutex dataMutex_;
    Encoder encoder_; // Encoder object
};

#endif // EN_HPP
