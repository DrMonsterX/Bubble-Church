#ifndef __Boom_H__
#define __Boom_H__


#include "cocos2d.h"
USING_NS_CC;
class Boom:public Layer
{
public:

	cocos2d::Point position;
	Sprite* sprite;

	static Boom* createBoomSprite(cocos2d::Point position);
	virtual bool init();
	void boomInit(cocos2d::Point position);
	
	Animate* createBoomAnimate(int num);

	CREATE_FUNC(Boom);

};

#endif

