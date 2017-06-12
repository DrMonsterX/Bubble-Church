#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Boom.h"
#include "BoomWave.h"



class HelloWorld : public cocos2d::Scene
{
public:
	int direction = 0;
	static cocos2d::Scene* createScene();
	int bubble = 3;
	std::vector<Vector<BoomWave*>> allWave;
	std::vector<Vector<BoomWave*>>::const_iterator pointer;
	
	bool runflag = false;
	bool boomflag = false;

	
    virtual bool init();
    
	//Sprite* bg;
	TMXTiledMap* _tileMap;
	TMXLayer* meta;

	Hero* hero;
	
	Point boomPosition;
	

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);
	
	
    
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void addHero(TMXTiledMap* map, Point startPoint);
	Point getBoomPosition(cocos2d::Point position);
	void addWave(Point boomPosition, int power);
	void removeWave(Vector<BoomWave*> waveArray);
	bool isCanReach(Point position);
	void removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition);


    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
