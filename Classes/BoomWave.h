#ifndef __BoomWave_H__
#define __BoomWave_H__


#include "cocos2d.h"
USING_NS_CC;
class BoomWave :public Layer
{
public:
	

	Point position;
	Sprite* sprite;

	static BoomWave* createWaveSprite(cocos2d::Point position,int direction);
	virtual bool init();
	void waveInit(cocos2d::Point position,int direction);

	Animate* createWaveAnimate(int num,int direction);

	CREATE_FUNC(BoomWave);

};

#endif
