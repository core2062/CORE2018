#include "TestAuton.h"

#include "Actions.h"

TestAuton::TestAuton() : COREAuton("Test Auton") {

}

void TestAuton::addNodes() {
	std::vector<Waypoint> waypoints;
	waypoints.emplace_back(Waypoint(COREVector::FromXY(0, 0), 100));
    waypoints.emplace_back(Waypoint(COREVector::FromXY(3, 0), 100));
    waypoints.emplace_back(Waypoint(COREVector::FromXY(6, 0), 100));
    waypoints.emplace_back(Waypoint(COREVector::FromXY(9, 0), 100));
    waypoints.emplace_back(Waypoint(COREVector::FromXY(36, 0), 100));
	Path path1(waypoints);
	CORELog::logInfo("Remaining length (Initial): " + to_string(path1.getRemainingLength()));
	m_testNode = new Node(5, new DriveWaypointAction(path1));
    addFirstNode(m_testNode);
}
