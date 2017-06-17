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
extern vector<string> strvec;
class message :public Dictionary
{
	message() :Dictionary() {};
	int *parr;
	int arrsize = 0;
	int kill[2] = { 0 };
	int dying[2] = { 0 };
	string *pstr;
	int strsize = 0;
};
class RoomScene :public Layer
{
public:
	RoomScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void ReturnHomeCallback(Ref *pSender);
	void EnterSceneCallback(Ref *pSender);
	void ChatterCallback(Ref *pSender);
	void onChangedCheckBox(Ref *pSender, CheckBox::EventType type);
	void SelectCallback2(Ref *pSender);
	void SelectCallback1(Ref *pSender);
	void DetermCallback1(Ref *pSender);
	void DetermCallback2(Ref *pSender);
	//void roleSelectedCallback2(Ref *pSender);
	void onChangedRadioButtonGroup1(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type);
	void onChangedRadioButtonGroup2(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type);
	void onChangedRadioButtonGroupmap(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type);
	bool ready = false;
	bool myready = false;
	RadioButtonGroup *radiobuttongroupmap;
	RadioButton *radiobutton1;
	RadioButton *radiobutton2;
	RadioButton *radiobutton3;
	RadioButton *radiobutton4;
	RadioButtonGroup *radiobuttongroup;
	RadioButton *tradiobutton1;
	RadioButton *tradiobutton2;
	RadioButton *tradiobutton3;
	Button *enter;
	Button *player1select;
	Button *player2select;
	Button *player1determ;
	Button *player2determ;
	//Vector<pair<int, string>> *vec;
	int playerNum;
	CREATE_FUNC(RoomScene);

	~RoomScene();
};
#endif


