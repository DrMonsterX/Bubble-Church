#include "Hero.h"
#include<math.h>
#include<cstring>
USING_NS_CC;

Hero* Hero::createHeroSprite(Point position, int direction, const char* name)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit(position, direction, name);
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}

bool Hero::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void Hero::heroInit(Point position, int direction, const char* name)
{
	this->isRun = false;
	this->position = position;
	sprite = Sprite::create(String::createWithFormat("%s41.png",name)->getCString());
	sprite->setAnchorPoint(Vec2(0.5, 0.4));
	sprite->setPosition(position);
	sprite->setScale(0.45f);
	addChild(sprite);
	auto* action = createAnimate(4, "stand", 4);
	action->setTag(100);
	sprite->runAction(action);
}

Animate* Hero::createAnimate(int direction, const char* action, int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("hero.plist", "hero.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d%d.png", action, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.15f);
	return Animate::create(animation);
}

void Hero::setAction(int direction, const char* action, int num)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, num);
	animate->setTag(100);
	sprite->runAction(animate);
}

void Hero::moveTo(int direction)//use this to control hero's movement
{
	float r = 1;
	if (direction == 1 && position.x + 5 < 480)
	{
		position.x += r;
	}
	else if (direction == 2 && position.x - 5 > 0)
	{
		position.x -= r;
	}
	else if (direction == 3 && position.y + 5 < 480)
	{
		position.y += r;
	}
	else if (direction == 4 && position.y - 5 > 0)
	{
		position.y -= r;
	}
	sprite->setPosition(position);
}