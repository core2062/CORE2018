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
        path1 = PathLoader::loadPath("test.json", false);
//        std::vector<Waypoint> waypoints;
//        waypoints.emplace_back(Waypoint(Translation2d(0, 0), 100));
//        path1 = Path(waypoints);
    }

	CORELog::logInfo("Remaining length (Initial): " + to_string(path1.getRemainingLength()));
    CORE2018::GetInstance()->driveSubsystem.resetTracker({path1.getFirstWaypoint().position,
                                                          path1.getFirstWaypoint().rotation});
	m_testNode = new Node(15, new DriveWaypointAction(path1));
    addFirstNode(m_testNode);
}
