#include <CORERobotlib.h>
#include <LiftSubsystem.h>
#include <Robot.h>

class LowerLiftAction: public COREAutonAction {
public:
	LowerLiftAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	CORE2018 Robot;
};

