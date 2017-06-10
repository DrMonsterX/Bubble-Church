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

	bool isRun;
	int direction;
	cocos2d::Point position;
	Sprite* sprite;
	TMXTiledMap* m_map;
	TMXLayer* meta;
	
	bool init();
	static Hero* createHeroSprite(cocos2d::Point position, int direction, const char* name);
	void heroInit(cocos2d::Point position, int direction, const char* name);
	Animate* createAnimate(int direction, const char *action, int num);
	void setAction(int direction, const char* action, int num);
	void moveTo(int position);
	void setTiledMap(TMXTiledMap* map);
	Point tileCoordForPosition(Point pos);
	bool isCanRun(int direction);
	bool judgeMap(Point tiledPos);
	CREATE_FUNC(Hero);	
};

#endif // !__Hero_H__