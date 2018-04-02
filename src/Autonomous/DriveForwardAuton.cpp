
#include "DriveForwardAuton.h"
#include <Robot.h>

DriveForwardAuton::DriveForwardAuton() :
	COREAuton("Drive Forward No Encoders") {
}

void DriveForwardAuton::addNodes() {
    addFirstNode(m_moveForward);
    m_moveForward = new Node(5, new DriveWaypointAction(
            CORE2018::GetInstance()->gameDataParser.LoadPath(sidePath::DRIVE_FORWARD, false)));
}
