#include "ctre/Phoenix.h"
#include "DriveSubsystem.h"
#include "Robot.h"

DriveSubsystem::DriveSubsystem() :
        m_pursuit(0, 0, 0, .1, m_path, false, 0),
        m_steerPID_P("Steer PID P"),
        m_steerPID_I("Steer PID I"),
        m_steerPID_D("Steer PID D"),
        m_rotationkP("Rotation P Value"),
        m_frontRightSteerMotor(FRONT_RIGHT_STEER_PORT),
        m_frontLeftSteerMotor(FRONT_LEFT_STEER_PORT),
        m_backRightSteerMotor(BACK_RIGHT_STEER_PORT),
        m_backLeftSteerMotor(BACK_LEFT_STEER_PORT),
        m_frontRightDriveMotor(FRONT_RIGHT_DRIVE_PORT),
        m_frontLeftDriveMotor(FRONT_LEFT_DRIVE_PORT),
        m_backRightDriveMotor(BACK_RIGHT_DRIVE_PORT),
        m_backLeftDriveMotor(BACK_LEFT_DRIVE_PORT),
        m_frontRightModule(new CORESwerve::SwerveModule(&m_frontRightDriveMotor, &m_frontRightSteerMotor)),
        m_frontLeftModule(new CORESwerve::SwerveModule(&m_frontLeftDriveMotor, &m_frontLeftSteerMotor)),
        m_backRightModule(new CORESwerve::SwerveModule(&m_backRightDriveMotor, &m_backRightSteerMotor)),
        m_backLeftModule(new CORESwerve::SwerveModule(&m_backLeftDriveMotor, &m_backLeftSteerMotor)) {
    m_swerveDrive = new CORESwerve(m_wheelbase, m_trackwidth, 3.0, 4915.2, m_frontLeftModule, m_backLeftModule,
                                   m_backRightModule, m_frontRightModule);

    try {
        m_gyro = new AHRS(SPI::Port::kMXP);
    } catch (std::exception ex) {
        CORELog::logError("Error initializing gyro: " + string(ex.what()));
    }
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
    if (SmartDashboard::GetBoolean("Zero Modules", false)) {
        SmartDashboard::PutBoolean("Zero Modules", false);
        CORELog::logWarning("Zeroing modules");
        m_swerveDrive->zeroOffsets();
    } else {
        m_swerveDrive->updateOffsets();
    }

    m_swerveDrive->inverseKinematics(0, 0, 0);
    m_swerveDrive->setSteerPID(m_steerPID_P.Get(), m_steerPID_I.Get(), m_steerPID_D.Get());
    SmartDashboard::PutBoolean("Field Oriented", true);
}

