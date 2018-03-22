
#include "DriveForwardAuton.h"
#include <Robot.h>

DriveForwardAuton::DriveForwardAuton() :
	COREAuton("Drive Forward Auton") {
}

void DriveForwardAuton::addNodes() {
    addFirstNode(m_moveForward);
    m_moveForward = new Node(5, new DriveWaypointAction(
            CORE2018::GetInstance()->gameDataParser.loadPath(sidePath::DRIVE_FORWARD, false)));
}
