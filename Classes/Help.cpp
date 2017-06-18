#include "Help.h"
#include "SimpleAudioEngine.h"
#include "HelloWorld.h"

USING_NS_CC;

Scene* Help::createScene()
{
	return Help::create();
}


bool Help::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();


	MenuItemImage* helpItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(Help::menuSelectCallback, this));
	helpItem->setPosition(Vec2(759, 65));
	helpItem->setScale(1.8f);
	Menu* helpmenu = Menu::create(helpItem, NULL);
	helpmenu->setPosition(Vec2::ZERO);
	this->addChild(helpmenu, 2);


	auto sprite = Sprite::create("Help.jpg");


	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


	this->addChild(sprite, 0);

	return true;
}


void Help::menuSelectCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}