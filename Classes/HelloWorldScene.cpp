#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define TileSize 33
#define MapNum 15
#define collidableTile 49
#define propsTile 50
#define waveTile 51

USING_NS_CC;


//init scene
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}




bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add map data
	_tileMap = TMXTiledMap::create("map.tmx");
	_tileMap->setPosition(Vec2(200, 100));//wait for updata
	addChild(_tileMap, 0, 100);
	this->meta = _tileMap->getLayer("meta");
	this->barrier = _tileMap->getLayer("barrier");

	//set player start point
	TMXObjectGroup* objGroup = _tileMap->getObjectGroup("objects");
	ValueMap playPointMap = objGroup->getObject("playerPoint");
	Point playPoint;
	playPoint.x = playPointMap.at("x").asFloat();
	playPoint.y = playPointMap.at("y").asFloat();

	//add hero to map, init hero's position
	addHero(_tileMap, playPoint);
	_tileMap->addChild(hero,10);

	//add keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, hero);
	
	//add schedule update
	schedule(schedule_selector(HelloWorld::update), 0.01f);

    return true;
}




void HelloWorld::update(float dt)
{
	//calibration boom position
	Point boomPosition = getBoomPosition(hero->position);
	//get boom position of tile map
	Point boomTiledPosition = getTiledPos(boomPosition);
	
	//judge movemoent
	if (hero->isAlive == true)
	{
		if (runflag == true)
		{
			//begin to run
			if (hero->isRun == false)
			{
				hero->isRun = true;
				hero->nowDirection = hero->aimDirection;
				hero->setAction(hero->nowDirection, "run", 7);
			}
			//change run direction
			else if (hero->isRun == true)
			{
				if (hero->nowDirection != hero->aimDirection)
				{
					hero->nowDirection = hero->aimDirection;
					hero->setAction(hero->nowDirection, "run", 7);
				}
			}
			hero->moveTo(hero->nowDirection);
		}
		//stop running and stand
		else if (hero->isRun&&runflag == false)
		{
			hero->isRun = false;
			hero->setAction(hero->nowDirection, "stand", 4);
		}
	}

	//judge boomset
	if (boomflag == true && hero->judgeMap(boomTiledPosition) && hero->bubble > 0 && hero->isAlive == true)
	{
		boomflag = false;//reset boom keyboard
		//create boom
		auto boom = Boom::createBoomSprite(boomPosition);
		hero->bubble--;
		_tileMap->addChild(boom);

		//change the tile map to make this tile can't move
		meta->setTileGID(collidableTile, boomTiledPosition);

		//set boom wave in 1.95 secend
		auto delaySetWave = DelayTime::create(1.95f);
		this->runAction(Sequence::create(delaySetWave, CallFunc::create(CC_CALLBACK_0(HelloWorld::addWave, this, boom->position, hero->power)), NULL));

		//remove boom in 2.9 second
		auto delayBoom = DelayTime::create(2.9f);
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoom, this, boom)), NULL));
		//change the tile map to make this tile can move
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoomMeta, this, meta, 0, boomTiledPosition)), NULL));
	}

	//judge if hero is dead
	if (heroAliveFlag == true)
	{
		Point tiledPos = getTiledPos(hero->position);
		int tiledGid = meta->getTileGIDAt(tiledPos);
		if (tiledGid == waveTile)
		{
			heroAliveFlag = false;
			hero->isAlive = false;
			hero->setAction(1, "die", 9);
			//remove hero in 1.5 second
			auto delayHeroRemove = DelayTime::create(1.5f);
			hero->runAction(Sequence::create(delayHeroRemove, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, hero)), NULL));
			//wait for add director
		}
	}
}




//set the link to keyboard
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//start movement
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_W)
	{
		runflag = true;
		hero->aimDirection = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keycode == EventKeyboard::KeyCode::KEY_S)
	{
		runflag = true;
		hero->aimDirection = 4;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_A)
	{
		runflag = true;
		hero->aimDirection = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_D)
	{
		runflag = true;
		hero->aimDirection = 1;
	}
	//set boom
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J || keycode == EventKeyboard::KeyCode::KEY_KP_ENTER)
	{
		boomflag = true;
	}
}




void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_W
		|| keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keycode == EventKeyboard::KeyCode::KEY_S
		|| keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_A
		|| keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_D)
		runflag = false;
}




//add hero to the map
void HelloWorld::addHero(TMXTiledMap* map,Point startPoint)
{
	hero = Hero::createHeroSprite(startPoint, 4, "stand");
	hero->setTiledMap(map);
}




//calibration boom position
Point HelloWorld::getBoomPosition(cocos2d::Point position)
{
	Point boomPoint;
	boomPoint.x = ((int)(position.x / TileSize))*TileSize + TileSize / 2;
	boomPoint.y = ((int)(position.y / TileSize))*TileSize + TileSize / 2;
	return boomPoint;
}




