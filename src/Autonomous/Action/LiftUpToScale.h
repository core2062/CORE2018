#ifndef SRC_AUTONOMOUS_ACTION_LIFTUPTOSCALE_H_
#define SRC_AUTONOMOUS_ACTION_LIFTUPTOSCALE_H_
#include <LiftSubsystem.h>
#include <CORERobotlib.h>


class LiftUpToScale: public COREAutonAction{
public:
	LiftUpToScale();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	LiftSubsystem liftSubsystem;
};

#endif
