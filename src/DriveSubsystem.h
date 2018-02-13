
#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "AHRS.h"


class DriveSubsystem : public CORESubsystem {
public:
	DriveSubsystem();
	CORESwerve m_swerveDrive;
	AHRS *m_gyro = nullptr;
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	void setMotors();
	void resetEncoders();
	void initTalons();
	double getMotorSpeed(TalonSRX desiredMotor, int pididx);
	double getGyroYaw();
	void resetYaw();
	COREConstant <double> m_angleOffset;
	double m_drivePID_P, m_drivePID_I, m_drivePID_D;
	TalonSRX *m_rightFrontSteerMotor, *m_rightBackSteerMotor, *m_leftFrontSteerMotor, *m_leftBackSteerMotor,
		*m_rightFrontDriveMotor, *m_rightBackDriveMotor, *m_leftFrontDriveMotor, *m_leftBackDriveMotor;
	TalonSRX *rightFrontDriveMotor();
	TalonSRX *leftFrontDriveMotor();
	TalonSRX *rightBackDriveMotor();
	TalonSRX *leftBackDriveMotor();
	TalonSRX *rightFrontSteerMotor();
	TalonSRX *leftFrontSteerMotor();
	TalonSRX *rightBackSteerMotor();
	TalonSRX *leftBackSteerMotor();

private:
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;
	CORESwerve::SwerveModule m_rightFrontModule;
	CORESwerve::SwerveModule m_leftFrontModule;
	CORESwerve::SwerveModule m_rightBackModule;
	CORESwerve::SwerveModule m_leftBackModule;

};
