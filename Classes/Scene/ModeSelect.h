#ifndef __MODESELECT_H__
#define __MODESELECT_H__


#include "cocos2d.h"


class ModeSelect : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	// a selector callback
	void menuSinglePuzzleCallback(cocos2d::Ref* pSender);
	void menuFateBeatCallback(cocos2d::Ref* pSender);
	void menuDoubleCallback(cocos2d::Ref* pSender);
	void menuOnLineCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ModeSelect);
};

#endif