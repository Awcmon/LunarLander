#include "View.h"

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

View::View()
{
	punchPos = ofVec3f(0.0f, 0.0f, 0.0f);
}

/*
void View::setInput(Input * _input)
{
	input = _input;
}
*/

void View::posViewPunch(ofVec3f _punchPos)
{
	if (_punchPos.lengthSquared() > punchPos.lengthSquared())
	{
		punchPos = _punchPos;
	}
}

void View::update()
{
	//reset punch pos
	//punchPos.x = approach(punchPos.x, 0, (punchPos.x) * 0.1);
	//punchPos.y = approach(punchPos.y, 0, (punchPos.y) * 0.1);
	punchPos += (-punchPos) * 0.1;

	//cam.setPosition(punchPos.x, punchPos.y, 10.0f);
}

ofVec3f View::getTotalOffset()
{
	return punchPos;
}
