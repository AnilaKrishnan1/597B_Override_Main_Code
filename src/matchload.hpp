#pragma once
#include "pros/adi.hpp"
#include "Constants.hpp"

using namespace pros;
using namespace Constants;
class Matchload{
    private:
    adi::DigitalOut Holder = adi::DigitalOut(Matchloader_p, false);
    bool Holder_out = false;
    public:
    Matchload(){}
    void open(){Holder_out=!Holder_out; 
    Holder.set_value(Holder_out);}

};