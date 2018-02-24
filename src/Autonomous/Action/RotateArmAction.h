#include <CORERobotLib.h>
#include <ScorerSubsystem.h>

class RotateArmAction : public COREAutonAction {
public:
	RotateArmAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;
};
