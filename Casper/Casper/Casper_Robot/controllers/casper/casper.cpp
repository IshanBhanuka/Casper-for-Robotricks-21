// File:controller code of casper       casper.cpp
// Date:9/19/2021
// Description: This is a line following robot's controller code C++


#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#define TIMESTEP 32
#define MAX_SPEED -6.2
#include <iostream>
using namespace std;
using namespace webots;

int driver(double num[]){
   if(num[0]>350 && num[1]>350 ){
      return 4;
   }
   else if(num[0]>350 && num[1]<350){
       return 2;
   }
   else if (num[1]>350 && num[0]<350){
       return 3;
   }
   else{
       return 4;
   }

}


int main(int argc, char **argv) {
  
  Robot *robot = new Robot();
  Motor *Rmotor = robot->getMotor("MotorR");
  Motor *Lmotor = robot->getMotor("MotorL");
  
  Rmotor->setPosition(INFINITY);
  Lmotor->setPosition(INFINITY);
  
  Rmotor->setVelocity(0.0);
  Lmotor->setVelocity(0.0);
  
  
 
  DistanceSensor *right= robot->getDistanceSensor("RightSensor");
  DistanceSensor *left = robot->getDistanceSensor("LeftSensor");
  
 
  right->enable(TIMESTEP);
  left->enable(TIMESTEP);
  
  int speedR=-10;
  int speedL=-10;

 
  while (robot->step(TIMESTEP) != -1) {
    
    Rmotor->setVelocity(MAX_SPEED);
    Lmotor->setVelocity(MAX_SPEED);
    
    double val_R=right->getValue();
    double val_L=left->getValue();

    double arr[3]={val_L,val_R};
    cout<<"turn right";   
    int decision=driver(arr);
    if (decision==2){
            cout<<"turn right";
            speedR=-9.0;
            speedL=9.0;
            }
    if (decision==3){
          
            speedR=9.0;
            speedL=-9.0;
            }
    if (decision==4){
        
           speedR=10.0 ;
           speedL=10.0 ;
           }
    Rmotor->setVelocity(speedR);
    Lmotor->setVelocity(speedL);
    
  };

 

  delete robot;
  return 0;
}
