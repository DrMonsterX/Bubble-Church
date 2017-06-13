#pragma once
#ifndef _POPULAYER_H
#define _POPULAYER_H


#include"cocos2d.h"

using namespace cocos2d;
class PopuLayer :virtual public Layer//,virtual public LayerColor
{
public:
	PopuLayer();
	virtual bool init();
	virtual void ButtonCallback1(Ref *pSender);
	virtual void ButtonCallback2(Ref *pSender);


	CREATE_FUNC(PopuLayer);
	~PopuLayer();
};
#endif // !_POPULAYER_H