#ifndef SRC_AUTONOMUS_ACTION_LIFTUPTOSWITCH_H_
#define SRC_AUTONOMUS_ACTION_LIFTUPTOSWITCH_H_
#include <CORERobotlib.h>

class LiftUpToSwitch {
public:
	LiftUpToSwitch();
	void actionInit();
	void action();
	void actionEnd();
};

#endif
