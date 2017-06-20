#include "ModeSelect.h"
#include "SimpleAudioEngine.h"
#include "DoubleHeroSelect1.h"
#include "SingleHeroSelect.h"
#include "OnlineHeroSelect.h"
#include "FateHeroSelect1.h"


USING_NS_CC;


Scene* ModeSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = ModeSelect::create();
	scene->addChild(layer);
	return scene;
}



//
bool ModeSelect::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();


	MenuItemImage* doubleItem = MenuItemImage::create(
		"DoublePlayerNormal.png",
		"DoublePlayerSelect.png",
		CC_CALLBACK_1(ModeSelect::menuDoubleCallback, this)); //Offline double mode
	doubleItem->setPosition(Vec2(929, 210));
	doubleItem->setScale(1.5f);
	Menu* doubleMenu = Menu::create(doubleItem, NULL);
	doubleMenu->setPosition(Vec2::ZERO);
	this->addChild(doubleMenu, 2);


	MenuItemImage* fateBeatItem = MenuItemImage::create(
		"FateBeatNormal.png",
		"FateBeatSelect.png",
		CC_CALLBACK_1(ModeSelect::menuFateBeatCallback, this));//  fate beat mode 
	fateBeatItem->setPosition(Vec2(929, 160));
	fateBeatItem->setScale(1.5f);
	Menu* fateBeatMenu = Menu::create(fateBeatItem, NULL);
	fateBeatMenu->setPosition(Vec2::ZERO);
	this->addChild(fateBeatMenu, 2);


	MenuItemImage* singlePuzzleItem = MenuItemImage::create(
		"SinglePuzzleNormal.png",
		"SinglePuzzleSelect.png",
		CC_CALLBACK_1(ModeSelect::menuSinglePuzzleCallback, this));//single puzzle 
	singlePuzzleItem->setPosition(Vec2(929, 110));
	singlePuzzleItem->setScale(1.5f);
	Menu* singlePuzzleMenu = Menu::create(singlePuzzleItem, NULL);
	singlePuzzleMenu->setPosition(Vec2::ZERO);
	this->addChild(singlePuzzleMenu, 2);


	MenuItemImage* onLineItem = MenuItemImage::create(
		"OnLineNormal.png",
		"OnLineSelect.png",
		CC_CALLBACK_1(ModeSelect::menuOnLineCallback, this));//online beat 
	onLineItem->setPosition(Vec2(929, 60));
	onLineItem->setScale(1.5f);
	Menu* onLineMenu = Menu::create(onLineItem, NULL);
	onLineMenu->setPosition(Vec2::ZERO);
	this->addChild(onLineMenu, 2);



	auto sprite = Sprite::create("HelloWorld.jpg");


	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


	this->addChild(sprite, 0);

	return true;
}



void ModeSelect::menuDoubleCallback(Ref* pSender)
{
	

	auto scene = DoubleHeroSelect1::createScene();
	Director::getInstance()->replaceScene(scene);
}



void ModeSelect::menuOnLineCallback(Ref* pSender)
{
	auto scene = OnlineHeroSelect::createScene();
	Director::getInstance()->pushScene(scene);
}



void ModeSelect::menuSinglePuzzleCallback(Ref* pSender)
{
	auto scene = SingleHeroSelect::createScene();
	Director::getInstance()->replaceScene(scene);
}



void ModeSelect::menuFateBeatCallback(Ref* pSender)
{
	auto scene = FateHeroSelect1::createScene();
	Director::getInstance()->replaceScene(scene);
}