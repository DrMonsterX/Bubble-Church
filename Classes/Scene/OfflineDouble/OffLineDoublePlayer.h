#ifndef __OFFLINEDOUBLEPLAYER_H__
#define __OFFLINEDOUBLEPLAYER_H__


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



//create a scene to play the offline double mode 
class OffLineDoublePlayer : public cocos2d::Layer
{
public:
    //overload the createScene() to accept information of hero and map
	static cocos2d::Scene* createScene(char* aimmap, char* aimhero1, char* aimhero2);

	char* map;

    //about hero's bubble
	int heroBubble1 = 1;
	int heroBubble2 = 1;
	std::vector<Vector<BoomWave*>> allWave1;
	std::vector<Vector<BoomWave*>>::const_iterator pointer1;
	std::vector<Vector<BoomWave*>> allWave2;
	std::vector<Vector<BoomWave*>>::const_iterator pointer2;

    //about hero1's status
	bool heroAliveFlag1 = true;
	bool runflag1 = false;
	bool boomflag1 = false;
	//about hero2's status
	bool heroAliveFlag2 = true;
	bool runflag2 = false;
	bool boomflag2 = false;

	//set map and map layer
	TMXTiledMap* _tileMap;
	TMXLayer* barrier;
	TMXLayer* meta;

	//set hero
	Hero* hero1;
	Hero* hero2;
	char* heroName1;
	char* heroName2;
	
	virtual bool init();

	//set schedule
	virtual void update(float dt);

	//set keyboard function
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	//about boom
	void removeBoom(Boom* boom);

	//about boom wave
	void addWave(Point boomPosition, int power, Hero* hero);
	void removeWave(Vector<BoomWave*> waveArray);
	int isCanReach(Point tiledPos);

	//change the tile map to make this tile that boom had boomed can move
	void removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition);

	//about position
	Point getBoomPosition(cocos2d::Point position);
	Point getTiledPos(Point position);

	//about props
	void giveGifts(Point position);

	//about gameover
	void gameOver();
	void menuAgainCallback(cocos2d::Ref* pSender);
	void menuRootCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);

	static OffLineDoublePlayer* create(char* map, char* aimhero1, char* aimhero2);

	CREATE_FUNC(OffLineDoublePlayer);
};

#endif
