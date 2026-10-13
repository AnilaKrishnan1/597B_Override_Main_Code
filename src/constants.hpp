#pragma once
#include <sys/_intsup.h>
#include <sys/_types.h>
#include <cmath>

namespace Constants {
    //right drivetrain
    static constexpr unsigned char rd1_p = 19; //Front right 
    static constexpr unsigned char rd2_p = 20; //5.5W right 
    static constexpr unsigned char rd3_p = 9; //End right 

    //left drivetrain
    static constexpr unsigned char ld1_p = 12; //Front left
    static constexpr unsigned char ld2_p = 11; //5.5W left
    static constexpr unsigned char ld3_p = 11; //End left

    
    //intake
    static constexpr unsigned char intakeMtr = 9;

    //cascade
    static constexpr unsigned char cascadeMtr = 1; //Cascade up and down motor

    //claw
    static constexpr unsigned char clawIn = 2; //Claw motor to collect pins/cups
    static constexpr unsigned char clawTurn = 6; //Claw motor to turn claw

    //sensors
    static constexpr unsigned char horizontal_p = 3;
    static constexpr unsigned char vertical_p = 5;
    static constexpr unsigned char inertial_p = 8;

    //odom 
    constexpr double gear_ratio = ((double)36/60); 
    constexpr double wheel_circumference = 2.75;
    constexpr double start_heading = 90;

    //drivetrain
    constexpr int threshold = 10; // Joystick deadzone (7–10%)

}