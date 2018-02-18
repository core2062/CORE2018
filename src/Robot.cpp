/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>
#include "ctre/Phoenix.h"

CORE2018::CORE2018() :
		m_driverJoystick(0),
		m_operatorJoystick(1)
		/*driveSubsystem(&m_driverJoystick)*/ {
}

CORE2018::~CORE2018() {

}

void CORE2018::RobotInit() {
	//driveSubsystem.robotInit();
}

void CORE2018::RobotPeriodic() {
}

void CORE2018::DisabledInit() {
}

void CORE2018::DisabledPeriodic() {
	//driveSubsystem.m_swerveDrive.haltMotors();
}

void CORE2018::TeleopInit() {
	std::cout<<"Reached teleop init"<<std::endl;
	//driveSubsystem.teleopInit();
}

void CORE2018::TeleopPeriodic() {
	//driveSubsystem.teleop();
	SmartDashboard::PutNumber("Joystick Value", m_driverJoystick.GetAxis(frc::Joystick::kThrottleAxis));
	SmartDashboard::PutNumber("Joystick Axis Value", m_operatorJoystick.GetAxis(frc::Joystick::kTwistAxis));
	std::cout<<"Reached teleop"<<std::endl;
}

void CORE2018::AutonomousInit() {
}

void CORE2018::AutonomousPeriodic() {
}

void CORE2018::TestInit() {
	std::cout<<"Reached test init";
	//driveSubsystem.testInit();
}

void CORE2018::TestPeriodic() {
	//driveSubsystem.test();
}

START_ROBOT_CLASS(CORE2018)