void DriveSubsystem::teleop() {
    if (m_gyro) {
        try {
            if (!m_gyro->IsConnected()) {
                CORELog::logError("Gyro has died!");
                SmartDashboard::PutBoolean("Field Oriented", false);
            }
        } catch (std::exception ex) {
            CORELog::logError("Error using gyro: " + string(ex.what()));
        }
    }

    //	Gets the joystick values for each of the functions
    double x = -driverJoystick->getAxis(COREJoystick::LEFT_STICK_X);
    double y = driverJoystick->getAxis(COREJoystick::LEFT_STICK_Y);
    if (abs(x) < 0.05) {
        x = 0;
    }
    if (abs(y) < 0.05) {
        y = 0;
    }
    double theta = -driverJoystick->getAxis(COREJoystick::RIGHT_STICK_X);
    if (abs(theta) < 0.05) {
        theta = 0;
    }

    theta *= 0.0602; //TODO: Someone should figure out what this value is/means

    if (m_gyro) {
        try {
            SmartDashboard::PutNumber("Gyro Yaw", getGyroYaw());

            double gyro_radians = toRadians(getGyroYaw());
            double temp = y * cos(gyro_radians) + x * sin(gyro_radians);
            x = -y * sin(gyro_radians) + x * cos(gyro_radians);
            y = temp;
        } catch (std::exception ex) {
            CORELog::logError("Error using gyro: " + string(ex.what()));
        }
    }

    m_swerveDrive->inverseKinematics(x, y, theta);

/*    auto result = m_swerveDrive->forwardKinematics();
    SmartDashboard::PutNumber("Returned Vector X", result.first);
    SmartDashboard::PutNumber("Returned Vector Y", result.second);

    m_x += (result.first * cos(gyro_radians) + result.second * sin(gyro_radians));
    m_y += (-result.first * sin(gyro_radians) + result.second * cos(gyro_radians));

    SmartDashboard::PutNumber("Total X", m_x);
    SmartDashboard::PutNumber("Total Y", m_y);*/
    try {
        if (driverJoystick->getRisingEdge(CORE::COREJoystick::START_BUTTON)) {
            CORELog::logWarning("Zeroing Yaw!");
            resetYaw();
        }
    } catch (std::exception ex) {
        CORELog::logError("Error using gyro: " + string(ex.what()));
    }

    SmartDashboard::PutNumber("Right Front Speed",
                              m_frontRightDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Front Speed", m_frontLeftDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Right Back Speed", m_backRightDriveMotor.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("Left Back Speed", m_backLeftDriveMotor.GetSensorCollection().GetQuadratureVelocity());

    SmartDashboard::PutNumber("Front Right Angle", m_frontRightModule->getAngle());
    SmartDashboard::PutNumber("Front Left Angle", m_frontLeftModule->getAngle());
    SmartDashboard::PutNumber("Back Right Angle", m_backRightModule->getAngle());
    SmartDashboard::PutNumber("Back Left Angle", m_backLeftModule->getAngle());

}

void DriveSubsystem::initTalons() {
    m_frontRightSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
    m_frontLeftSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
    m_backRightSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);
    m_backLeftSteerMotor.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::Analog, 0, 0);

    m_frontRightDriveMotor.ConfigSelectedFeedbackSensor(
            ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_frontLeftDriveMotor.ConfigSelectedFeedbackSensor(
            ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_backRightDriveMotor.ConfigSelectedFeedbackSensor(
            ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    m_backLeftDriveMotor.ConfigSelectedFeedbackSensor(
            ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

    m_frontRightSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_frontRightDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_frontLeftSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_backLeftSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_backRightSteerMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_backRightDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_backLeftDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_frontLeftDriveMotor.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

    m_frontLeftDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_frontRightDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_backLeftDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_backRightDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_frontLeftSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_frontRightSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_backLeftSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_backRightSteerMotor.Set(ControlMode::PercentOutput, 0);

    m_frontLeftSteerMotor.SetInverted(true);
    m_frontRightSteerMotor.SetInverted(true);
    m_backLeftSteerMotor.SetInverted(true);
    m_backRightSteerMotor.SetInverted(true);
    m_frontLeftDriveMotor.SetInverted(true);
    m_frontRightDriveMotor.SetInverted(true);
    m_backLeftDriveMotor.SetInverted(true);
    m_backRightDriveMotor.SetInverted(true);

    m_frontLeftDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_frontRightDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_backLeftDriveMotor.SetNeutralMode(NeutralMode::Brake);
    m_backRightDriveMotor.SetNeutralMode(NeutralMode::Brake);
}

void DriveSubsystem::resetYaw() {
    m_thetaOffset = 0;
    m_gyroOffset = 0;
    m_gyro->ZeroYaw();
}

double DriveSubsystem::getGyroYaw(bool raw) {
    if (raw) {
        return m_gyro->GetYaw();
    } else {
        return m_gyro->GetYaw() + toDegrees(m_thetaOffset) - m_gyroOffset;

    }
}

void DriveSubsystem::startPath(Path path, bool reversed, double maxAccel, double maxAngAccel,
                               double tolerance, bool gradualStop, double lookahead) {
    m_pursuit = AdaptivePursuit(lookahead, maxAccel, m_rotationkP.Get(), .025, path, reversed, tolerance, gradualStop);
}

void DriveSubsystem::resetTracker(Position2d initialPos) {
    m_x = initialPos.getTranslation().getX();
    m_y = initialPos.getTranslation().getY();
    m_theta = initialPos.getRotation().getRadians();
    m_thetaOffset = initialPos.getRotation().getRadians();
    m_swerveDrive->zeroEncoders();
    CORELog::logWarning("Initial position set to X: " + to_string(m_x) + " Y: " + to_string(m_y)
                        + " Theta: " + to_string(m_thetaOffset));
}

void DriveSubsystem::autonInitTask() {
    m_gyroOffset = getGyroYaw(true);
}

void DriveSubsystem::preLoopTask() {
    double gyro_radians = 0;
    if(m_gyro && m_gyro->IsConnected()) {
        gyro_radians= toRadians(getGyroYaw());
    }
    auto result = m_swerveDrive->forwardKinematics();

    m_x += (result.getTranslation().getX() * cos(gyro_radians) + result.getTranslation().getY() * sin(gyro_radians));
    m_y += (-result.getTranslation().getX() * sin(gyro_radians) + result.getTranslation().getY() * cos(gyro_radians));
    m_theta += result.getRotation().getRadians();

    SmartDashboard::PutNumber("Robot X", m_x);
    SmartDashboard::PutNumber("Robot Y", m_y);
    SmartDashboard::PutNumber("Robot Theta", m_theta);

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
        CORELog::logInfo("Gyro radians: " + to_string(gyro_radians) + " Requested theta: " + to_string(theta));
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
    m_frontLeftDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_frontRightDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_backLeftDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_backRightDriveMotor.Set(ControlMode::PercentOutput, 0);
    m_frontLeftSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_frontRightSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_backLeftSteerMotor.Set(ControlMode::PercentOutput, 0);
    m_backRightSteerMotor.Set(ControlMode::PercentOutput, 0);
}

//void DriveSubsystem::setMotors() {
//    m_timer.Start();
//    if (m_timer.getTime() < 3) {
//        m_leftFrontDriveMotor.Set(ControlMode::PercentOutput, 0.5);
//        m_rightFrontDriveMotor.Set(ControlMode::PercentOutput, 0.5);
//        m_leftBackDriveMotor.Set(ControlMode::PercentOutput, 0.5);
//        m_rightBackDriveMotor.Set(ControlMode::PercentOutput, 0.5);
//    }
//}
