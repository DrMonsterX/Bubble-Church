#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define TileSize 32
#define MapNum 17
#define collidableTile 70
#define propsTile 84
#define waveTile 98
#define bubbleTile 14
#define shoesTile 28
#define syrupTile 42

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
	ValueMap playPointMap1 = objGroup->getObject("playerPoint1");
	Point playPoint1;
	playPoint1.x = playPointMap1.at("x").asFloat();
	playPoint1.y = playPointMap1.at("y").asFloat();
	ValueMap playPointMap2 = objGroup->getObject("playerPoint2");
	Point playPoint2;
	playPoint2.x = playPointMap2.at("x").asFloat();
	playPoint2.y = playPointMap2.at("y").asFloat();

	//add hero to map, init hero's position
	hero1 = Hero::createHeroSprite(playPoint1, 4, "zy");
	hero1->setTiledMap(_tileMap);
	_tileMap->addChild(hero1,10);
	hero2 = Hero::createHeroSprite(playPoint2, 4, "ssx");
	hero2->setTiledMap(_tileMap);
	_tileMap->addChild(hero2, 10);

	//add keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _tileMap);
	
	//add schedule update
	schedule(schedule_selector(HelloWorld::update), 0.01f);

    return true;
}




void HelloWorld::update(float dt)
{
	//calibration boom position
	Point boomPosition1 = getBoomPosition(hero1->position);
	//get boom position of tile map
	Point boomTiledPosition1 = getTiledPos(boomPosition1);

	//calibration boom position
	Point boomPosition2 = getBoomPosition(hero2->position);
	//get boom position of tile map
	Point boomTiledPosition2 = getTiledPos(boomPosition2);
	
	//judge movemoent
	if (hero1->isAlive == true)
	{
		if (runflag1 == true)
		{
			//begin to run
			if (hero1->isRun == false)
			{
				hero1->isRun = true;
				hero1->nowDirection = hero1->aimDirection;
				hero1->setAction(hero1->nowDirection, "run", 7);
			}
			//change run direction
			else if (hero1->isRun == true)
			{
				if (hero1->nowDirection != hero1->aimDirection)
				{
					hero1->nowDirection = hero1->aimDirection;
					hero1->setAction(hero1->nowDirection, "run", 7);
				}
			}
			hero1->moveTo(hero1->nowDirection,hero1->speed);
		}
		//stop running and stand
		else if (hero1->isRun&&runflag1 == false)
		{
			hero1->isRun = false;
			hero1->setAction(hero1->nowDirection, "stand", 4);
		}
	}

	if (hero2->isAlive == true)
	{
		if (runflag2 == true)
		{
			//begin to run
			if (hero2->isRun == false)
			{
				hero2->isRun = true;
				hero2->nowDirection = hero2->aimDirection;
				hero2->setAction(hero2->nowDirection, "run", 7);
			}
			//change run direction
			else if (hero2->isRun == true)
			{
				if (hero2->nowDirection != hero2->aimDirection)
				{
					hero2->nowDirection = hero2->aimDirection;
					hero2->setAction(hero2->nowDirection, "run", 7);
				}
			}
			hero2->moveTo(hero2->nowDirection, hero2->speed);
		}
		//stop running and stand
		else if (hero2->isRun&&runflag2 == false)
		{
			hero2->isRun = false;
			hero2->setAction(hero2->nowDirection, "stand", 4);
		}
	}



	//judge boomset
	if (boomflag1 == true && hero1->judgeMap(boomTiledPosition1) && hero1->bubble > 0 && hero1->isAlive == true)
	{
		boomflag1 = false;//reset boom keyboard
		//create boom
		auto boom = Boom::createBoomSprite(boomPosition1);
		hero1->bubble--;
		_tileMap->addChild(boom);

		//change the tile map to make this tile can't move
		meta->setTileGID(collidableTile, boomTiledPosition1);

		//set boom wave in 1.95 secend
		auto delaySetWave = DelayTime::create(1.95f);
		this->runAction(Sequence::create(delaySetWave, CallFunc::create(CC_CALLBACK_0(HelloWorld::addWave, this, boom->position, hero1->power,hero1)), NULL));

		//remove boom in 2.9 second
		auto delayBoom = DelayTime::create(2.9f);
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoom, this, boom)), NULL));
		//change the tile map to make this tile can move
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoomMeta, this, meta, 0, boomTiledPosition1)), NULL));
	}

	//judge boomset
	if (boomflag2 == true && hero2->judgeMap(boomTiledPosition2) && hero2->bubble > 0 && hero2->isAlive == true)
	{
		boomflag2 = false;//reset boom keyboard
						 //create boom
		auto boom = Boom::createBoomSprite(boomPosition2);
		hero2->bubble--;
		_tileMap->addChild(boom);

		//change the tile map to make this tile can't move
		meta->setTileGID(collidableTile, boomTiledPosition2);

		//set boom wave in 1.95 secend
		auto delaySetWave = DelayTime::create(1.95f);
		this->runAction(Sequence::create(delaySetWave, CallFunc::create(CC_CALLBACK_0(HelloWorld::addWave, this, boom->position, hero2->power,hero2)), NULL));

		//remove boom in 2.9 second
		auto delayBoom = DelayTime::create(2.9f);
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoom, this, boom)), NULL));
		//change the tile map to make this tile can move
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(HelloWorld::removeBoomMeta, this, meta, 0, boomTiledPosition2)), NULL));
	}




	//judge if hero get props
	if (heroAliveFlag1 == true)
	{
		Point tiledPos = getTiledPos(hero1->position);
		int tiledGid = barrier->getTileGIDAt(tiledPos);
		if (tiledGid == bubbleTile)
		{
			hero1->bubble++;
			heroBubble1++;
			barrier->removeTileAt(tiledPos);
		}
		else if (tiledGid == shoesTile)
		{
			hero1->speed += 0.2f;
			barrier->removeTileAt(tiledPos);
		}
		else if (tiledGid == syrupTile)
		{
			hero1->power++;
			barrier->removeTileAt(tiledPos);
		}
	}

	//judge if hero get props
	if (heroAliveFlag2 == true)
	{
		Point tiledPos = getTiledPos(hero2->position);
		int tiledGid = barrier->getTileGIDAt(tiledPos);
		if (tiledGid == bubbleTile)
		{
			hero2->bubble++;
			heroBubble2++;
			barrier->removeTileAt(tiledPos);
		}
		else if (tiledGid == shoesTile)
		{
			hero2->speed += 0.2f;
			barrier->removeTileAt(tiledPos);
		}
		else if (tiledGid == syrupTile)
		{
			hero2->power++;
			barrier->removeTileAt(tiledPos);
		}
	}



	//judge if hero is dead
	if (heroAliveFlag1 == true)
	{
		Point tiledPos = getTiledPos(hero1->position);
		int tiledGid = meta->getTileGIDAt(tiledPos);
		if (tiledGid == waveTile)
		{
			heroAliveFlag1 = false;
			hero1->isAlive = false;
			hero1->setAction(1, "die", 9);
			//remove hero in 1.5 second
			auto delayHeroRemove = DelayTime::create(1.5f);
			hero1->runAction(Sequence::create(delayHeroRemove, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, hero1)), NULL));
			//wait for add director
		}
	}

	if (heroAliveFlag2 == true)
	{
		Point tiledPos = getTiledPos(hero2->position);
		int tiledGid = meta->getTileGIDAt(tiledPos);
		if (tiledGid == waveTile)
		{
			heroAliveFlag2 = false;
			hero2->isAlive = false;
			hero2->setAction(1, "die", 9);
			//remove hero in 1.5 second
			auto delayHeroRemove = DelayTime::create(1.5f);
			hero2->runAction(Sequence::create(delayHeroRemove, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, hero2)), NULL));
			//wait for add director
		}
	}
}




