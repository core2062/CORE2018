
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "DriveSubsystem.h"
#include <cmath>
#include "COREHardware/COREJoystick.h"
#include "wpilib.h"

DriveSubsystem::DriveSubsystem() :
	m_rightFrontSteerMotor(new TalonSRX(FRONT_RIGHT_STEER_PORT)),
	m_leftFrontSteerMotor(new TalonSRX(FRONT_LEFT_STEER_PORT)),
	m_rightBackSteerMotor(new TalonSRX(BACK_RIGHT_STEER_PORT)),
	m_leftBackSteerMotor(new TalonSRX(BACK_LEFT_STEER_PORT)),
	m_rightFrontDriveMotor(new TalonSRX(FRONT_RIGHT_DRIVE_PORT)),
	m_leftFrontDriveMotor(new TalonSRX(FRONT_LEFT_DRIVE_PORT)),
	m_rightBackDriveMotor(new TalonSRX(BACK_RIGHT_DRIVE_PORT)),
	m_leftBackDriveMotor(new TalonSRX(BACK_LEFT_DRIVE_PORT)),
	m_rightFrontModule(m_rightFrontDriveMotor, m_rightFrontSteerMotor),
	m_rightBackModule(m_rightBackDriveMotor, m_rightBackSteerMotor),
	m_leftFrontModule(m_leftFrontDriveMotor, m_leftFrontSteerMotor),
	m_leftBackModule(m_leftBackDriveMotor, m_leftBackSteerMotor),
	m_swerveDrive(m_wheelbase, m_trackwidth, &m_leftFrontModule, &m_leftBackModule, &m_rightBackModule, &m_rightFrontModule),
	m_drivePID_P(0),
	m_drivePID_I(0),
	m_drivePID_D(0),
	m_angleOffset("Swerve Steer Angle Offset", 0) {

}

void DriveSubsystem::robotInit() {
	Robot->m_driverJoystick.getAxis(CORE::COREJoystick::LEFT_STICK_Y);
	Robot->m_driverJoystick.getAxis(CORE::COREJoystick::RIGHT_STICK_X);
	initTalons();

}

void DriveSubsystem::teleopInit() {

}

void DriveSubsystem::teleop() {
	initTalons();
	setMotors();

}

void DriveSubsystem::setMotors() {
	/*SmartDashboard::PutNumber("Drive P Value", m_drivePID_P);
	SmartDashboard::PutNumber("Drive I Value", m_drivePID_I);
	SmartDashboard::PutNumber("Drive D Value", m_drivePID_D);
	//Sets PID for the modules
	m_rightFrontModule.setAnglePID(m_drivePID_P, m_drivePID_I, m_drivePID_D);
	m_rightBackModule.setAnglePID(m_drivePID_P, m_drivePID_I, m_drivePID_D);
	m_leftFrontModule.setAnglePID(m_drivePID_P, m_drivePID_I, m_drivePID_D);
	m_leftBackModule.setAnglePID(m_drivePID_P, m_drivePID_I, m_drivePID_D);

	//Gets the joystick values for each of the functions
	double y = robot->m_driverJoystick.getAxis(COREJoystick::LEFT_STICK_Y);
	double x = robot->m_driverJoystick.getAxis(COREJoystick::LEFT_STICK_X);
	double z = robot->m_driverJoystick.getAxis(COREJoystick::RIGHT_STICK_X);

	double forward = y * cos(DriveSubsystem::getGyroYaw() - m_angleOffset.Get()) + x *
			sin(DriveSubsystem::getGyroYaw() - m_angleOffset.Get());
	double strafeRight = -y * sin(DriveSubsystem::getGyroYaw() - m_angleOffset.Get()) +
			x * cos(DriveSubsystem::getGyroYaw() - m_angleOffset.Get());
	m_swerveDrive.calculate(forward, strafeRight, z);
	m_swerveDrive.update();
	SmartDashboard::PutNumber("Right Front Speed", m_rightFrontDriveMotor->GetSensorCollection().GetQuadratureVelocity());
	SmartDashboard::PutNumber("Left Front Speed", m_leftFrontDriveMotor->GetSensorCollection().GetQuadratureVelocity());
	SmartDashboard::PutNumber("Right Back Speed", m_rightBackDriveMotor->GetSensorCollection().GetQuadratureVelocity());
	SmartDashboard::PutNumber("Left Back Speed", m_leftBackDriveMotor->GetSensorCollection().GetQuadratureVelocity());
	SmartDashboard::PutNumber("Right Front Angle", m_rightFrontSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Left Front Angle", m_leftFrontSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Right Back Angle", m_rightBackSteerMotor->GetSensorCollection().GetQuadraturePosition());
	SmartDashboard::PutNumber("Left Back Angle", m_leftBackSteerMotor->GetSensorCollection().GetQuadraturePosition());*/
}

void DriveSubsystem::resetEncoders() {
	m_rightFrontSteerMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftFrontSteerMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightBackSteerMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftBackSteerMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightFrontDriveMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftFrontDriveMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightBackDriveMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftBackDriveMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
}

void DriveSubsystem::initTalons() {

	m_rightFrontSteerMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 150);
	m_leftFrontSteerMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 150);
	m_rightBackSteerMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 150);
	m_leftBackSteerMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 150);
	m_rightFrontDriveMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 150);
	m_leftFrontDriveMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 150);
	m_rightBackDriveMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 150);
	m_leftBackDriveMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 150);

	m_rightFrontSteerMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_rightFrontDriveMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_leftFrontSteerMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_leftBackSteerMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_rightBackSteerMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_rightBackDriveMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_leftBackDriveMotor->SetStatusFramePeriod(Status_1_General, 10, 150);
	m_leftFrontDriveMotor->SetStatusFramePeriod(Status_1_General, 10, 150);

	m_leftFrontDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_rightFrontDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_leftBackDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_rightBackDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_leftFrontSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_rightFrontSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_leftBackSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_rightBackSteerMotor->Set(ControlMode::PercentOutput, 0);


}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw() {
	SmartDashboard::PutNumber("Gyro Yaw", 0);
	return m_gyro->GetYaw();
}

double DriveSubsystem::getMotorSpeed(TalonSRX desiredMotor, int pididx) {
	return desiredMotor.GetSelectedSensorVelocity(pididx);
}

void DriveSubsystem::teleopEnd() {
	m_leftFrontDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_rightFrontDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_leftBackDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_rightBackDriveMotor->Set(ControlMode::PercentOutput, 0);
	m_leftFrontSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_rightFrontSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_leftBackSteerMotor->Set(ControlMode::PercentOutput, 0);
	m_rightBackSteerMotor->Set(ControlMode::PercentOutput, 0);
}

TalonSRX* DriveSubsystem::rightFrontDriveMotor() {
	return m_rightFrontDriveMotor;
}

TalonSRX* DriveSubsystem::leftFrontDriveMotor() {
	return m_leftFrontDriveMotor;
}

TalonSRX* DriveSubsystem::rightBackDriveMotor() {
	return m_rightBackDriveMotor;
}

TalonSRX* DriveSubsystem::leftBackDriveMotor() {
	return m_leftBackDriveMotor;
}

TalonSRX* DriveSubsystem::rightFrontSteerMotor() {
	return m_rightFrontSteerMotor;
}

TalonSRX* DriveSubsystem::leftFrontSteerMotor() {
	return m_leftFrontSteerMotor;
}

TalonSRX* DriveSubsystem::rightBackSteerMotor() {
	return m_rightBackSteerMotor;
}

TalonSRX* DriveSubsystem::leftBackSteerMotor() {
	return m_leftBackSteerMotor;
}
