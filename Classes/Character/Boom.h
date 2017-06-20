#ifndef __Boom_H__
#define __Boom_H__


#include "cocos2d.h"


USING_NS_CC;


class Boom:public Layer
{
public:
    // boom's position 
	cocos2d::Point position;
	
	//boom sprite
	Sprite* sprite;

	static Boom* createBoomSprite(cocos2d::Point position);
	virtual bool init();
	void boomInit(cocos2d::Point position);
	
	//create boom animate
	Animate* createBoomAnimate(int num);

	CREATE_FUNC(Boom);

};

#endif
