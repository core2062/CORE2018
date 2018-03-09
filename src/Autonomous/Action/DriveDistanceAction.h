#include <CORERobotLib.h>
#include <DriveSubsystem.h>
#include <Robot.h>

class DriveDistanceAction : public COREAutonAction {
public:
	DriveDistanceAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	CORE2018 Robot;
};