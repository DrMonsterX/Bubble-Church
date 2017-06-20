#ifndef __ONLINEHERO_H__
#define __ONLINEHERO_H__

#include "cocos2d.h"


USING_NS_CC;


enum hero_direction
{
	Right = 1, Left = 2, Up = 3, Down = 4
};



//create the hero class 
class OnlineHero :public Layer
{
public:
    //about hero's status
	bool isAlive = true;

    //save hero's name to create the right animate 
	const char* name;

	//about movement
	bool isRun;
	float speed = 5.0;
	int nowDirection;
	int aimDirection;

	//about bubble
	int power = 1;
	int bubble = 1;

	cocos2d::Point position;
	Sprite* sprite;
	TMXTiledMap* m_map;
	TMXLayer* meta;

	//init hero
	bool init();
	static OnlineHero* createHeroSprite(cocos2d::Point position, int direction, const char* name);
	void heroInit(cocos2d::Point position, int direction, const char* name);

	//create animate
	Animate* createAnimate(int direction, const char *action, const char* name, int num);

	//create ancition
	void setAction(int direction, const char* action, int num);

	//create movement
	void moveTo(int position, float speed);

	void setTiledMap(TMXTiledMap* map);

	//change globle position into tile position
	Point tileCoordForPosition(Point pos);

	//judge if hero can continue movement
	bool isCanRun(int direction);
	bool judgeMap(Point tiledPos);

	CREATE_FUNC(OnlineHero);
};

#endif 
