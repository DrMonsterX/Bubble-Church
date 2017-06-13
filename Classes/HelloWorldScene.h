#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Boom.h"
#include "BoomWave.h"
#include<vector>
#include<stdlib.h>
#include<time.h>

enum tile_status
{
	none = 0, collid = 1, props = 2
};



class HelloWorld : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	int heroBubble = 1;
	std::vector<Vector<BoomWave*>> allWave;
	std::vector<Vector<BoomWave*>>::const_iterator pointer;
	
	bool heroAliveFlag = true;
	bool runflag = false;
	bool boomflag = false;

    virtual bool init();
    //set map and map layer
	TMXTiledMap* _tileMap;
	TMXLayer* barrier;
	TMXLayer* meta;

	//set hero
	Hero* hero;
	
	//set schedule
	virtual void update(float dt);

	//set keyboard function
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	//about hero
	void addHero(TMXTiledMap* map, Point startPoint);

	//about boom
	void removeBoom(Boom* boom);
	
	//about boom wave
	void addWave(Point boomPosition, int power);
	void removeWave(Vector<BoomWave*> waveArray);
	int isCanReach(Point tiledPos);
	
	//change the tile map to make this tile that boom had boomed can move
	void removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition);

	//about position
	Point getBoomPosition(cocos2d::Point position);
	Point getTiledPos(Point position);

	//about props
	void giveGifts(Point position);


    CREATE_FUNC(HelloWorld);
};

#endif 
