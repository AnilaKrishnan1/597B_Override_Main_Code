#pragma once
#include "constants.hpp"
#include "main.h"
using namespace pros;
using namespace Constants;
#include "pros/motor_group.hpp"
#include "lemlib/api.hpp"
pros::MotorGroup leftMotors({ld1_p, -ld2_p, -ld3_p},
                            pros::MotorGearset::blue); // left motor group 
pros::MotorGroup rightMotors({-rd1_p, rd2_p, rd3_p}, pros::MotorGearset::blue); // right motor group 
// tracking wheels
// horizontal tracking wheel encoder. Rotation sensor, port 20, not reversed
pros::Rotation horizontalEnc(horizontal_p);
// vertical tracking wheel encoder. Rotation sensor, port 11, reversed
pros::Rotation verticalEnc(vertical_p);
// horizontal tracking wheel. 2.75" diameter, 5.75" offset, back of the robot (negative)
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);

// MEASURE OFFSET WHEN ON THE ROBOT

// vertical tracking wheel. 2.75" diameter, 2.5" offset, left of the robot (negative)
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

pros::Imu imu(inertial_p);

lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

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

// include lemlib
// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController,angularController, sensors, &throttleCurve, &steerCurve);

void follow(const asset &path, double lookahead = 10, int timeout = 3000) {
    chassis.follow(path, lookahead, timeout, true, false);
    }
  
    void resetCoordinateSystem() { chassis.setPose(0, 0, 0); }
    
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

}
 

// get a path used for pure pursuit
// this needs to be put outside a function