//set the link to keyboard
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//start movement
	if (keycode == EventKeyboard::KeyCode::KEY_W)
	{
		runflag1 = true;
		hero1->aimDirection = 3;
	}
	else if(keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		runflag2 = true;
		hero2->aimDirection = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S)
	{
		runflag1 = true;
		hero1->aimDirection = 4;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		runflag2 = true;
		hero2->aimDirection = 4;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A)
	{
		runflag1 = true;
		hero1->aimDirection = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		runflag2 = true;
		hero2->aimDirection = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D)
	{
		runflag1 = true;
		hero1->aimDirection = 1;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		runflag2 = true;
		hero2->aimDirection = 1;
	}
	//set boom
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J)
	{
		boomflag1 = true;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_KP_ENTER)
	{
		boomflag2 = true;
	}
}




void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_S
		|| keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_D)
		runflag1 = false;
	else if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
		|| keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		runflag2 = false;
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J)
		boomflag1 = false;
	else if (keycode == EventKeyboard::KeyCode::KEY_KP_ENTER)
		boomflag2 = false;
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
void HelloWorld::addWave(Point boomPosition, int Power,Hero* hero)
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

			//give out props
			giveGifts(getTiledPos(aimPoint));
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

			//give out props
			giveGifts(getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}

	//add boom wave to the up side
	for (int i = 1; i <= hero->power; i++)
	{
		Point aimPoint = Point(boomPosition.x, boomPosition.y + i*TileSize);
		Point aimTilePos = getTiledPos(aimPoint);
		int aimTile = isCanReach(aimTilePos);
		if (aimTile ==none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Up);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if(aimTile ==collid)
			break;
		else if (aimTile == props)
		{
			barrier->removeTileAt(getTiledPos(aimPoint));
			meta->removeTileAt(getTiledPos(aimPoint));
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Up);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));

			//give out props
			giveGifts(getTiledPos(aimPoint));
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

			//give out props
			giveGifts(getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
			break;
		}
	}
	//add all waves into a vector
	std::vector<Vector<BoomWave*>> allWave;
	std::vector<Vector<BoomWave*>>::const_iterator pointer;
	int heroBubble;
	if (hero == hero1)
	{
		allWave = allWave1;
		pointer = pointer1;
		heroBubble = heroBubble1;
	}
	else if (hero == hero2)
	{
		allWave = allWave2;
		pointer = pointer2;
		heroBubble = heroBubble2;
	}
	allWave.push_back(waveArray);
	//use pointer to point to these waves
	if (allWave.size() == 1)
		pointer = allWave.begin();
	else
		pointer = allWave.end() - 1;
	std::vector<Vector<BoomWave*>>::const_iterator it = pointer;
	
	//remove these waves in 0.85 second
	auto delayRemoveWave = DelayTime::create(0.85f);
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



//give out props when the wall is boomed
void HelloWorld::giveGifts(Point position)
{
	srand(time(NULL));
	int num = random(1, 8);
	if (num == 1)
	{
		barrier->setTileGID(bubbleTile, position);
	}
	else if (num == 2)
	{
		barrier->setTileGID(shoesTile, position);
	}
	else if (num == 3)
	{
		barrier->setTileGID(syrupTile, position);
	}
}