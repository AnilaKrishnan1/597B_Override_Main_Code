#pragma once
#include "pros/adi.hpp"
#include "Constants.hpp"

using namespace pros;
using namespace Constants;
class Matchload2{
    private:
    adi::DigitalOut Holder2 = adi::DigitalOut(Matchloader_p2, false);
    bool Holder2_out = false;
    public:
    Matchload2(){}
    void open(){Holder2_out=!Holder2_out; 
    Holder2.set_value(Holder2_out);}
};