#ifndef __DOUBLEHEROSELECT2_H__
#define __DOUBLEHEROSELECT2_H__


#include "cocos2d.h"


class DoubleHeroSelect2 : public cocos2d::Layer
{
public:
	char* hero1 = "ssx";
	char* hero2 = "zy";

	static cocos2d::Scene* createScene(char* hero1);

	virtual bool init();

	// a selector callback
	void menuHeroCallback1(cocos2d::Ref* pSender);
	void menuHeroCallback2(cocos2d::Ref* pSender);
	void menuHeroCallback3(cocos2d::Ref* pSender);
	void menuHeroCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	static DoubleHeroSelect2* create(char* hero1);

	CREATE_FUNC(DoubleHeroSelect2);
};

#endif