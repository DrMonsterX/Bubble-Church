#ifndef __DOUBLEMAPSELECT_H__
#define __DOUBLEMAPSELECT_H__


#include "cocos2d.h"


class DoubleMapSelect : public cocos2d::Layer
{
public:
	//to save the information of hero select and map select
	char* map = "Map1.tmx";
	char* hero1;
	char* hero2;

	static cocos2d::Scene* createScene(char* aimhero1,char* aimhero2);

	virtual bool init();

	// selector callbacks
	void menuMapCallback1(cocos2d::Ref* pSender);
	void menuMapCallback2(cocos2d::Ref* pSender);
	void menuMapCallback3(cocos2d::Ref* pSender);
	void menuMapCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

    // overload the create() to accept the information of hero1 and hero2
	static DoubleMapSelect* create(char* hero1, char* hero2);
	
	CREATE_FUNC(DoubleMapSelect);
};

#endif
