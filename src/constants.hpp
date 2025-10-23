#pragma once
#include <sys/_intsup.h>
#include <sys/_types.h>
#include <cmath>

namespace Constants {
    //right drivetrain
    static constexpr unsigned char rd1_p = 17; //stacked right 
    static constexpr unsigned char rd2_p = 20; //Middle right 
    static constexpr unsigned char rd3_p = 16; //End right 

    //left drivetrain
    static constexpr unsigned char ld1_p = 13; //stacked left
    static constexpr unsigned char ld2_p = 14; //Middle left
    static constexpr unsigned char ld3_p = 15; //End left

    //intakes
    static constexpr unsigned char intake_top_p = 1;
    static constexpr unsigned char intake_mid_p = 2;
    static constexpr unsigned char intake_btm_p = 3;

    //sensors
    static constexpr unsigned char horizontal_p = 18;
    static constexpr unsigned char vertical_p = 19;
    static constexpr unsigned char inertial_p = 4;

    //odom shit
    constexpr double gear_ratio = ((double)36/60); 
    constexpr double wheel_circumference = 2.75;
    constexpr double start_heading = 90;

    //piston
    static constexpr unsigned char Matchloader_p = 'A';
    //drivetrain
    constexpr int threshold = 10; // Joystick deadzone (7–10%)

}