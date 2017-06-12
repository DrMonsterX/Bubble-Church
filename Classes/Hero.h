#ifndef __Hero_H__
#define __Hero_H__


#include "cocos2d.h"
USING_NS_CC;
enum hero_direction
{
	Right = 1, Left = 2, Up = 3, Down = 4
};
class Hero:public Layer
{
public:
	
	//about movement
	bool isRun;
	int nowDirection;
	int aimDirection;

	//about bubble
	int power = 3;
	int bubble = 3;

	cocos2d::Point position;
	Sprite* sprite;
	TMXTiledMap* m_map;
	TMXLayer* meta;

	
	//init hero
	bool init();
	static Hero* createHeroSprite(cocos2d::Point position, int direction, const char* name);
	void heroInit(cocos2d::Point position, int direction, const char* name);

	//create animate
	Animate* createAnimate(int direction, const char *action, int num);

	//create ancition
	void setAction(int direction, const char* action, int num);

	//create movement
	void moveTo(int position);

	void setTiledMap(TMXTiledMap* map);
	
	//change globle position into tile position
	Point tileCoordForPosition(Point pos);

	//judge if hero can continue movement
	bool isCanRun(int direction);
	bool judgeMap(Point tiledPos);


	CREATE_FUNC(Hero);	
};

#endif 