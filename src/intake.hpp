#pragma once
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;
using namespace Constants;

//two different motors: Clawin and intake
class Intake{
    public:
    //initialize motor
    Motor IntakeMtr = Motor(intake);
    Motor ClawinMtr = Motor(clawIn);
    Intake(){
    IntakeMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    ClawinMtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
    inline void in(int voltage){
      IntakeMtr.move(voltage);
      ClawinMtr.move(voltage);
    }
    inline void out(int voltage){
      IntakeMtr.move(-1*voltage);
      ClawinMtr.move(-1*voltage);
    }


};  