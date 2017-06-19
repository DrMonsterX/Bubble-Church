#ifndef __SETTING_H__
#define __SETTING_H__


#include "cocos2d.h"


class Setting : public cocos2d::Scene
{
public:

	bool isMusicPlay = false;

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuMusicCloseCallback(cocos2d::Ref* pSender);
	void menuMusicStartCallback(cocos2d::Ref* pSender);
	/*void menuSettingCallback(cocos2d::Ref* pSender);
	void menuHelpCallback(cocos2d::Ref* pSender);*/
	void menuBackCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Setting);
};

#endif