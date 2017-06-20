#include "SinglePuzzle.h"
#include "SimpleAudioEngine.h"
#include "HelloWorld.h"


#define TileSize 32
#define MapNum 17
#define collidableTile 70
#define propsTile 84
#define waveTile 98
#define winTile 112
#define bubbleTile 14
#define shoesTile 28
#define syrupTile 42


USING_NS_CC;


//init scene
Scene* SinglePuzzle::createScene(char* aimhero1)
{
	auto scene = Scene::create();
	auto layer = SinglePuzzle::create(aimhero1);
	scene->addChild(layer);
	return scene;
}



//overload create() to accept the information of hero
SinglePuzzle* SinglePuzzle::create(char* aimhero1)
{
	SinglePuzzle* pRet = new SinglePuzzle();
	//save hero1's information into a variable
	pRet->heroName1 = aimhero1;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}



//init game scene
bool SinglePuzzle::init()
{
	if (!Layer::init())
	{
		return false;
	}
    //get visible size of the game 
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //set background picture 
	auto background = Sprite::create("OffLineDoublePlayer.jpg");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);

	//add map data
	_tileMap = TMXTiledMap::create(map);
	_tileMap->setPosition(Vec2(600, 100));//wait for updata
	addChild(_tileMap, 0, 100);
	this->meta = _tileMap->getLayer("meta");
	this->barrier = _tileMap->getLayer("barrier");

	//set player start point
	TMXObjectGroup* objGroup = _tileMap->getObjectGroup("objects");
	ValueMap playPointMap1 = objGroup->getObject("playerPoint");
	Point playPoint1;
	playPoint1.x = playPointMap1.at("x").asFloat();
	playPoint1.y = playPointMap1.at("y").asFloat();

	//add hero to map, init hero's position
	hero1 = Hero::createHeroSprite(playPoint1, 4, heroName1);
	hero1->setTiledMap(_tileMap);
	_tileMap->addChild(hero1, 10);

	//add keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SinglePuzzle::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SinglePuzzle::onKeyReleased, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _tileMap);

	//add schedule update
	schedule(schedule_selector(SinglePuzzle::update), 0.01f);

	return true;
}



//
void SinglePuzzle::update(float dt)
{
	//calibration boom position
	Point boomPosition1 = getBoomPosition(hero1->position);
	//get boom position of tile map
	Point boomTiledPosition1 = getTiledPos(boomPosition1);

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
			hero1->moveTo(hero1->nowDirection, hero1->speed);
		}
		//stop running and stand
		else if (hero1->isRun&&runflag1 == false)
		{
			hero1->isRun = false;
			hero1->setAction(hero1->nowDirection, "stand", 4);
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
		this->runAction(Sequence::create(delaySetWave, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::addWave, this, boom->position, hero1->power, hero1)), NULL));

		//remove boom in 2.9 second
		auto delayBoom = DelayTime::create(2.9f);
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::removeBoom, this, boom)), NULL));
		//change the tile map to make this tile can move
		this->runAction(Sequence::create(delayBoom, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::removeBoomMeta, this, meta, 0, boomTiledPosition1)), NULL));
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

			auto delayGameOver = DelayTime::create(1.8f);
			this->runAction(Sequence::create(delayGameOver, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::gameOver, this,false)), NULL));
		}
	}


	//judge if hero is win
	if (heroAliveFlag1 == true)
	{
		Point tiledPos = getTiledPos(hero1->position);
		int tiledGid = meta->getTileGIDAt(tiledPos);
		if (tiledGid == winTile)
		{
			heroAliveFlag1 = false;
			hero1->isAlive = false;
			hero1->removeFromParent();
			auto delayGameOver = DelayTime::create(0.5f);
			this->runAction(Sequence::create(delayGameOver, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::gameOver, this, true)), NULL));
		}
	}
}



//set the link to keyboard
void SinglePuzzle::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	//start movement
	if (keycode == EventKeyboard::KeyCode::KEY_W&&heroAliveFlag1 == true)
	{
		runflag1 = true;
		hero1->aimDirection = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S&&heroAliveFlag1 == true)
	{
		runflag1 = true;
		hero1->aimDirection = 4;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A&&heroAliveFlag1 == true)
	{
		runflag1 = true;
		hero1->aimDirection = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D&&heroAliveFlag1 == true)
	{
		runflag1 = true;
		hero1->aimDirection = 1;
	}
	//set boom
	else if ((keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J) && heroAliveFlag1 == true)
	{
		boomflag1 = true;
	}
}



//to change the status of hero when the keyboard is released
void SinglePuzzle::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	if ((keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_S
		|| keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_D) && heroAliveFlag1 == true)
		runflag1 = false;
	else if ((keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J) && heroAliveFlag1 == true)
		boomflag1 = false;
}



//calibration boom position
Point SinglePuzzle::getBoomPosition(cocos2d::Point position)
{
	Point boomPoint;
	boomPoint.x = ((int)(position.x / TileSize))*TileSize + TileSize / 2;
	boomPoint.y = ((int)(position.y / TileSize))*TileSize + TileSize / 2;
	return boomPoint;
}



