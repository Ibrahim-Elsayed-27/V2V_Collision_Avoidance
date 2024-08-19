//FCW.hpp

#ifndef FCW_HPP
#define FCW_HPP

#include "../../Config/config.hpp"
#include "../../Sensors/US.hpp"
#include "../../comm_manager/vehicle.hpp"
#include <deque>
#include <chrono>

//  "US_FC", "US_FL", "US_FR".

class FCW {
public:
    FCW();


    // front US data Consumer
    void Update_US_FC_Data(std::shared_ptr<std::vector<USData>> reading);
    
    //void Update_US_FL_Data(std::shared_ptr<std::vector<USData>> reading);
    //void Update_US_FR_Data(std::shared_ptr<std::vector<USData>> reading);

    bool Run_FCW_Controller1(); 

    
private:

    // local front US data
    double distance_FC;

    //double distance_FL, distance_FR;

    // local front US data ptr
    std::shared_ptr<std::vector<USData>> US_FC_Data_Ptr;

    //std::shared_ptr<std::vector<USData>> US_FL_Data_Ptr; 
    //std::shared_ptr<std::vector<USData>> US_FR_Data_Ptr; 

    double distance_th_front = 15  ; //cm

    // History data for gradient calculation
    struct DistanceTimestamp {
        double distance;
        std::chrono::system_clock::time_point timestamp;
    };

    std::deque<DistanceTimestamp> distance_history;
    const size_t max_history_size = 2;

    // Gradient threshold
    double gradient_th = 50; // 

    void updateDistanceHistory(double distance, const std::chrono::system_clock::time_point& timestamp);
    double calculateDistanceGradient() const;

};

#endif // FCW_HPP