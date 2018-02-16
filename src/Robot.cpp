/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "Robot.h"
#include "wpilib.h"

CORE2018 * Robot = nullptr;

CORE2018::CORE2018() :
	driveSubsystem()
	//m_driverJoystick(0),
	//m_operatorJoystick(1)
	{
	Robot = this;
}
void CORE2018::StartCompetition() {

}

void CORE2018::RobotInit() {

}

 void CORE2018::DisabledInit() {

 }

 CORE2018::~CORE2018() {
 	Robot = nullptr;
 }

 START_ROBOT_CLASS(CORE2018);


//void CORE2018::robotInit() {
//
//}
//void CORE2018::teleopInit() {
//
//}
//void CORE2018::teleop() {
//
//}


// void Robot::AutonomousInit() {
//
// }
//
// void Robot::AutonomousPeriodic(){
//
// }


//
// void Robot::TeleopInit(){
//
// }
// void Robot::TestInit(){
//
// }
//
// void Robot::RobotPeriodic(){
//
// }
//
// void Robot::DisabledPeriodic(){
//
// }
//
// void Robot::TeleopPeriodic() {
//
// }
//
// void Robot::TestPeriodic(){
//
// }
//
// void Robot::StartCompetition() {
//
// }
//



