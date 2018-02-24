#ifndef SRC_AUTONOMUS_ACTION_LIFTUPTOSCALE_H_
#define SRC_AUTONOMUS_ACTION_LIFTUPTOSCALE_H_
#include <LiftSubsystem.h>
#include <CORERobotlib.h>
#include <ctre/phoenix.h>
#include <Robot.h>

class LiftUpToScale: public COREAutonAction{
public:
	LiftUpToScale();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
};

#endif
