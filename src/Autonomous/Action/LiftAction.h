#include <CORERobotLib.h>


enum liftAction {
	BOTTOM,
	TOP,
	SCALE,
	SWITCH
};

class LiftAction: public COREAutonAction {
public:
	explicit LiftAction(liftAction action);
    explicit LiftAction(int newPosition);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;

private:
	static COREConstant<int> m_bottomHeight, m_topHeight; //TODO: Add more constants
	liftAction m_requestedLiftAction;
};
