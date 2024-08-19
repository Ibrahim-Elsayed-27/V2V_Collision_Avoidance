//BSW.hpp

#ifndef BSW_HPP
#define BSW_HPP

#include "../../lib/lib.hpp"

#include "../../Config/config.hpp"
#include "../../Sensors/US.hpp"

class BSW {
public:
    BSW();
    // rear US data Consumer

    void Update_US_RL_Data(std::shared_ptr<std::vector<USData>> reading);
    void Update_US_RR_Data(std::shared_ptr<std::vector<USData>> reading);

    int Run_BSW_Controller1(); 
    

private:
    // local rear US data
    double  distance_RL, distance_RR;

    // local rear US data ptr
    std::shared_ptr<std::vector<USData>> US_RL_Data_Ptr; 
    std::shared_ptr<std::vector<USData>> US_RR_Data_Ptr; 

    double distance_th_backR = 20  ; //cm
    double distance_th_backL= 20  ; //cm


};

#endif // BSW_HPP





