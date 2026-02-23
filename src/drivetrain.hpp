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
// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {ld1_p, ld2_p, ld3_p}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{rd1_p, rd2_p, rd3_p}

  // IMU Port
  ,inertial_p

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,gear_ratio

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor
ss
  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}