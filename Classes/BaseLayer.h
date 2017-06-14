#pragma once
#ifndef BASELAYER_H
#define BASELAYER_H

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "PopuLayer.h"


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
	//room
	virtual void menuCheckCallback4(Ref *pSender);
	PopuLayer *popul;
	BaseLayer();
	~BaseLayer();
	CREATE_FUNC(BaseLayer);
};

#endif

