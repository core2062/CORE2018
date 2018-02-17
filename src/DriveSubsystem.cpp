
#include "ctre/Phoenix.h"
#include "Robot.h"
#include "DriveSubsystem.h"
#include <cmath>
#include "COREHardware/COREJoystick.h"
#include "COREDrive/CORESwerveDrive.h"
#include "AHRS.h"
#include <wpilib.h>

DriveSubsystem::DriveSubsystem(CORE::COREJoystick * driverJoystick) :
	m_swerveDrive(20.8, 25.881, FRONT_LEFT_DRIVE_PORT, FRONT_LEFT_STEER_PORT, 0, BACK_LEFT_DRIVE_PORT, BACK_LEFT_STEER_PORT, 0,
			FRONT_RIGHT_DRIVE_PORT, FRONT_RIGHT_STEER_PORT, 0, BACK_RIGHT_DRIVE_PORT, BACK_RIGHT_STEER_PORT, 0),
	m_drivePID_P(0.001),
	m_drivePID_I(0),
	m_drivePID_D(0),
	m_gyro(new AHRS(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 200)) {
	m_driverJoystick = driverJoystick;
}

void DriveSubsystem::robotInit() {
    m_driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_X);
    m_driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_Y);
    m_driverJoystick->registerAxis(CORE::COREJoystick::RIGHT_STICK_X);
    SmartDashboard::PutBoolean("Zero Modules", false);

	//m_gyro = new AHRS(SerialPort::kUSB, AHRS::SerialDataType::kProcessedData, 200);
	//m_gyro
	/*try {
		SmartDashboard::PutBoolean("NavX initialized", true);
	} catch (std::exception & ex){
		SmartDashboard::PutBoolean("NavX initialized", false);
	}*/
	m_swerveDrive.init();


}

void DriveSubsystem::teleopInit() {
	SmartDashboard::PutBoolean("Reached teleop", true);
	double leftFrontOffset = Preferences::GetInstance()->GetDouble("Front Left Steer Offset", 0);
	double leftBackOffset = Preferences::GetInstance()->GetDouble("Back Left Steer Offset", 0);
	double rightFrontOffset = Preferences::GetInstance()->GetDouble("Front Right Steer Offset", 0);
	double rightBackOffset = Preferences::GetInstance()->GetDouble("Back Right Steer Offset", 0);

	m_swerveDrive.setAngleOffsets(leftFrontOffset, leftBackOffset, rightFrontOffset, rightBackOffset);
}

void DriveSubsystem::teleop() {

	SmartDashboard::PutNumber("Drive P Value", m_drivePID_P);
	SmartDashboard::PutNumber("Drive I Value", m_drivePID_I);
	SmartDashboard::PutNumber("Drive D Value", m_drivePID_D);

	//Sets PID for the modules
	m_swerveDrive.setSteerPID(m_drivePID_P, m_drivePID_I, m_drivePID_D);

	//	Gets the joystick values for each of the functions
	double x = m_driverJoystick->getAxis(COREJoystick::LEFT_STICK_X);
	double y = m_driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
	double theta = m_driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
	m_swerveDrive.setMotors(x, y, theta, getGyroYaw());

	SmartDashboard::PutNumber("Joy X", x);
	SmartDashboard::PutNumber("Joy Y", y);
	SmartDashboard::PutNumber("Joy Theta", theta);

	//	SmartDashboard::PutNumber("Right Front Speed", m_rightFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
	//	SmartDashboard::PutNumber("Left Front Speed", m_leftFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
	//	SmartDashboard::PutNumber("Right Back Speed", m_rightBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());
	//	SmartDashboard::PutNumber("Left Back Speed", m_leftBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());
	//
		SmartDashboard::PutNumber("Right Front Angle", m_swerveDrive.getRightFrontModuleAngle(false));
		SmartDashboard::PutNumber("Left Front Angle", m_swerveDrive.getLeftFrontModuleAngle(false));
		SmartDashboard::PutNumber("Right Back Angle", m_swerveDrive.getRightBackModuleAngle(false));
		SmartDashboard::PutNumber("Left Back Angle", m_swerveDrive.getLeftBackModuleAngle(false));
}

void DriveSubsystem::resetEncoders() {
	m_swerveDrive.resetEncoders();
}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw() {
	SmartDashboard::PutNumber("Gyro Yaw", m_gyro->GetYaw());
	return m_gyro->GetYaw();
}

void DriveSubsystem::teleopEnd() {
	m_swerveDrive.resetMotors();
}

void DriveSubsystem::testInit() {
    resetYaw();
    m_swerveDrive.zeroAngleOffsets();
    m_swerveDrive.setSteerPID(0, 0, 0);
}

void DriveSubsystem::test() {
    if(SmartDashboard::GetBoolean("Zero Modules", false)) {
        SmartDashboard::PutBoolean("Zero Modules", false);
        Preferences::GetInstance()->PutDouble("Front Left Steer Offset", m_swerveDrive.getLeftFrontModuleAngle(true));
        Preferences::GetInstance()->PutDouble("Front Right Steer Offset", m_swerveDrive.getRightFrontModuleAngle(true));
        Preferences::GetInstance()->PutDouble("Back Left Steer Offset", m_swerveDrive.getLeftBackModuleAngle(true));
        Preferences::GetInstance()->PutDouble("Back Right Steer Offset", m_swerveDrive.getRightBackModuleAngle(true));
    }
    SmartDashboard::PutNumber("Gyro Yaw", m_gyro->GetYaw());
    SmartDashboard::PutNumber("Front Left Steer Angle", m_swerveDrive.getLeftFrontModuleAngle(false));
    SmartDashboard::PutNumber("Front Right Steer Angle", m_swerveDrive.getRightFrontModuleAngle(false));
    SmartDashboard::PutNumber("Back Left Steer Angle", m_swerveDrive.getLeftBackModuleAngle(false));
    SmartDashboard::PutNumber("Back Right Steer Angle", m_swerveDrive.getRightBackModuleAngle(false));
}
