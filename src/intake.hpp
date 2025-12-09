#pragma once
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;
using namespace Constants;

//three different motors in_top_p in_mid_p in_btm_p
class Intake{
    public:
    //initialize motor
    Motor Intake_top_mtr = Motor(intake_top_p);
    Motor Intake_mid_mtr = Motor(intake_mid_p);
    Motor Intake_btm_mtr = Motor(intake_btm_p);
    Intake(){
    Intake_top_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    Intake_mid_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    Intake_btm_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
    inline void storage(int voltage){
        Intake_btm_mtr.move(-1*voltage);
    }
    inline void storage_middle(int voltage){
        Intake_btm_mtr.move(-1*voltage);
        Intake_mid_mtr.move(-1*voltage);
    }
    inline void top_level(int voltage){
        Intake_top_mtr.move(voltage);
        Intake_mid_mtr.move(-1*voltage);
        Intake_btm_mtr.move(-1*voltage);
    }
    inline void mid_level(int voltage){
        Intake_btm_mtr.move(-1*voltage);
        Intake_mid_mtr.move(-1*voltage);
        Intake_top_mtr.move(-1*voltage);
    }
    inline void resting(){
        Intake_btm_mtr.move(0);
        Intake_top_mtr.move(0);
        Intake_mid_mtr.move(0);
    }
};  