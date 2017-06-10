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
	sprite->setAnchorPoint(Vec2(0.5, 0.2));
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
	if (direction == 1 && isCanRun(direction))
	{
		position.x += r;
	}
	else if (direction == 2 && isCanRun(direction))
	{
		position.x -= r;
	}
	else if (direction == 3 && isCanRun(direction))
	{
		position.y += r;
	}
	else if (direction == 4 && isCanRun(direction))
	{
		position.y -= r;
	}
	sprite->setPosition(position);
}


void Hero::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}


Point Hero::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	int x = pos.x / tiledSize.width;
	int y = (495 - pos.y) / tiledSize.height;
	return Point(x, y);
}

bool Hero::isCanRun(int direction)
{
	if (direction == 1)
	{
		if ((int)position.x % 33 != 0)
		{
			return true;
		}
		else if ((int)position.y%33 != 0)
		{
			Point tilePos = tileCoordForPosition(Point(position.x + 1, position.y));
			return judgeMap(tilePos);
		}
		else
		{
			Point tilePos1 = tileCoordForPosition(Point(position.x + 1, position.y+1));
			Point tilePos2 = tileCoordForPosition(Point(position.x + 1, position.y-1));
			return (judgeMap(tilePos1) | judgeMap(tilePos2));
		}
	}
	else if (direction == 2)
	{
		if ((int)position.x % 33 != 0)
		{
			return true;
		}
		else if ((int)position.y % 33 != 0)
		{
			Point tilePos = tileCoordForPosition(Point(position.x - 1, position.y));
			return judgeMap(tilePos);
		}
		else
		{
			Point tilePos1 = tileCoordForPosition(Point(position.x - 1, position.y + 1));
			Point tilePos2 = tileCoordForPosition(Point(position.x - 1, position.y - 1));
			return (judgeMap(tilePos1) | judgeMap(tilePos2));
		}
	}
	else if (direction == 3)
	{
		if ((int)position.y % 33 != 0)
		{
			return true;
		}
		else if((int)position.x % 33 != 0)
		{
			Point tilePos = tileCoordForPosition(Point(position.x, position.y + 1));
			return judgeMap(tilePos);
		}
		else
		{
			Point tilePos1 = tileCoordForPosition(Point(position.x + 1, position.y + 1));
			Point tilePos2 = tileCoordForPosition(Point(position.x - 1, position.y + 1));
			return (judgeMap(tilePos1) | judgeMap(tilePos2));
		}
	}
	else if (direction == 4)
	{
		if ((int)position.y % 33 != 0)
		{
			return true;
		}
		else if((int)position.x % 33 != 0)
		{
			Point tilePos = tileCoordForPosition(Point(position.x, position.y - 1));
			return judgeMap(tilePos);
		}
		else
		{
			Point tilePos1 = tileCoordForPosition(Point(position.x + 1, position.y - 1));
			Point tilePos2 = tileCoordForPosition(Point(position.x - 1, position.y - 1));
			return (judgeMap(tilePos1) | judgeMap(tilePos2));
		}
	}
}

bool Hero::judgeMap(Point tiledPos)
{
	int tiledGid = meta->getTileGIDAt(tiledPos);
	if (tiledGid != 0)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		Value prop = properties.asValueMap().at("Collidable");
		if (prop.asString().compare("true") == 0)
			return false;
		else
			return true;
	}
	else
		return true;
}