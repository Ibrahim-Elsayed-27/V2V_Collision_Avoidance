//BSW.cpp

#include "BSW.hpp"

#include <iostream>


BSW::BSW(){}
/*  static int c=0;

    // Get Average to smooth signal 
    distance_FC = 0;
    int size = US_FC_Data_Ptr.get()->size();
    for (int i=0;i< size ; i++){
        distance_FC += Latest_R(US_FC_Data_Ptr.get(),i).distance;
    }

    distance_FC = distance_FC/size;

    int flag_1=0;
    
    if(c<100){
    std::cout<<"distance avg: " << distance_FC<<std::endl;
    }
    c++;
    
*/

int BSW::Run_BSW_Controller1(){
  static int c=0;

  distance_RL =0;
  distance_RR =0;

  //smooting for RL
  int sizeRL=US_RL_Data_Ptr.get()->size();
  for (int i=0;i< sizeRL ; i++){
    distance_RL += Latest_R(US_RL_Data_Ptr.get(),i).distance;
  }
  //after smootin
  distance_RL = distance_RL/sizeRL;


  

  //smooting for RR 
  int sizeRR=US_RR_Data_Ptr.get()->size();
  for (int i=0;i< sizeRR ; i++){
    distance_RR += Latest_R(US_RR_Data_Ptr.get(),i).distance;
  }
  //after smooting
  distance_RR = distance_RR/sizeRR;

  std::cout<<distance_RL<<std::endl;
  std::cout<<distance_RR<<std::endl;
  
  int flag=0;
  if(c<100){
   std::cout<<"distance avg for RR : " << distance_RR<<"distance avg for RL : " << distance_RL<<std::endl;
  }
  c++;


  if(distance_RR < distance_th_backR ){
    flag += 1;
  }


  if (distance_RL < distance_th_backL ){
      
    flag += 2;
  }

    
  return flag;     
   
}


void BSW::Update_US_RL_Data(std::shared_ptr<std::vector<USData>> reading){
    US_RL_Data_Ptr=reading; 
}
void BSW::Update_US_RR_Data(std::shared_ptr<std::vector<USData>> reading){
    US_RR_Data_Ptr=reading; 
}


