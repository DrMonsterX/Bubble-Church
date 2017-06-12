#include "Boom.h"


//init boom
Boom* Boom::createBoomSprite(cocos2d::Point position)
{
	Boom* boom = new Boom();
	if (boom&&boom->init())
	{
		boom->autorelease();
		boom->boomInit(position);

		return boom;
	}
	CC_SAFE_DELETE(boom);
	return NULL;
}



//init boom
bool Boom::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}



//init boom
void Boom::boomInit(cocos2d::Point position)
{

	this->position = position;
	sprite = Sprite::create("boom1.png");
	
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(position);
	sprite->setScale(0.15f);
	
	addChild(sprite);
	//set boom animate
	auto* action = createBoomAnimate(19);
	sprite->runAction(action);
}



//create boom animate
Animate* Boom::createBoomAnimate(int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("boom.plist", "boom.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("boom%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.15f);
	return Animate::create(animation);
}