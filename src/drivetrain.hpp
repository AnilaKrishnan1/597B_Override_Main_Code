#pragma once
#include "constants.hpp"
#include "main.h"
using namespace pros;
using namespace Constants;
#include "pros/motor_group.hpp"
pros::MotorGroup leftMotors({ld1_p, -ld2_p, -ld3_p},
                            pros::MotorGearset::blue); // left motor group 
pros::MotorGroup rightMotors({-rd1_p, rd2_p, rd3_p}, pros::MotorGearset::blue); // right motor group 
// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(horizontal_p);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(vertical_p);


pros::Imu imu(inertial_p);

 inline void tankDrive(int leftY, int rightY){
    rightMotors.move(rightY);
    leftMotors.move(leftY);
}
 inline void arcadeDrive(signed char leftY, signed char rightX) {
        leftY = abs(leftY)<threshold ? 0 : leftY;
        rightX = abs(rightX)<threshold ? 0 : rightX;
        leftMotors.move(leftY + rightX);
        rightMotors.move(leftY - rightX);
}
/**
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

  

};
*/



    
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging