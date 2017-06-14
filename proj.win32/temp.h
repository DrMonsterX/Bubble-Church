#pragma once
#ifndef BASELAYER_H
#define BASELAYER_H

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;
class BaseLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene *createScene();
	//return
	virtual void menuCheckCallback1(Ref *pSender);
	//setting
	virtual void menuCheckCallback2(Ref *pSender);
	//help
	virtual void menuCheckCallback3(Ref *pSender);
	virtual void menuCheckCallback4(Ref *pSender);
	//loading and save
	virtual void addButton();
	virtual void onButtonClicked(Ref *pSender);

	//virtual void onEnterTransitionDidFinish();
	virtual void AddBackground(Size visibleSize);
	virtual void CreateMenu();
	virtual void onChangedSlider(Ref *pSender, Slider::EventType type);
	virtual void onChangedRadioButtonGroup(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type);
	virtual void onChangedCheckBox(Ref *pSender, CheckBox::EventType type);
	virtual void scrollCallback(Ref *pSender, ScrollView::EventType type);
	virtual void textFieldEvent(Ref *pSender, TextField::EventType type);
	//virtual void textFieldKeyboardEvent(Ref *pSender, EventKeyboard::KeyCode key);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event * even);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event * even);
	BaseLayer();
	void update(float dt);
	int count = 0;
	Sprite *scrollpng;
	EventListenerKeyboard *keylisten;
	EventDispatcher *eventDispatcher;
	MoveBy* moveby;
	cocos2d::ui::ScrollView *scroll;
	NodeGrid *nodegrid;
	TextField *textField;
	Text *displaylabel;
	LoadingBar *ldbar;
	//LoadingScene *tran;
	~BaseLayer();
	CREATE_FUNC(BaseLayer);
};

#endif


