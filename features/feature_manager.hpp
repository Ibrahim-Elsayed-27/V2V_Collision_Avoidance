// feature_manager.hpp

#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "../sensor_manager/sensor_manager.hpp"
#include "../comm_manager/comm_manager.hpp"
#include "../features/BSW/BSW.hpp"
#include "../features/DNPW/DNPW.hpp"
#include "../features/EEBL/EEBL.hpp"
#include "../features/FCW/FCW.hpp"
#include "../features/IMA/IMA.hpp"

class Feature_manager
{
public:
    Feature_manager();

    Feature_manager(std::shared_ptr<SensorManager> sensor_manager_handle,std::shared_ptr<CommManager> comm_manager_handle);  
    
    ~Feature_manager();

    void Run_Features();
    
private:
    std::shared_ptr<SensorManager> sensor_manager_ptr;
    std::shared_ptr<CommManager> comm_manager_ptr;

    BSW bsw;
    DNPW dnpw;
    EEBL eebl;
    FCW fcw;
    IMA ima;

    void Run_BSW();
    void Run_DNPW();
    void Run_EEBL();
    void Run_FCW();
    void Run_IMA();

};


#endif // FEATURE_HPP