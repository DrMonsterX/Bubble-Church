#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H
#include"cocos2d.h"
using namespace cocos2d;
class GameOver :public Scene
{
public:

	GameOver();
	static cocos2d::Scene* createScene();

	virtual bool init();
	void closeButtonClicked(Ref *pSender);

	~GameOver();
	CREATE_FUNC(GameOver);

};
#endif // !GAMEOVER_H