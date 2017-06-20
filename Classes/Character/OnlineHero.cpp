#include "OnlineHero.h"
#include<math.h>
#include<cstring>


#define MapNum 17
#define TiledSize 32
#define collidableTile 70
#define propsTile 84
#define waveTile 98


USING_NS_CC;


//init hero
OnlineHero* OnlineHero::createHeroSprite(Point position, int direction, const char* name)
{
	OnlineHero* hero = new OnlineHero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->name = name;
		hero->heroInit(position, direction, name);
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}



//init hero
bool OnlineHero::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}



//init hero
void OnlineHero::heroInit(Point position, int direction, const char* name)
{
	//set hero's status  
	this->isRun = false;
	this->position = position;
	
	//create hero sprite
	sprite = Sprite::create(String::createWithFormat("%sstand41.png", name)->getCString());
	sprite->setAnchorPoint(Vec2(0.5f, 0.2f));
	sprite->setPosition(position);
	sprite->setScale(0.45f);
	addChild(sprite);
	
	//create hero's stand animate
	auto* action = createAnimate(4, "stand", name, 4);
	action->setTag(100);
	sprite->runAction(action);
}



//create animate
Animate* OnlineHero::createAnimate(int direction, const char* action, const char* name, int num)
{
	//load hero's picture
	SpriteFrameCache* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("hero.plist", "hero.png");
	
	//add the pictrue into frame array 
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		SpriteFrame* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%s%d%d.png", name, action, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	
	//create hero's animate
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.15f);
	return Animate::create(animation);
}



//create animate action
void OnlineHero::setAction(int direction, const char* action, int num)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, name, num);
	animate->setTag(100);
	sprite->runAction(animate);
}



//create movement
void OnlineHero::moveTo(int direction, float speed)//use this to control hero's movement
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
void OnlineHero::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}



//change globle position into tile position
Point OnlineHero::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	int x = pos.x / tiledSize.width;
	int y = (MapNum*TiledSize - pos.y) / tiledSize.height;
	return Point(x, y);
}



//judge if hero can continue movement
bool OnlineHero::isCanRun(int direction)
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
			Point tilePos = tileCoordForPosition(Point(position.x, position.y + speed + 1));
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
bool OnlineHero::judgeMap(Point tiledPos)
{
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//the status that the tile is a collid
	if (tiledGid == collidableTile)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		Value prop_collidable = properties.asValueMap().at("Collidable");
		if (prop_collidable.asString().compare("true") == 0)
			return false;
		else
			return true;
	}
	//the status that the tile can be boomed
	else if (tiledGid == propsTile)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid);
		Value prop_props = properties.asValueMap().at("Props");
		if (prop_props.asString().compare("true") == 0)
			return false;
		else
			return true;
	}
	//the status that the tile is void
	else
		return true;
}
