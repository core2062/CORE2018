
#include "DriveForwardAuton.h"
#include <CORERobotLib.h>

DriveForwardAuton::DriveForwardAuton(double speedInInches, double distanceInFeet) :
	COREAuton("Drive Forward Auton", 0.0) {
}

void DriveForwardAuton::addNodes() {
	m_moveForward->complete();
}
