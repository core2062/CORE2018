#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include "AHRS.h"
#include "COREFramework/COREScheduler.h"


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
	double m_fudgeFactor = 1.0;
	double m_wheelCircumference = 0.0;
	double m_ticksToRotation = 0.0;
	TalonSRX m_rightFrontSteerMotor, m_leftFrontSteerMotor, m_rightBackSteerMotor, m_leftBackSteerMotor,
			m_rightFrontDriveMotor, m_leftFrontDriveMotor, m_rightBackDriveMotor, m_leftBackDriveMotor;
	CORESwerve::SwerveModule *m_rightFrontModule, *m_rightBackModule, *m_leftFrontModule, *m_leftBackModule;
	CORESwerve m_swerveDrive;
	COREConstant <double> m_steerPID_P, m_steerPID_I, m_steerPID_D, m_angleOffset;
	AHRS *m_gyro;
};
