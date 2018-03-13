#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include <CORERobotLib.h>
#include "COREKinematics/SwerveTracker.h"
#include "AHRS.h"
#include "COREFramework/COREScheduler.h"


class DriveSubsystem : public CORESubsystem, public CORETask {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	void preLoopTask();
	void resetEncoders();
	void initTalons();
	void autonInitTask() override;
	double getGyroYaw();
	bool pathDone();
	void resetYaw();


	void startPath(Path path, bool reversed = false, double maxAccel = 25.0,
			double tolerance = .25, bool gradualStop = true, double lookahead = 0.0);
	void resetTracker(Position2d initialPos);
	Path m_path;
	SwerveTracker *m_swerveTracker= nullptr;
	AdaptivePursuit m_pursuit;
	RobotFrame *frame = nullptr;
	COREVector path;

private:
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;
	double m_fudgeFactor = 1.0;
	COREConstant <double> m_steerPID_P, m_steerPID_I, m_steerPID_D;
	TalonSRX m_rightFrontSteerMotor, m_leftFrontSteerMotor, m_rightBackSteerMotor, m_leftBackSteerMotor,
			m_rightFrontDriveMotor, m_leftFrontDriveMotor, m_rightBackDriveMotor, m_leftBackDriveMotor;
	CORESwerve::SwerveModule *m_rightFrontModule, *m_leftFrontModule, *m_rightBackModule, *m_leftBackModule;
	CORESwerve* m_swerveDrive;
	AHRS *m_gyro;
	COREVector m_total;
	double m_x, m_y;
    int count = 0;
};
