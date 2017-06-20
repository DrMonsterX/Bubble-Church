#ifndef __FATEHEROSELECT1_H__
#define __FATEHEROSELECT1_H__


#include "cocos2d.h"


class FateHeroSelect1 : public cocos2d::Layer
{
public:
	//to save the information of hero
	char* hero1 = "ssx";

	static cocos2d::Scene* createScene();

	virtual bool init();

	//selector callbacks
	void menuHeroCallback1(cocos2d::Ref* pSender);
	void menuHeroCallback2(cocos2d::Ref* pSender);
	void menuHeroCallback3(cocos2d::Ref* pSender);
	void menuHeroCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(FateHeroSelect1);
};

#endif
