#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Boom.h"


class HelloWorld : public cocos2d::Scene
{
public:
	int direction = 0;
	static cocos2d::Scene* createScene();

    virtual bool init();
    
	//Sprite* bg;
	cocos2d::TMXTiledMap* _tileMap;
	Hero* hero;
	int keyflag = 0;

	void distoryBoom(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);
    
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void addHero(TMXTiledMap* map, Point startPoint);
	Point getBoomPosition(cocos2d::Point position);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
