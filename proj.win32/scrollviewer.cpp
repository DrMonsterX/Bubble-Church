#include "scrollviewer.h"

using namespace cocos2d;
void ScrollView::TouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	// ÒÆ¶¯  
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	CCPoint posPoint = CCPointMake(getPositionX() + touchPoint.x - m_TouchCurPoint.x, getPositionY());
	setPosition(posPoint);
	m_TouchCurPoint = touchPoint;
}
scrollviewer::scrollviewer()
{
}


scrollviewer::~scrollviewer()
{
}
