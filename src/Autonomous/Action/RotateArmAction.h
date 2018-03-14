#include <CORERobotLib.h>
#include <ScorerSubsystem.h>

enum positionArmAction {

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

	positionArmAction m_requestedArmAction;
};
