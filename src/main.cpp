#include "main.h"
#include "drivetrain.hpp"
#include "intake.hpp"
//#include "vex.h"
//#include <pros/screen.hpp>
#include "matchload.hpp"
//#include lemlib
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp"
ASSET(lowerGoalScorePath_txt);
lemlib_tarball::Decoder decoder(lowerGoalScorePath_txt);

using namespace pros;
Intake in;
Matchload match;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
// void initialize() {
// 	pros::lcd::initialize();
// }

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	resetCoordinateSystem();
	chassis.moveToPoint(0,18,1500,{.maxSpeed = 60});
	c::delay(1500);
	chassis.turnToHeading(90, 1000,{.maxSpeed = 40});
	match.open(); 
	c::delay(1500);
	resetCoordinateSystem();
	chassis.setPose(0,0,50); 
	chassis.turnToHeading(90, 400,{.maxSpeed = 40});
	chassis.moveToPoint(10,13,400,{.forwards=true});
	c::delay(1500);
	in.storage(127);
	c::delay(5000);
}
  	




/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller master(CONTROLLER_MASTER);
	int matchET = 0;
	while (true) {
	//tankdrive
		arcadeDrive(master.get_analog(ANALOG_LEFT_Y),master.get_analog(ANALOG_RIGHT_X));
	//intake
		if (master.get_digital(E_CONTROLLER_DIGITAL_A)) {
			in.floor(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			in.floor(-127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			in.storage(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			in.storage(-127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			in.top_level(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			in.mid_level(-127);
		} else {
			in.resting();
		}

	//matchload mech
		if (master.get_digital(E_CONTROLLER_DIGITAL_UP) && (millis() - matchET > 500)){
			match.open(); matchET = millis();
		}
	}
}
