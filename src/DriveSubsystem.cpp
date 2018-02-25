#include "ctre/Phoenix.h"
#include "DriveSubsystem.h"
#include "Robot.h"
#include "COREHardware/COREJoystick.h"
#include "COREFramework/COREScheduler.h"

DriveSubsystem::DriveSubsystem() :
		m_rightFrontSteerMotor(0),
		m_leftFrontSteerMotor(0),
		m_rightBackSteerMotor(0),
		m_leftBackSteerMotor(0),
		m_rightFrontDriveMotor(0),
		m_leftFrontDriveMotor(0),
		m_rightBackDriveMotor(0),
		m_leftBackDriveMotor(0),
		m_rightFrontModule(new CORESwerve::SwerveModule(&m_rightFrontDriveMotor, &m_rightFrontSteerMotor)),
		m_rightBackModule(new CORESwerve::SwerveModule(&m_rightBackDriveMotor, &m_rightBackSteerMotor)),
		m_leftFrontModule(new CORESwerve::SwerveModule(&m_leftFrontDriveMotor, &m_leftFrontSteerMotor)),
		m_leftBackModule(new CORESwerve::SwerveModule(&m_leftBackDriveMotor, &m_leftBackSteerMotor)),
		m_swerveDrive(m_wheelbase, m_trackwidth, 3.0, 1228.8, m_leftFrontModule, m_leftBackModule, m_rightBackModule, m_rightFrontModule),
		m_steerPID_P("Steer PID P", 0.001),
		m_steerPID_I("Steer PID I", 0),
		m_steerPID_D("Steer PID D", 0),
		m_angleOffset("Swerve Steer Angle Offset", 0),
		m_gyro(new AHRS(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 200)) {

}

void DriveSubsystem::robotInit() {
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_X);
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->registerAxis(CORE::COREJoystick::RIGHT_STICK_X);
	SmartDashboard::PutBoolean("Zero Modules", false);

	//m_gyro = new AHRS(SerialPort::kUSB, AHRS::SerialDataType::kProcessedData, 200);
	//m_gyro
	/*try {
		SmartDashboard::PutBoolean("NavX initialized", true);
	} catch (std::exception & ex){
		SmartDashboard::PutBoolean("NavX initialized", false);
	}*/
	initTalons();
}

void DriveSubsystem::teleopInit() {
    m_swerveDrive.setSteerPID(m_steerPID_P.Get(), m_steerPID_I.Get(), m_steerPID_D.Get());
}

void DriveSubsystem::teleop() {
    CORELog::logInfo("Before getting joystick values");
	//	Gets the joystick values for each of the functions
    double x = driverJoystick->getAxis(COREJoystick::LEFT_STICK_X);
    double y = driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);

    double theta = driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
	CORELog::logInfo("After getting joystick values");


	double forward = y * cos(getGyroYaw() - m_angleOffset.Get()) + x *
                                                                   sin(getGyroYaw() - m_angleOffset.Get());
    double strafeRight = -y * sin(getGyroYaw() - m_angleOffset.Get()) +
                         x * cos(getGyroYaw() - m_angleOffset.Get());
    m_swerveDrive.calculate(forward, strafeRight, theta);
    m_swerveDrive.update();

	CORELog::logInfo("Before getting stuff from sensor collection");
    SmartDashboard::PutNumber("Right Front Speed", m_rightFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Front Speed", m_leftFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Right Back Speed", m_rightBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Back Speed", m_leftBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());
	CORELog::logInfo("After getting stuff from sensor collection");

    SmartDashboard::PutNumber("Right Front Angle", m_rightFrontModule->getAngle());
    SmartDashboard::PutNumber("Left Front Angle", m_leftFrontModule->getAngle());
    SmartDashboard::PutNumber("Right Back Angle", m_rightBackModule->getAngle());
    SmartDashboard::PutNumber("Left Back Angle", m_leftBackModule->getAngle());
}

void DriveSubsystem::resetEncoders() {
	m_rightFrontSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftFrontSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightBackSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftBackSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightFrontDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftFrontDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_rightBackDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
	m_leftBackDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 10);
}

void DriveSubsystem::initTalons() {
	m_rightFrontSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
	m_leftFrontSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
	m_rightBackSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
	m_leftBackSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);

	m_rightFrontDriveMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
	m_leftFrontDriveMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
	m_rightBackDriveMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
	m_leftBackDriveMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

	m_rightFrontSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_rightFrontDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_leftFrontSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_leftBackSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_rightBackSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_rightBackDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_leftBackDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
	m_leftFrontDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

	m_leftFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_rightFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_leftBackDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_rightBackDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_leftFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_rightFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_leftBackSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_rightBackSteerMotor.Set(ControlMode::PercentOutput, 0);
}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw() {
	SmartDashboard::PutNumber("Gyro Yaw", m_gyro->GetYaw());
	return m_gyro->GetYaw();
}

void DriveSubsystem::teleopEnd() {
	m_leftFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_rightFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_leftBackDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_rightBackDriveMotor.Set(ControlMode::PercentOutput, 0);
	m_leftFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_rightFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_leftBackSteerMotor.Set(ControlMode::PercentOutput, 0);
	m_rightBackSteerMotor.Set(ControlMode::PercentOutput, 0);
}

void DriveSubsystem::testInit() {
	resetYaw();

	m_leftFrontModule->setAngleOffset(0);
	m_rightFrontModule->setAngleOffset(0);
	m_leftBackModule->setAngleOffset(0);
	m_rightBackModule->setAngleOffset(0);
	m_leftFrontModule->setAnglePID(0, 0, 0);
	m_rightFrontModule->setAnglePID(0, 0, 0);
	m_leftBackModule->setAnglePID(0, 0, 0);
	m_rightBackModule->setAnglePID(0, 0, 0);
}

void DriveSubsystem::test() {
	if(SmartDashboard::GetBoolean("Zero Modules", false)) {
		SmartDashboard::PutBoolean("Zero Modules", false);
		Preferences::GetInstance()->PutDouble("Front Left Steer Offset", m_leftFrontModule->getAngle(true));
		Preferences::GetInstance()->PutDouble("Front Right Steer Offset", m_rightFrontModule->getAngle(true));
		Preferences::GetInstance()->PutDouble("Back Left Steer Offset", m_leftBackModule->getAngle(true));
		Preferences::GetInstance()->PutDouble("Back Right Steer Offset", m_rightBackModule->getAngle(true));
	}
	SmartDashboard::PutNumber("Gyro Yaw", m_gyro->GetYaw());
	SmartDashboard::PutNumber("Front Left Steer Angle", m_leftFrontModule->getAngle());
	SmartDashboard::PutNumber("Front Right Steer Angle", m_rightFrontModule->getAngle());
	SmartDashboard::PutNumber("Back Left Steer Angle", m_leftBackModule->getAngle());
	SmartDashboard::PutNumber("Back Right Steer Angle", m_rightBackModule->getAngle());
}
