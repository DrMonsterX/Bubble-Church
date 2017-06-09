#ifndef __Hero_H__
#define __Hero_H__


#include "cocos2d.h"
USING_NS_CC;
enum hero_direction
{
	R=1,L=2,U=3,D=4
};
class Hero:public Layer
{
public:

	bool isRun;
	int direction;
	cocos2d::Point position;
	Sprite* sprite;
	
	static Hero* createHeroSprite(cocos2d::Point position, int direction, const char* name);
	virtual bool init();
	void heroInit(cocos2d::Point position, int direction, const char* name);
	Animate* createAnimate(int direction, const char *action, int num);
	void setAction(int direction, const char* action, int num);
	void moveTo(int position);
	CREATE_FUNC(Hero);
};

#endif // !__Hero_H__