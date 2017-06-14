#pragma once
#ifndef  _CONTROLLAYER_
#define _CONTROLLAYER_
#include"cocos2d.h"


using namespace cocos2d;
using namespace std;
class ControlLayer :public cocos2d::Layer
{
public:
	ControlLayer();
	static cocos2d::Scene* createScene();
	virtual bool init();//remaining
	//void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event * even);
	//void ControlLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event * even);
	//void MouseDown(Event  *evect);
	//void MouseUp(Event  *evect);
	//void MouseMove(Event  *evect);
	void gameover();
	void timeupdate(float);
	void timeupdatebegin(float);
	void untimeupdate(float);
	void untimeupdatebegin(float);
	bool iswin;//remianing
	void showresult();
	//void update();
	void onEnter();
	bool isbegin = false;
	bool isover = false;
	vector<int> socre = { 0,0,0,0 };

	float min = 0;
	float sec = 0;
	float begin = 0;
	//static MainScene *pMainScene;


	CREATE_FUNC(ControlLayer);
	~ControlLayer();
};
#endif // ! _CONTROLLAYER_
