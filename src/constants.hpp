#pragma once
#include <sys/_intsup.h>
#include <sys/_types.h>

namespace Constants {
    //right drivetrain
    static constexpr unsigned char rd1_p = 17; //Front right 
    static constexpr unsigned char rd2_p = 20; //Middle right 
    static constexpr unsigned char rd3_p = 16; //End right 

    //left drivetrain
    static constexpr unsigned char ld1_p = 13; //Front left
    static constexpr unsigned char ld2_p = 14; //Middle left
    static constexpr unsigned char ld3_p = 15; //End left

    //intakes
    static constexpr unsigned char intake_top_p = 1;
    static constexpr unsigned char intake_mid_p = 2;
    static constexpr unsigned char intake_btm_p = 3;

}