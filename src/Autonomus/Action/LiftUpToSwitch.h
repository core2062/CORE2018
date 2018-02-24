#ifndef SRC_AUTONOMUS_ACTION_LIFTUPTOSWITCH_H_
#define SRC_AUTONOMUS_ACTION_LIFTUPTOSWITCH_H_
#include <LiftSubsystem.h>
#include <CORERobotlib.h>

class LiftUpToSwitch : public COREAutonAction {
public:
	LiftUpToSwitch();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
};

#endif
