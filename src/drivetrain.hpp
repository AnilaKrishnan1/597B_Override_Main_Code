#pragma once
#include "constants.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
using namespace pros;
using namespace Constants;
#include "pros/motor_group.hpp"

class DriveTrain {
     public:
    //initializing right drivetrain motors
    const Motor rd1_mtr = Motor(rd1_p);
    const Motor rd2_mtr = Motor(rd2_p);
    const Motor rd3_mtr = Motor(rd3_p);
    //initializing left drivetrain motors
    const Motor ld1_rmtr = Motor(ld1_p);
    const Motor ld2_rmtr = Motor(ld2_p);
    const Motor ld3_rmtr = Motor(ld3_p);
    //initializing motorgroups
    
    MotorGroup Rightdt_group = MotorGroup({rd1_p, rd2_p, rd3_p});   
	MotorGroup Leftdt_group = MotorGroup({-ld1_p, -ld2_p,-ld3_p}); // the - sign makes the motors reverse

    DriveTrain(){
        //set motor break mode for right drivetrain
        rd1_mtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        rd2_mtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        rd3_mtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        //set motor break mode for left drivetrain
        ld1_rmtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        ld2_rmtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        ld3_rmtr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }

    inline void tankDrive(int leftY, int rightY){
        Rightdt_group.move(rightY);
        Leftdt_group.move(leftY);
    }

};