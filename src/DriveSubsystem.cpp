#include "ctre/Phoenix.h"
#include "DriveSubsystem.h"
#include "Robot.h"
#include "COREHardware/COREJoystick.h"
#include "COREFramework/COREScheduler.h"
#include "COREUtilities/COREVector.h"
#include "Timer.h"
#include "SerialPort.h"
#include "CORELogging/CORELog.h"

DriveSubsystem::DriveSubsystem() :
		m_pursuit(0, 0, 0, .1, m_path, false, 0),
		m_steerPID_P("Steer PID P"),
		m_steerPID_I("Steer PID I"),
		m_steerPID_D("Steer PID D"),
		m_rightFrontSteerMotor(FRONT_RIGHT_STEER_PORT),
		m_leftFrontSteerMotor(FRONT_LEFT_STEER_PORT),
		m_rightBackSteerMotor(BACK_RIGHT_STEER_PORT),
		m_leftBackSteerMotor(BACK_LEFT_STEER_PORT),
		m_rightFrontDriveMotor(FRONT_RIGHT_DRIVE_PORT),
		m_leftFrontDriveMotor(FRONT_LEFT_DRIVE_PORT),
		m_rightBackDriveMotor(BACK_RIGHT_DRIVE_PORT),
		m_leftBackDriveMotor(BACK_LEFT_DRIVE_PORT),
		m_rightFrontModule(new CORESwerve::SwerveModule(&m_rightFrontDriveMotor, &m_rightFrontSteerMotor)),
		m_leftFrontModule(new CORESwerve::SwerveModule(&m_leftFrontDriveMotor, &m_leftFrontSteerMotor)),
		m_rightBackModule(new CORESwerve::SwerveModule(&m_rightBackDriveMotor, &m_rightBackSteerMotor)),
		m_leftBackModule(new CORESwerve::SwerveModule(&m_leftBackDriveMotor, &m_leftBackSteerMotor)),
		m_gyro(new AHRS(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 60)) {
    m_swerveDrive = new CORESwerve(m_wheelbase, m_trackwidth, 3.0, 4915.2, m_leftFrontModule, m_leftBackModule, m_rightBackModule, m_rightFrontModule);
//    m_swerveTracker = SwerveTracker::GetInstance();
//    m_swerveTracker->injectCORESwerve(m_swerveDrive);
}

void DriveSubsystem::robotInit() {
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_X);
	driverJoystick->registerAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->registerAxis(CORE::COREJoystick::RIGHT_STICK_X);
	driverJoystick->registerButton(CORE::COREJoystick::START_BUTTON);
	SmartDashboard::PutBoolean("Zero Modules", false);
    m_swerveDrive->inverseKinematics(0, 0, 0);
    m_swerveDrive->setSteerPID(m_steerPID_P.Get(), m_steerPID_I.Get(), m_steerPID_D.Get());
    resetYaw();
	initTalons();
    m_swerveDrive->updateOffsets();
}

void DriveSubsystem::teleopInit() {
    if(SmartDashboard::GetBoolean("Zero Modules", false)) {
        SmartDashboard::PutBoolean("Zero Modules", false);
        CORELog::logWarning("Zeroing modules");
        m_swerveDrive->zeroOffsets();
    } else
        m_swerveDrive->updateOffsets();

    m_swerveDrive->inverseKinematics(0, 0, 0);
    m_swerveDrive->setSteerPID(m_steerPID_P.Get(), m_steerPID_I.Get(), m_steerPID_D.Get());
    m_x = 0;
    m_y = 0;
}

