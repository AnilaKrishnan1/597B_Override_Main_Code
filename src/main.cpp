#include "main.h"
#include "drivetrain.hpp"
#include "intake.hpp"
//#include "vex.h"
//#include <pros/screen.hpp>
#include "matchload.hpp"
#include "matchload2.hpp"
//#include lemlib
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib-tarball/api.hpp"
ASSET(lowerGoalScorePath_txt);
lemlib_tarball::Decoder decoder(lowerGoalScorePath_txt);

using namespace pros;
Intake in;
Matchload match;
Matchload2 blocker;
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
	chassis.setPose(0,0,90);
	chassis.moveToPoint(11,0,1000,{.maxSpeed = 60});
	c::delay(1500);
	chassis.turnToHeading(90, 1300,{.maxSpeed = 40});
	match.open(); 
	chassis.setPose(0,0,0);
	chassis.moveToPoint(13,-4,1000,{.maxSpeed = 140}); // change after testing to be faster and ram into it
	blocker.open(); 
	in.storage(127); // intakes blocks from matchload
	c::delay(2000); // change after testing 
	chassis.moveToPoint(13,-5,1000,{.maxSpeed = 140});
	c::delay(2000);
	chassis.moveToPoint(13,-7,1000,{.maxSpeed = 140});
	c::delay(2000);
	chassis.setPose(0,0,0);
	chassis.turnToHeading(3, 300,{.maxSpeed = 40});
	
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,-11,1000,{.forwards = false,.maxSpeed = 60});
	in.resting();
	c::delay(1000);
	match.open(); // closes matchload
	blocker.open(); 
	c::delay(1000);
	in.top_level(127); //scores on high goal
	c::delay(4000); // change after testing ------
	in.resting();
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,2,400,{.forwards = true,.maxSpeed = 60});
	c::delay(500);
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,-5,800,{.forwards = false,.maxSpeed = 80});// gets control

	c::delay(2000);
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,4,300,{.maxSpeed = 60}); // moves back
	in.storage(-127); //outtakes blocks
	c::delay(1500);
	in.resting();
	chassis.turnToHeading(90, 1500,{.maxSpeed = 40});
	chassis.setPose(0,0,0);
	chassis.moveToPoint(6,40,5000,{.maxSpeed = 60}); // moves across the field 
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,-5,200,{.forwards = false, .maxSpeed = 60}); // moves back
	chassis.setPose(0,0,0);
	chassis.turnToHeading(-90, 1600,{.maxSpeed = 40});
	match.open(); 
	chassis.setPose(0,0,0);
	chassis.moveToPoint(-15,-8,900,{.maxSpeed = 80}); // moves to matchload

	blocker.open(); // opens blocker
	in.storage(127); // intakes blocks from matchload
	c::delay(4000); // change after testing -------
	chassis.moveToPoint(-15,-9,1000,{.maxSpeed = 90});
	c::delay(3000); // change after testing -------
	chassis.setPose(0,0,0);
	chassis.moveToPoint(2,-3,900,{.forwards = false,.maxSpeed = 60}); // moves to score on high goal
	match.open();
	blocker.open();
	c::delay(1000);
	in.top_level(127); //scores on high goal
	c::delay(6000); // change after testing ------
/*
	in.resting();
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,7,900,{.maxSpeed = 60}); // moves back
	in.storage(-127); //outtakes blocks
	c::delay(1500);
	in.resting();
	chassis.turnToHeading(-90, 1500,{.maxSpeed = 40});
	c::delay(1000);
	chassis.moveToPoint(-25,-15,2000,{.maxSpeed = 200}); // parks
	in.storage(-127); //outtakes blocks
	c::delay(1500);
	in.resting();
	*/
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
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			in.storage_middle(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			in.storage(-127); // outtake
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			in.top_level(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			in.mid_level(127);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			in.storage(127);
		} else {
			in.resting();
		}

	//matchload mech and descore
		if (master.get_digital(E_CONTROLLER_DIGITAL_UP) && (millis() - matchET > 500)){
			match.open(); matchET = millis();
		}
		if (master.get_digital(E_CONTROLLER_DIGITAL_X) && (millis() - matchET > 500)){
			blocker.open(); matchET = millis();
		}
	}
}




// matchload 3 pseudocode

/*
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,10,1100,{.maxSpeed = 60}); // moves back
	chassis.setPose(0,0,0);
	chassis.turnToHeading(-90, 1500,{.maxSpeed = 40});
	chassis.moveToPoint(10,0,800,{.maxSpeed = 60}); // moves right
	chassis.turnToHeading(0, 1500,{.maxSpeed = 40});
	chassis.setPose(0,0,0);
	chassis.moveToPoint(0,30,4000,{.maxSpeed = 60}); // moves across left long goal
	chassis.turnToHeading(90, 1500,{.maxSpeed = 40});
	chassis.moveToPoint(10,0,800,{.maxSpeed = 60}); // moves left towards matchload
	chassis.turnToHeading(90, 1500,{.maxSpeed = 40});
	chassis.setPose(0,0,0);
*/

/*

	match.open(); //opens matchload
	chassis.moveToPoint(0,15,1100,{.maxSpeed = 60});
	in.storage(127); // intakes blocks from matchload
	c::delay(4000); // change after testing -------
	chassis.setPose(0,0,0);
*/

/*
	chassis.moveToPoint(0,-10,1400,{.forwards = false,.maxSpeed = 60});
	in.resting();
	blocker.open(); 
	c::delay(2000);
	match.open(); // closes matchload
	in.top_level(127); //scores on high goal
	c::delay(6000); // change after testing ------
	in.resting();
*/
