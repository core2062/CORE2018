#include "TestPathAuton.h"
#include "Robot.h"

TestPathAuton::TestPathAuton() : COREAuton("Test Path Auton") {

}

void TestPathAuton::addNodes() {
    Path path1;
    if(COREPathConnectionHandler::path.getRemainingLength() != 0) {
        path1 = COREPathConnectionHandler::path;
    } else {
        CORELog::logError("Valid path not recived from dashboard!");
        std::vector<Waypoint> waypoints;
        waypoints.emplace_back(Waypoint(Translation2d(0, 0), 100));
        path1 = Path(waypoints);
    }

	CORELog::logInfo("Remaining length (Initial): " + to_string(path1.getRemainingLength()));
    CORE2018::GetInstance()->driveSubsystem.setLocation(path1.getFirstWaypoint().position.getX(),
                                                        path1.getFirstWaypoint().position.getY());
	m_testNode = new Node(15, new DriveWaypointAction(path1, Translation2d(path1.getFirstWaypoint().position.getX(), path1.getFirstWaypoint().position.getY())));
    addFirstNode(m_testNode);
}
