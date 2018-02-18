#pragma once

//#include "Robot.h"
#include "ctre/Phoenix.h"
#include "CORERobotLib.h"
#include "AHRS.h"
#include "COREHardware/COREJoystick.h"

class DriveSubsystem : public CORESubsystem {
private:
	COREJoystick * m_driverJoystick;
	double m_wheelbase = 20.8;
	double m_trackwidth = 25.881;

public:
	DriveSubsystem(COREJoystick * driverJoystick);
	CORESwerve m_swerveDrive;
	void robotInit();
	void teleopInit();
	void teleop();
	void teleopEnd();
	void resetEncoders();
	void test() override;
    void testInit();
	double getGyroYaw();
	void resetYaw();
	double m_drivePID_P, m_drivePID_I, m_drivePID_D;
	AHRS *m_gyro;

};
