#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__
#ifndef BOOST_EXCEPTION_DISABLE
#define BOOST_EXCEPTION_DISABLE
#endif


#include "cocos2d.h"


class HelloBubble : public cocos2d::Scene
{
public:
	bool isMusicPlay = false;
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuHelpCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloBubble);
};

#endif 