#ifndef __FATEMAPSELECT_H__
#define __FATEMAPSELECT_H__

#include "cocos2d.h"

class FateMapSelect : public cocos2d::Layer
{
public:
	char* map = "Map1.tmx";
	char* hero1;
	char* hero2;

	static cocos2d::Scene* createScene(char* aimhero1, char* aimhero2);

	virtual bool init();

	// a selector callback
	void menuMapCallback1(cocos2d::Ref* pSender);
	void menuMapCallback2(cocos2d::Ref* pSender);
	void menuMapCallback3(cocos2d::Ref* pSender);
	void menuMapCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	static FateMapSelect* create(char* hero1, char* hero2);
	CREATE_FUNC(FateMapSelect);
};



#endif
