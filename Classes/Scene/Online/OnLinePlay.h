#ifndef __ONLINEPLAY_H__
#define __ONLINEPLAY_H__


#include "cocos2d.h"
#include "OnlineHero.h"
#include "Boom.h"
#include "BoomWave.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>  
#include <iostream>  
#include <client.hpp> 
#include <orderMessage.hpp>


using namespace std;


enum tile_status
{
	none = 0, collid = 1, props = 2
};



class OnLinePlay : public cocos2d::Layer
{
public:
	
	friend class client;
	static cocos2d::Scene* createScene(client* c, char* t);
		

	int playerNum = 0; //save the number of players;
	bool isStart = false;
	orderMessage msg_;
	
	char id[8]="";
	char* map = "map2.tmx";
	
	void progressOrder(orderMessage msg);
    int getPlayer(orderMessage msg);


	int heroBubble1 = 1;
	int heroBubble2 = 1;

	std::vector<Vector<BoomWave*>> allWave1;
	std::vector<Vector<BoomWave*>>::const_iterator pointer1;
	std::vector<Vector<BoomWave*>> allWave2;
	std::vector<Vector<BoomWave*>>::const_iterator pointer2;


	bool heroAliveFlag1 = true;
	bool runflag1 = false;
	bool boomflag1 = false;

	bool heroAliveFlag2 = true;
	bool runflag2 = false;
	bool boomflag2 = false;

	virtual bool init();
	//set map and map layer
	TMXTiledMap* _tileMap;
	TMXLayer* barrier;
	TMXLayer* meta;

	//set hero
	OnlineHero* hero1;
	OnlineHero* hero2;
	char* heroName1 = "0";
	char* heroName2 = "0";

	//set schedule
	virtual void update(float dt);

	//set keyboard function
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	//about boom
	void removeBoom(Boom* boom);

	//about boom wave
	void addWave(Point boomPosition, int power, OnlineHero* hero);
	void removeWave(Vector<BoomWave*> waveArray);
	int isCanReach(Point tiledPos);

	//change the tile map to make this tile that boom had boomed can move
	void removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition);

	//about position
	Point getBoomPosition(cocos2d::Point position);
	Point getTiledPos(Point position);

	//about props
	void giveGifts(Point position);

	//to start game in a same time
	virtual void allReady(float dt);
	void allReadyInit();

	//about gameover
	void gameOver();
	void menuRootCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);


	static OnLinePlay* create(client *c, char *t);
};

#end