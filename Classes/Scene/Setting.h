#ifndef __SETTING_H__
#define __SETTING_H__


#include "cocos2d.h"


class Setting : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	//selector callbacks
	void menuMusicCloseCallback(cocos2d::Ref* pSender);
	void menuMusicStartCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Setting);
};

#endif
