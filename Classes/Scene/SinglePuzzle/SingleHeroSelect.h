#ifndef __SINGLEHEROSELECT_H__
#define __SINGLEHEROSELECT_H__


#include "cocos2d.h"


class SingleHeroSelect : public cocos2d::Layer
{
public:
	//to save the information of hero's name 
	char* hero1 = "ssx";

	static cocos2d::Scene* createScene();

	virtual bool init();

	// selector callbacks
	void menuHeroCallback1(cocos2d::Ref* pSender);
	void menuHeroCallback2(cocos2d::Ref* pSender);
	void menuHeroCallback3(cocos2d::Ref* pSender);
	void menuHeroCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(SingleHeroSelect);
};

#endif