void DriveSubsystem::teleop() {
    if(!m_gyro->IsConnected()) {
        CORELog::logError("Gyro has died!");
        m_gyro = new AHRS(SerialPort::Port::kUSB, AHRS::SerialDataType::kProcessedData, 100);
    }
	//	Gets the joystick values for each of the functions
    double x = -driverJoystick->getAxis(COREJoystick::LEFT_STICK_X);
    double y = driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
    if(abs(x) < 0.05) {
        x = 0;
    }
    if(abs(y) < 0.05) {
        y = 0;
    }

    SmartDashboard::PutNumber("Gyro Yaw", getGyroYaw());

	double theta = -driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
    if(abs(theta) < 0.05) {
        theta = 0;
    }

    double gyro_radians = toRadians(getGyroYaw());
    double temp = y * cos(gyro_radians) + x * sin(gyro_radians);
    x = -y * sin(gyro_radians) + x * cos(gyro_radians);
    y = temp;

    m_swerveDrive->inverseKinematics(x, y, theta);

    auto result = m_swerveDrive->forwardKinematics();
    SmartDashboard::PutNumber("Returned Vector X", result.first);
    SmartDashboard::PutNumber("Returned Vector Y", result.second);

    m_x += (result.first * cos(gyro_radians) + result.second * sin(gyro_radians));
    m_y += (-result.first * sin(gyro_radians) + result.second * cos(gyro_radians));

    SmartDashboard::PutNumber("Total X", m_x);
    SmartDashboard::PutNumber("Total Y", m_y);

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
	m_rightFrontSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_leftFrontSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_rightBackSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_leftBackSteerMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_rightFrontDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_leftFrontDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_rightBackDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
	m_leftBackDriveMotor.GetSensorCollection().SetQuadraturePosition(0, 0);
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

    m_leftFrontDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightFrontDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_leftBackDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_rightBackDriveMotor.SetNeutralMode(NeutralMode::Brake);
}

void DriveSubsystem::resetYaw() {
	m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw(bool raw) {
    if(raw) {
        return m_gyro->GetYaw();
    } else {
        return m_gyro->GetYaw() + m_theta - m_gyroOffset;

    }
}

void DriveSubsystem::startPath(Path path, Position2d startPos, bool reversed, double maxAccel, double maxAngAccel,
                               double tolerance, bool gradualStop, double lookahead) {
    m_x = startPos.getTranslation().getX();
    m_y = startPos.getTranslation().getY();
    m_theta = startPos.getRotation().getDegrees();
    CORELog::logInfo("Theta Angle: " + to_string(m_theta));
    m_swerveDrive->zeroEncoders();
	m_pursuit = AdaptivePursuit(lookahead, maxAccel, maxAngAccel, .025, path, reversed, tolerance, gradualStop);
}

void DriveSubsystem::resetTracker(Position2d initialPos) {
    m_x = initialPos.getTranslation().getX();
    m_y = initialPos.getTranslation().getY();
    m_theta = initialPos.getRotation().getRadians();
    CORELog::logWarning("Initial position set to X: " + to_string(m_x) + " Y: " + to_string(m_y)
                        + " Theta: " + to_string(m_theta));
}

void DriveSubsystem::autonInitTask() {
	/*Position2d startingPosition;
	resetTracker(startingPosition);
	m_swerveTracker->start();*/
    m_gyroOffset = getGyroYaw(true);
}

void DriveSubsystem::preLoopTask() {
    double gyro_radians = toRadians(getGyroYaw());
    auto result = m_swerveDrive->forwardKinematics();

    m_x += (result.first * cos(gyro_radians) + result.second * sin(gyro_radians));
    m_y += (-result.first * sin(gyro_radians) + result.second * cos(gyro_radians));

    SmartDashboard::PutNumber("Robot X", m_x);
    SmartDashboard::PutNumber("Robot Y", m_y);

    if (!m_pursuit.isDone() && CORE::COREDriverstation::getMode() == CORE::COREDriverstation::AUTON) {
        Position2d pos(Translation2d(m_x, m_y), Rotation2d::fromRadians(gyro_radians));
        Position2d::Delta command = m_pursuit.update(pos, Timer::GetFPGATimestamp());

        double maxVel = 0.0;
        maxVel = max(maxVel, command.dx);
        if (maxVel > 1) {
            double scaling = 1 / maxVel;
            command.dx *= scaling;
        }
        maxVel = 0.0;
        maxVel = max(maxVel, command.dy);
        if (maxVel > 1) {
            double scaling = 1 / maxVel;
            command.dy *= scaling;
        }

        double y = -command.dy;
        double x = -command.dx;
        double temp = y * cos(gyro_radians) + x * sin(gyro_radians);
        x = -y * sin(gyro_radians) + x * cos(gyro_radians);
        y = temp;

        double theta = -command.dtheta;
        m_swerveDrive->inverseKinematics(x, y, theta);
    }
}

void DriveSubsystem::teleopEnd() {
	zeroMotors();
}

bool DriveSubsystem::pathDone() {
    return m_pursuit.isDone();
}
void DriveSubsystem::zeroMotors() {
    m_leftFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_rightFrontDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_leftBackDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_rightBackDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_leftFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_rightFrontSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_leftBackSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_rightBackSteerMotor.Set(ControlMode::PercentOutput, 0);
}
