#include "Hero.h"
#include<math.h>
#include<cstring>
#define MapNum 17
#define TiledSize 32
#define collidableTile 70
#define propsTile 84
#define waveTile 98
USING_NS_CC;


//init hero
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



//init hero
bool Hero::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}



//init hero
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



//create animate
Animate* Hero::createAnimate(int direction, const char* action, int num)
{
	SpriteFrameCache* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("hero.plist", "hero.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d%d.png", action, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.15f);
	return Animate::create(animation);
}



//create animate action
void Hero::setAction(int direction, const char* action, int num)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, num);
	animate->setTag(100);
	sprite->runAction(animate);
}



//create movement
void Hero::moveTo(int direction,float speed)//use this to control hero's movement
{
	if (direction == Right && isCanRun(direction))
	{
		position.x += speed;
	}
	else if (direction == Left && isCanRun(direction))
	{
		position.x -= speed;
	}
	else if (direction == Up && isCanRun(direction))
	{
		position.y += speed;
	}
	else if (direction == Down && isCanRun(direction))
	{
		position.y -= speed;
	}
	sprite->setPosition(position);
}




//set tile map
void Hero::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}



//change globle position into tile position
Point Hero::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	int x = pos.x / tiledSize.width;
	int y = (MapNum*TiledSize - pos.y) / tiledSize.height;
	return Point(x, y);
}



//judge if hero can continue movement
bool Hero::isCanRun(int direction)
{
	//judge the right side
	if (direction == Right)
	{
		int num = (int)((position.x + speed) / TiledSize);
		if ((int)(position.x / TiledSize) == num)
		{
			return true;
		}
		else
		{
			Point tilePos = tileCoordForPosition(Point(position.x + speed + 1, position.y));
			if ((position.x + speed) - num*TiledSize < 0.1)
			{
				position.x += 0.1f;
				return judgeMap(tilePos);
			}
			else
				return judgeMap(tilePos);
		}
	}
	//judge the left side
	else if (direction == Left)
	{
		int num = (int)((position.x - speed) / TiledSize);
		if ((int)(position.x / TiledSize) == num)
		{
			return true;
		}
		else
		{
			Point tilePos = tileCoordForPosition(Point(position.x - speed - 1, position.y));
			if ((position.x - speed) - num*TiledSize < 0.1)
			{
				position.x -= 0.1f;
				return judgeMap(tilePos);
			}
			else
				return judgeMap(tilePos);
		}
	}
	//judge the up side
	else if (direction == Up)
	{
		int num = (int)((position.y + speed) / TiledSize);
		if ((int)(position.y / TiledSize) == num)
		{
			return true;
		}
		else
		{
			Point tilePos = tileCoordForPosition(Point(position.x, position.y + speed+1));
			if ((position.y + speed) - num*TiledSize < 0.1)
			{
				position.y += 0.1f;
				return judgeMap(tilePos);
			}
			else
				return judgeMap(tilePos);
		}
	}
	//judge the down side
	else if (direction == Down)
	{
		int num = (int)((position.y - speed) / TiledSize);
		if ((int)(position.y / TiledSize) == num)
		{
			return true;
		}
		else
		{
			Point tilePos = tileCoordForPosition(Point(position.x, position.y - speed - 1));
			if ((position.y - speed) - num*TiledSize < 0.1)
			{
				position.y -= 0.1f;
				return judgeMap(tilePos);
			}
			else
				return judgeMap(tilePos);
		}
	}
}



//judge if hero can go into this tile
bool Hero::judgeMap(Point tiledPos)
{
	int tiledGid = meta->getTileGIDAt(tiledPos);
	if (tiledGid == collidableTile)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		Value prop_collidable = properties.asValueMap().at("Collidable");
		if (prop_collidable.asString().compare("true") == 0)
			return false;
		else
			return true;
	}
	else if (tiledGid == propsTile)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		Value prop_props = properties.asValueMap().at("Props");
		if (prop_props.asString().compare("true") == 0)
			return false;
		else
			return true;
	}
	else
		return true;
}