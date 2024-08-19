//FCW.cpp

#include "FCW.hpp"

#include <iostream>


FCW::FCW(){}


bool FCW::Run_FCW_Controller1(){
    static int c=0;

    /* Get Average to smooth signal */
    distance_FC = 0;
    int size = US_FC_Data_Ptr.get()->size();
    for (int i=0;i< size ; i++){
        distance_FC += Latest_R(US_FC_Data_Ptr.get(),i).distance;
    }

    distance_FC = distance_FC/size;

    int flag_1=0;
    int flag_2=0;

    auto now = std::chrono::system_clock::now();
    updateDistanceHistory(distance_FC, now);
    double distance_gradient = calculateDistanceGradient();
    if(c<100){
    std::cout<<"distance avg: " << distance_FC<< "    "<< "gradient : "<<distance_gradient<<std::endl;
    }
    c++;
    

    //if((distance_FC < distance_th_front) || (distance_FL < distance_th_front) ||(distance_FR < distance_th_front)){
    if(distance_FC < distance_th_front){  
      flag_1= 1;
    }    
     
    //checking gradient threshold 
    if(distance_gradient > gradient_th){  
      flag_2= 1;
    }    

    return (flag_1 && flag_2);

}

void FCW::Update_US_FC_Data(std::shared_ptr<std::vector<USData>> reading){
    US_FC_Data_Ptr=reading; 
}
/*
void FCW::Update_US_FL_Data(std::shared_ptr<std::vector<USData>> reading){
    US_FL_Data_Ptr=reading; 
}
void FCW::Update_US_FR_Data(std::shared_ptr<std::vector<USData>> reading){
    US_FR_Data_Ptr=reading; 
*/

void FCW::updateDistanceHistory(double distance, const std::chrono::system_clock::time_point& timestamp) {
    distance_history.push_back({distance, timestamp});
    if (distance_history.size() > max_history_size) {
        distance_history.pop_front();
    }
}

double FCW::calculateDistanceGradient() const {
    if (distance_history.size() < 2) {
        return 0.0;
    }

    const auto& latest = distance_history.back();
    const auto& previous = distance_history[distance_history.size() - 2];

    auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(latest.timestamp - previous.timestamp).count();
    /*
    if (time_diff == 0) {
        return 0.0;
    }*/

    return previous.distance - latest.distance; 
}
