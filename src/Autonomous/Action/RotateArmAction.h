#include <CORERobotLib.h>
#include <ScorerSubsystem.h>

enum armAction {

	UP,
	MIDDLE,
	DOWN

};

class RotateArmAction : public COREAutonAction {
public:
	RotateArmAction();
	void actionInit();
	actionStatus action() override;
	void actionEnd();
	ScorerSubsystem scorerSubsystem;



private:

	armAction m_requestedArmAction;
};
