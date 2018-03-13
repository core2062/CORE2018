#include "TestAuton.h"
#include "pathfinder.h"

#include "Actions.h"

TestAuton::TestAuton() : COREAuton("Test Auton") {
    int POINT_LENGTH = 3;

    Waypoint* points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);

    Waypoint p1 = { -4, -1, d2r(45) };      // Waypoint @ x=-4, y=-1, exit angle=45 degrees
    Waypoint p2 = { -1, 2, 0 };             // Waypoint @ x=-1, y= 2, exit angle= 0 radians
    Waypoint p3 = {  2, 4, 0 };             // Waypoint @ x= 2, y= 4, exit angle= 0 radians
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;

    TrajectoryCandidate candidate;
    pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.001, 15.0, 10.0, 60.0, &candidate);

    int length = candidate.length;
    Segment *trajectory = malloc(length * sizeof(Segment));

    pathfinder_generate(&candidate, trajectory);

    free(trajectory);
    return 0;
}

void TestAuton::addNodes() {
	std::vector<Waypoint> waypoints;
	waypoints.emplace_back(Waypoint(COREVector::FromXY(0, 0), 0.2));
	waypoints.emplace_back(Waypoint(COREVector::FromXY(0, 4), 0.2));
	waypoints.emplace_back(Waypoint(COREVector::FromXY(0, 12), 0.2));
	Path path1(waypoints);
	CORELog::logInfo("Remaining length: " + to_string(path1.getRemainingLength()));
	m_testNode = new Node(5, new DriveWaypointAction(path1));
    addFirstNode(m_testNode);
}
