#ifndef SRC_AUTONOMOUS_ACTION_INTAKECUBEACTION_H_
#define SRC_AUTONOMOUS_ACTION_INTAKECUBEACTION_H_
#include <CORERobotlib.h>
#include <IntakeSubsystem.h>
#include <ScorerSubsystem.h>

class IntakeCubeAction : public COREAutonAction {
public:
	IntakeCubeAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	IntakeSubsystem intakeSubsystem;
	ScorerSubsystem scorerSubsystem;
};

#endif
