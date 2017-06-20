#include "BoomWave.h"


#define TiledSize 33


//init boom wave
BoomWave* BoomWave::createWaveSprite(cocos2d::Point position, int direction)
{
	BoomWave* wave = new BoomWave();
	if (wave&&wave->init())
	{
		wave->autorelease();
		wave->waveInit(position, direction);

		return wave;
	}
	CC_SAFE_DELETE(wave);
	return NULL;
}



//init boom wave
bool BoomWave::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}



//init boom wave
void BoomWave::waveInit(cocos2d::Point position, int direction)
{
	//set boomwave's position 
	this->position = position;
	
	//according to the direction to choose the animate and create sprite
	if(direction==1)
	    sprite = Sprite::create("boomwave11.png");
	else if(direction == 2)
		sprite = Sprite::create("boomwave21.png");
	else if(direction==3)
		sprite = Sprite::create("boomwave31.png");
	else if(direction==4)
		sprite = Sprite::create("boomwave41.png");

	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(position);
	sprite->setScale(0.15f);
	
	addChild(sprite);
	
	//set wave animate
	auto* action = createWaveAnimate(9,direction);
	sprite->runAction(action);
}



//create boom animate
Animate* BoomWave::createWaveAnimate(int num,int direction)
{
	//load boomwave picture
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("boom.plist", "boom.png");
	
	//add pictrue into frame array
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("boomwave%d%d.png", direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	
	//create animate
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	
	return Animate::create(animation);
}