//add boom wave
void HelloWorld::addWave(Point boomPosition, int Power)
{
	//set boom crash
	meta->setTileGID(waveTile, getTiledPos(boomPosition));

	//add boom wave
	Vector<BoomWave*> waveArray;
	//add boom wave to the right side
	for (int i = 1; i <= hero->power; i++)
	{
		Point aimPoint = Point(boomPosition.x + i*TileSize, boomPosition.y);
		//if the right side is void, create a wave
		if (isCanReach(getTiledPos(aimPoint))==none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Right);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		//if the right side is a wall,stop creating
		else if(isCanReach(getTiledPos(aimPoint)) == collid)
			break;
		//if the right side is a changeable tile,just remove it and stop creating to next tile
		else if (isCanReach(getTiledPos(aimPoint)) == props)
		{
			//remove tile
			barrier->removeTileAt(getTiledPos(aimPoint));
			meta->removeTileAt(getTiledPos(aimPoint));
			//create a wave
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Right);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}

	//add boom wave to the left side
	for (int i = 1; i <= hero->power; i++)
	{
		Point aimPoint = Point(boomPosition.x - i*TileSize, boomPosition.y);
		if (isCanReach(getTiledPos(aimPoint))==none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Left);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if(isCanReach(getTiledPos(aimPoint))==collid)
			break;
		else if (isCanReach(getTiledPos(aimPoint)) == props)
		{
			barrier->removeTileAt(getTiledPos(aimPoint));
			meta->removeTileAt(getTiledPos(aimPoint));
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Left);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}

	//add boom wave to the up side
	for (int i = 1; i <= hero->power; i++)
	{
		Point aimPoint = Point(boomPosition.x, boomPosition.y + i*TileSize);
		if (isCanReach(getTiledPos(aimPoint))==none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Up);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if(isCanReach(getTiledPos(aimPoint))==collid)
			break;
		else if (isCanReach(getTiledPos(aimPoint)) == props)
		{
			barrier->removeTileAt(getTiledPos(aimPoint));
			meta->removeTileAt(getTiledPos(aimPoint));
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Up);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}

	//add boom wave to the down side
	for (int i = 1; i <= hero->power; i++)
	{
		Point aimPoint = Point(boomPosition.x, boomPosition.y - i*TileSize);
		if (isCanReach(getTiledPos(aimPoint))==none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Down);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if(isCanReach(getTiledPos(aimPoint))==collid)
			break;
		else if (isCanReach(getTiledPos(aimPoint)) == props)
		{
			barrier->removeTileAt(getTiledPos(aimPoint));
			meta->removeTileAt(getTiledPos(aimPoint));
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Down);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}
	//add all waves into a vector
	allWave.push_back(waveArray);
	//use pointer to point to these waves
	if (allWave.size() == 1)
		pointer = allWave.begin();
	else
		pointer = allWave.end() - 1;
	std::vector<Vector<BoomWave*>>::const_iterator it = pointer;
	
	//remove these waves in 1.3 second
	auto delayRemoveWave = DelayTime::create(1.3f);
	this->runAction(Sequence::create(delayRemoveWave, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeWave, this, *it)), NULL));
	
	//reset hero's boom number
	hero->bubble++;
	
	//clear the vector
	if (hero->bubble == heroBubble)
		allWave.clear();
}




//remove boom waves
void HelloWorld::removeWave(Vector<BoomWave*> waveArray)
{
	for (Vector<BoomWave*>::const_iterator it = waveArray.begin(); it != waveArray.end(); it++)
	{
		meta->removeTileAt(getTiledPos((*it)->position));
		(*it)->removeFromParent();
	}

}




//judge what kind of things is on this tild
int HelloWorld::isCanReach(Point tiledPos)
{
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//judge hard wall
	if (tiledGid == collidableTile)
	{
		Value properties = _tileMap->getPropertiesForGID(tiledGid);
		Value prop = properties.asValueMap().at("Collidable");
		if (prop.asString().compare("true") == 0)
			return collid;
	}
	//judge changeable wall
	else if (tiledGid == propsTile)
	{
		Value properties = _tileMap->getPropertiesForGID(tiledGid);
		Value prop = properties.asValueMap().at("Props");
		if (prop.asString().compare("true") == 0)
		{
			return props;
		}
	}
	//judge void tild
	else
		return none;
}




//change the tile map to make this tile that boom had boomed can move
void HelloWorld::removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition)
{
	meta->setTileGID(gid, boomTiledPosition);
}




//change globle position into tiled position
Point HelloWorld::getTiledPos(Point position)
{
	Point tiledPos;
	tiledPos.x = (int)position.x / TileSize;
	tiledPos.y = (int)((MapNum*TileSize - position.y) / TileSize);
	return tiledPos;
}



//remove boom when it's boom is over
void HelloWorld::removeBoom(Boom* boom)
{
	boom->removeFromParent();
}



