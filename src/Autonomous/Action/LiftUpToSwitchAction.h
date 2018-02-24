#include <LiftSubsystem.h>
#include <CORERobotlib.h>
#include <Robot.h>

class LiftUpToSwitch : public COREAutonAction {
public:
	LiftUpToSwitch();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	CORE2018 Robot;
	double m_switchHeight;
};

