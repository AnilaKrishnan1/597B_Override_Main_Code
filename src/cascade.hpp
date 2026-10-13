#pragma once
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;
using namespace Constants;

//two different motors: Clawin and intake
class Cascade{
    public:
    //initialize motor
    Motor CascadeMtr = Motor(cascadeMtr);
    Motor ClawturnMtr = Motor(clawIn);
    Cascade(){
    CascadeMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ClawturnMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
    inline void allUp(int voltage){
      ClawturnMtr.move(voltage);
      CascadeMtr.move(voltage);
    }
    inline void allDown(int voltage){
      ClawturnMtr.move(-1*voltage);
      CascadeMtr.move(-1*voltage);
    }
    inline void cascadeDown(int voltage){
      CascadeMtr.move(-1*voltage);
    }
    inline void clawDown(int voltage){
      ClawturnMtr.move(-1*voltage);
    }


};  