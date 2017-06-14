#pragma once
#ifndef _HELP_SCENE_H
#define _HELP_SCENE_H
#include<cocos2d.h>
#include "BaseLayer.h"
class Help :public BaseLayer
{
public:
	Help();
	virtual bool init();
	static Scene *createScene();
	void scrollCallback(Ref *pSender, ScrollView::EventType type);
	Sprite *scrollpng;
	ScrollView *scroll;
	~Help();
	CREATE_FUNC(Help);
};
#endif