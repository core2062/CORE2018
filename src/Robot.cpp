/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>
#include "ctre/Phoenix.h"
CORE2018 * Robot = nullptr;

CORE2018::CORE2018() :
	driveSubsystem(),
	m_driverJoystick(0),
	m_operatorJoystick(1) {
	Robot = this;
}
CORE2018::~CORE2018() {
	Robot = nullptr;

}

void CORE2018::RobotInit() {
	driveSubsystem.robotInit();
}

void CORE2018::DisabledInit() {
}

void CORE2018::TeleopPeriodic() {
	driveSubsystem.teleop();
}

 void CORE2018::AutonomousInit() {

 }
 void CORE2018::AutonomousPeriodic(){
 }
 void CORE2018::TeleopInit(){
	 driveSubsystem.teleopInit();
 }
 void CORE2018::TestInit() {
	 driveSubsystem.teleopInit();

 }
 void CORE2018::RobotPeriodic(){
 }
 void CORE2018::DisabledPeriodic(){
	SmartDashboard::PutNumber("Disabled Right Front Angle", driveSubsystem.m_rightFrontSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Disabled Left Front Angle", driveSubsystem.m_leftFrontSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Disabled Right Back Angle", driveSubsystem.m_rightBackSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Disabled Left Back Angle", driveSubsystem.m_leftBackSteerMotor->GetSensorCollection().GetQuadraturePosition());
 }

 void CORE2018::TestPeriodic(){
 }

START_ROBOT_CLASS(CORE2018)
