#pragma once

#include <CORERobotLib.h>
#include "COREUtilities/COREConstant.h"


enum liftAction {
	BOTTOM,
	TOP,
	SCALE,
	SWITCH
};

class LiftAction: public COREAutonAction {
public:
	explicit LiftAction(liftAction action);
	void actionInit() override;
	actionStatus action() override;
	void actionEnd() override;

private:
	COREConstant<int> m_bottomHeight, m_topHeight, m_switchHeight, m_scaleHeight;
	liftAction m_requestedLiftAction;
};
