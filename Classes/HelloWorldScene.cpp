#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// add "HelloWorld" splash screen"




	/*bg = Sprite::create("1.png");

	// position the sprite on the center of the screen
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScale(0.8f);

	// add the sprite as a child to this layer
	this->addChild(bg, 0);*/

	_tileMap = TMXTiledMap::create("map.tmx");
	_tileMap->setPosition(Vec2(200, 100));
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* objGroup = _tileMap->getObjectGroup("objects");
	ValueMap playPointMap = objGroup->getObject("playerPoint");
	Point playPoint;
	playPoint.x = playPointMap.at("x").asFloat();
	playPoint.y = playPointMap.at("y").asFloat();


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);


	addHero(_tileMap, playPoint);
	_tileMap->addChild(hero,10);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, hero);
	
	
	schedule(schedule_selector(HelloWorld::update), 0.01f);

	
    return true;
}

void HelloWorld::update(float dt)
{
	if (keyflag ==1)
	{
		if (hero->isRun == false)
		{
			hero->isRun = true;
			hero->direction = direction;
			hero->setAction(hero->direction, "run", 7);
		}
		else if (hero->isRun == true)
		{
			if (hero->direction != direction)
			{
				hero->direction = direction;
				hero->setAction(hero->direction, "run", 7);
			}
		}
		hero->moveTo(hero->direction);
	}
	else if (keyflag == 2)
	{
		auto boom = Boom::createBoomSprite(hero->position);
		_tileMap->addChild(boom);
		auto delayTime = DelayTime::create(3.0f);
		boom->runAction(Sequence::create(delayTime, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, boom)), NULL));

	}
	else if (hero->isRun&&keyflag ==0)
	{
		hero->isRun = false;
		hero->setAction(hero->direction, "stand", 4);
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_W)
	{
		keyflag = 1;
		direction = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW || keycode == EventKeyboard::KeyCode::KEY_S)
	{
		keyflag = 1;
		direction = 4;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_A)
	{
		keyflag = 1;
		direction = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_D)
	{
		keyflag = 1;
		direction = 1;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE || keycode == EventKeyboard::KeyCode::KEY_J || keycode == EventKeyboard::KeyCode::KEY_KP_ENTER)
	{
		keyflag = 2;
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	keyflag = 0;
}


void HelloWorld::addHero(TMXTiledMap* map,Point startPoint)
{
	hero = Hero::createHeroSprite(startPoint, 4, "stand");
	hero->setTiledMap(map);
}