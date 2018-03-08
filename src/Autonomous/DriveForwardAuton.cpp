
#include "DriveForwardAuton.h"
#include <CORERobotLib.h>

DriveForwardAuton::DriveForwardAuton(double speedInInches, double distanceInFeet) :
	COREAuton("Drive Forward Auton") {
	m_moveForward = new Node(5, new DriveDistanceAction());
}

void DriveForwardAuton::addNodes() {

}
