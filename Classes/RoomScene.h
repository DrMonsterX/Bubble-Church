#pragma once
#ifndef _ROOM_SCENE_H
#define _ROOM_SCENE_H
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"BaseLayer.h"


USING_NS_CC;

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;
class RoomScene :public Layer
{
public:
	RoomScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void ReturnHomeCallback(Ref *pSender);
	void StartSceneCallback(Ref *pSender);
	void onChangedCheckBox(Ref *pSender, CheckBox::EventType type);
	bool ready = false;
	bool myready = false;
	int playerNum;
	CREATE_FUNC(RoomScene);

	~RoomScene();
};
#endif


