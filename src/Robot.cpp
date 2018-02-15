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
	driveSubsystem(),
	m_driverJoystick(0),
	m_operatorJoystick(1) {
	Robot = this;
}

void CORE2018::robotInit() {

}
void CORE2018::teleopInit() {

}
void CORE2018::teleop() {

}

START_ROBOT_CLASS(CORE2018);
/*
 * This autonomous (along with the chooser code above) shows how to
 * select between different autonomous modes using the dashboard. The
 * sendable chooser code works with the Java SmartDashboard. If you
 * prefer the LabVIEW Dashboard, remove all of the chooser code and
 * uncomment the GetString line to get the auto name from the text box
 * below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to
 * the if-else structure below with additional strings. If using the
 * SendableChooser make sure to add them to the chooser code above as
 * well.
 */
/*
 void Robot::AutonomousInit() {

 }

 void Robot::AutonomousPeriodic(){

 }

 void Robot::DisabledInit() {

 }

 void Robot::TeleopInit(){

 }
 void Robot::TestInit(){

 }

 void Robot::RobotPeriodic(){

 }

 void Robot::DisabledPeriodic(){

 }

 void Robot::TeleopPeriodic() {

 }

 void Robot::TestPeriodic(){

 }

 void Robot::StartCompetition() {

 }
 */



