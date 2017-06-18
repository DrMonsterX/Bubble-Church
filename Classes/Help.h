#ifndef __HELPH__
#define __HELP_H__

#include "cocos2d.h"

class Help : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuSelectCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Help);
};

#endif 