//add boom wave
void SinglePuzzle::addWave(Point boomPosition, int Power, Hero* hero)
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
		if (isCanReach(getTiledPos(aimPoint)) == none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Right);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		//if the right side is a wall,stop creating
		else if (isCanReach(getTiledPos(aimPoint)) == collid)
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
		if (isCanReach(getTiledPos(aimPoint)) == none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Left);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if (isCanReach(getTiledPos(aimPoint)) == collid)
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
		if (aimTile == none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Up);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if (aimTile == collid)
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
		if (isCanReach(getTiledPos(aimPoint)) == none)
		{
			BoomWave* wave = BoomWave::createWaveSprite(aimPoint, Down);
			meta->setTileGID(waveTile, getTiledPos(aimPoint));
			waveArray.pushBack(wave);
			_tileMap->addChild(wave, 9);
		}
		else if (isCanReach(getTiledPos(aimPoint)) == collid)
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
	allWave.push_back(waveArray);

	//use pointer to point to these waves
	if (allWave.size() == 1)
		pointer = allWave.begin();
	else
		pointer = allWave.end() - 1;
	std::vector<Vector<BoomWave*>>::const_iterator it = pointer;

	//remove these waves in 0.85 second
	auto delayRemoveWave = DelayTime::create(0.85f);
	this->runAction(Sequence::create(delayRemoveWave, CallFunc::create(CC_CALLBACK_0(SinglePuzzle::removeWave, this, *it)), NULL));

	//reset hero's boom number
	hero->bubble++;

	//clear the vector
	if (hero->bubble == heroBubble)
		allWave.clear();
}



//remove boom waves
void SinglePuzzle::removeWave(Vector<BoomWave*> waveArray)
{
	for (Vector<BoomWave*>::const_iterator it = waveArray.begin(); it != waveArray.end(); it++)
	{
		meta->removeTileAt(getTiledPos((*it)->position));
		(*it)->removeFromParent();
	}

}



//judge what kind of things is on this tild
int SinglePuzzle::isCanReach(Point tiledPos)
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
void SinglePuzzle::removeBoomMeta(TMXLayer* meta, int gid, Point boomTiledPosition)
{
	meta->setTileGID(gid, boomTiledPosition);
}



//change globle position into tiled position
Point SinglePuzzle::getTiledPos(Point position)
{
	Point tiledPos;
	tiledPos.x = (int)position.x / TileSize;
	tiledPos.y = (int)((MapNum*TileSize - position.y) / TileSize);
	return tiledPos;
}



//remove boom when it's boom is over
void SinglePuzzle::removeBoom(Boom* boom)
{
	boom->removeFromParent();
}



//give out props when the wall is boomed
void SinglePuzzle::giveGifts(Point position)
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



//to stop this game
void SinglePuzzle::gameOver(bool isReach)
{
	//unload the update
	unscheduleUpdate();

	//create the tips to adviec that the game is over
	TTFConfig ttfconfig("use.ttf", 200);
	if (isReach)
	{
		auto lable = Label::createWithTTF(ttfconfig, "GOOD GAME");
		lable->setPosition(Vec2(600, 500));
		this->addChild(lable, 1);
	}
	else
	{
		auto lable = Label::createWithTTF(ttfconfig, "Emmmmmmm");
		lable->setPosition(Vec2(600, 500));
		this->addChild(lable, 1);
	}
	

	//to create a button to play again
	MenuItemImage* againItem = MenuItemImage::create(
		"AgainNormal.png",
		"AgainSelect.png",
		CC_CALLBACK_1(SinglePuzzle::menuAgainCallback, this));
	againItem->setPosition(Vec2(600, 250));
	againItem->setScale(1.5f);
	Menu* againMenu = Menu::create(againItem, NULL);
	againMenu->setPosition(Vec2::ZERO);
	this->addChild(againMenu, 2);

	//to create a button to go back to the root scene
	MenuItemImage* rootItem = MenuItemImage::create(
		"RootNormal.png",
		"RootSelect.png",
		CC_CALLBACK_1(SinglePuzzle::menuRootCallback, this));
	rootItem->setPosition(Vec2(600, 300));
	rootItem->setScale(1.5f);
	Menu* rootMenu = Menu::create(rootItem, NULL);
	rootMenu->setPosition(Vec2::ZERO);
	this->addChild(rootMenu, 2);

	//to create a button to end the game
	MenuItemImage* closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelect.png",
		CC_CALLBACK_1(SinglePuzzle::menuCloseCallback, this));
	closeItem->setPosition(Vec2(600, 200));
	closeItem->setScale(1.5f);
	Menu* closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 2);
}



//to play again this mode
void SinglePuzzle::menuAgainCallback(cocos2d::Ref* pSender)
{
	auto scene = SinglePuzzle::createScene(heroName1);
	Director::getInstance()->replaceScene(scene);
}



//to change into the root scene
void SinglePuzzle::menuRootCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloBubble::createScene();
	Director::getInstance()->replaceScene(scene);
}



//to end the game
void SinglePuzzle::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	exit(0);
#endif
}
