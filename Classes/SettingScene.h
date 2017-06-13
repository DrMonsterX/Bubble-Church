#pragma once
#ifndef _SETTING_SCENE_H
#define _SETTING_SCENE_H
#include<cocos2d.h>
#include "SimpleAudioEngine.h"
#include "BaseLayer.h"
class Setting :public BaseLayer
{
public:
	Setting();
	virtual bool init();
	static Scene *createScene();
	void onChangedCheckBox1(Ref *pSender, CheckBox::EventType type);
	void onChangedCheckBox2(Ref *pSender, CheckBox::EventType type);
	//void menuSoundCallback(cocos2d::Ref *pSender);
	//void menuMusicCallback(cocos2d::Ref *pSender);
	void onChangedSlider1(Ref *pSender, Slider::EventType type);
	void onChangedSlider2(Ref *pSender, Slider::EventType type);
	
	~Setting();
	CREATE_FUNC(Setting);
};
#endif
