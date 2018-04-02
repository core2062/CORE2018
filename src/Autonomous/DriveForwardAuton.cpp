
#include "DriveForwardAuton.h"
#include <Robot.h>
#include "Action/DriveDistanceAction.h"

DriveForwardAuton::DriveForwardAuton() :
	COREAuton("Drive Forward No Encoders") {
}

void DriveForwardAuton::addNodes() {
    addFirstNode(m_moveForward);
    m_moveForward = new Node(5, new DriveDistanceAction());
}
