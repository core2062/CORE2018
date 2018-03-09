#include "ctre/Phoenix.h"
#include "DriveSubsystem.h"
#include "Robot.h"
#include "COREHardware/COREJoystick.h"
#include "COREFramework/COREScheduler.h"

DriveSubsystem::DriveSubsystem() :
		m_rightFrontSteerMotor(FRONT_RIGHT_STEER_PORT),
		m_leftFrontSteerMotor(FRONT_LEFT_STEER_PORT),
		m_rightBackSteerMotor(BACK_RIGHT_STEER_PORT),
		m_leftBackSteerMotor(BACK_LEFT_STEER_PORT),
		m_rightFrontDriveMotor(FRONT_RIGHT_DRIVE_PORT),
		m_leftFrontDriveMotor(FRONT_LEFT_DRIVE_PORT),
		m_rightBackDriveMotor(BACK_RIGHT_DRIVE_PORT),
		m_leftBackDriveMotor(BACK_LEFT_DRIVE_PORT),
		m_rightFrontModule(new CORESwerve::SwerveModule(&m_rightFrontDriveMotor, &m_rightFrontSteerMotor)),
		m_rightBackModule(new CORESwerve::SwerveModule(&m_rightBackDriveMotor, &m_rightBackSteerMotor)),
		m_leftFrontModule(new CORESwerve::SwerveModule(&m_leftFrontDriveMotor, &m_leftFrontSteerMotor)),
		m_leftBackModule(new CORESwerve::SwerveModule(&m_leftBackDriveMotor, &m_leftBackSteerMotor)),
		m_steerPID_P("Steer PID P", 0.005),
		m_steerPID_I("Steer PID I", 0),
		m_steerPID_D("Steer PID D", 0),
		m_pursuit(0, 0, .1, m_path, false, 0),
		m_gyro(new AHRS(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 200)) {
    m_swerveDrive = new CORESwerve(m_wheelbase, m_trackwidth, 3.0, 1228.8, m_leftFrontModule, m_leftBackModule, m_rightBackModule, m_rightFrontModule);
}

void DriveSubsystem::robotInit() {
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_X);
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->registerAxis(CORE::COREJoystick::RIGHT_STICK_X);
	driverJoystick->registerButton(CORE::COREJoystick::START_BUTTON);
	SmartDashboard::PutBoolean("Zero Modules", false);
    resetYaw();
	initTalons();
}

void DriveSubsystem::teleopInit() {
    if(SmartDashboard::GetBoolean("Zero Modules", false)) {
        SmartDashboard::PutBoolean("Zero Modules", false);
        CORELog::logInfo("Zeroing modules");
        m_swerveDrive->zeroOffsets();
    }
    m_swerveDrive->calculate(0, 0, 0);
    m_swerveDrive->update();
    m_swerveDrive->setSteerPID(m_steerPID_P.Get(), m_steerPID_I.Get(), m_steerPID_D.Get());
}

void DriveSubsystem::teleop() {
	//	Gets the joystick values for each of the functions
    double x = -1 * driverJoystick->getAxis(COREJoystick::LEFT_STICK_X);
    double y = driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
	SmartDashboard::PutNumber("Joystick X", x);
    SmartDashboard::PutNumber("Joystick Y", y);
    if(abs(x) < 0.05) {
        x = 0;
    }
    if(abs(y) < 0.05) {
        y = 0;
    }

    SmartDashboard::PutNumber("Gyro Yaw", getGyroYaw());

	double theta = driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);

    double gyro_radians = toRadians(getGyroYaw());
    double temp = y * cos(gyro_radians) + x * sin(gyro_radians);
    x = -y * sin(gyro_radians) + x * cos(gyro_radians);
    y = temp;
    m_swerveDrive->calculate(x, y, -theta);
    m_swerveDrive->update();

    if (driverJoystick->getRisingEdge(CORE::COREJoystick::START_BUTTON)) {
		CORELog::logWarning("Zeroing Yaw!");
    	resetYaw();
    }

    SmartDashboard::PutNumber("Right Front Speed", m_rightFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Front Speed", m_leftFrontDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Right Back Speed", m_rightBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Back Speed", m_leftBackDriveMotor.GetSensorCollection().GetQuadratureVelocity());

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

    m_leftFrontSteerMotor.SetInverted(true);
    m_rightFrontSteerMotor.SetInverted(true);
    m_leftBackSteerMotor.SetInverted(true);
    m_rightBackSteerMotor.SetInverted(true);
    m_leftFrontDriveMotor.SetInverted(true);
    m_rightFrontDriveMotor.SetInverted(true);
    m_leftBackDriveMotor.SetInverted(true);
    m_rightBackDriveMotor.SetInverted(true);
}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw() {
	return m_gyro->GetYaw();
}

void DriveSubsystem::startPath(Path path, bool reversed,
		double maxAccel, double tolerance, bool gradualStop, double lookahead) {
	m_pursuit = AdaptivePursuit(lookahead, maxAccel, .025, path, reversed, tolerance, gradualStop);
}

void DriveSubsystem::resetTracker(Position2d initialPos) {
	m_swerveTracker->reset(Timer::GetFPGATimestamp(), initialPos);
}

void DriveSubsystem::autonInit() {
	Position2d startingPosition;
	resetTracker(startingPosition);

}

void DriveSubsystem::auton() {
	if (!m_pursuit.isDone()) {
		Position2d pos;
		if (frame == nullptr) {
			pos = m_swerveTracker->getLatestFieldToVehicle();
		} else {
			pos = frame->getLatest(path);
		}
		Position2d::Delta command = m_pursuit.update(pos,
				Timer::GetFPGATimestamp());
		COREVector setpoint = m_swerveDrive->inverseKinematics();
		double maxVel = 0.0;
		maxVel = max(maxVel, setpoint.GetX());
		if (maxVel > 100) {
			setpoint = COREVector(setpoint.GetX(), setpoint.GetY());
		}
	} else {

	}

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

void DriveSubsystem::autonInitTask() {
    CORELog::logInfo("Test");
    resetYaw();
    m_leftFrontModule->setAngleOffset(0);
    m_rightFrontModule->setAngleOffset(0);
    m_leftBackModule->setAngleOffset(0);
    m_rightBackModule->setAngleOffset(0);
    m_leftFrontModule->setAnglePID(0, 0, 0);
    m_rightFrontModule->setAnglePID(0, 0, 0);
    m_leftBackModule->setAnglePID(0, 0, 0);
    m_rightBackModule->setAnglePID(0, 0, 0);

	SmartDashboard::PutNumber("Gyro Yaw", m_gyro->GetYaw());
	SmartDashboard::PutNumber("Front Left Steer Angle", m_leftFrontModule->getAngle());
	SmartDashboard::PutNumber("Front Right Steer Angle", m_rightFrontModule->getAngle());
	SmartDashboard::PutNumber("Back Left Steer Angle", m_leftBackModule->getAngle());
	SmartDashboard::PutNumber("Back Right Steer Angle", m_rightBackModule->getAngle());
}
