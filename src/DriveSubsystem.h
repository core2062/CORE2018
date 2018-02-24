#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "AHRS.h"


class DriveSubsystem : public CORESubsystem {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	void resetEncoders();
	void initTalons();
	void test() override;
	void testInit();
	double getGyroYaw();
	void resetYaw();

private:
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;
	CORESwerve m_swerveDrive;
	AHRS *m_gyro;
	COREConstant <double> m_angleOffset, m_steerPID_P, m_steerPID_I, m_steerPID_D;
	CORESwerve::SwerveModule *m_rightFrontModule, *m_leftFrontModule, *m_rightBackModule, *m_leftBackModule;
	TalonSRX m_rightFrontSteerMotor, m_rightBackSteerMotor, m_leftFrontSteerMotor, m_leftBackSteerMotor,
			m_rightFrontDriveMotor, m_rightBackDriveMotor, m_leftFrontDriveMotor, m_leftBackDriveMotor;
};
