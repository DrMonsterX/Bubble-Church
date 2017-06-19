#include "HelloWorld.h"
#include "ModeSelect.h"
#include "Help.h"
#include "Setting.h"


USING_NS_CC;


Scene* HelloBubble::createScene()
{
	return HelloBubble::create();
}



//
bool HelloBubble::init()
{
	
	if (!Scene::init())
	{
		return false;
	}
	
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	
	MenuItemImage* startItem = MenuItemImage::create(
		"StartNormal.png",
		"StartSelect.png",
		CC_CALLBACK_1(HelloBubble::menuStartCallback, this));
	startItem->setPosition(Vec2(929, 210));
	startItem->setScale(1.5f);
	Menu* startmenu = Menu::create(startItem, NULL);
	startmenu->setPosition(Vec2::ZERO);
	this->addChild(startmenu, 2);


	MenuItemImage* settingItem = MenuItemImage::create(
		"SettingNormal.png",
		"SettingSelect.png",
		CC_CALLBACK_1(HelloBubble::menuSettingCallback, this));
	settingItem->setPosition(Vec2(929, 160));
	settingItem->setScale(1.5f);
	Menu* settingmenu = Menu::create(settingItem, NULL);
	settingmenu->setPosition(Vec2::ZERO);
	this->addChild(settingmenu, 2);


	MenuItemImage* helpItem = MenuItemImage::create(
		"HelpNormal.png",
		"HelpSelect.png",
		CC_CALLBACK_1(HelloBubble::menuHelpCallback, this));
	helpItem->setPosition(Vec2(929, 110));
	helpItem->setScale(1.5f);
	Menu* helpmenu = Menu::create(helpItem, NULL);
	helpmenu->setPosition(Vec2::ZERO);
	this->addChild(helpmenu, 2);


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelect.png",
		CC_CALLBACK_1(HelloBubble::menuCloseCallback, this));
	closeItem->setPosition(Vec2(929,60));
	closeItem->setScale(1.5f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	auto sprite = Sprite::create("HelloWorld.jpg");

	
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	
	this->addChild(sprite, 0);

	return true;
}



//
void HelloBubble::menuCloseCallback(Ref* pSender)
{
	
	Director::getInstance()->end();
	exit(0);
   #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	exit(0);
   #endif
}



//
void HelloBubble::menuStartCallback(Ref* pSender)
{
	auto scene = ModeSelect::createScene();
	Director::getInstance()->replaceScene(scene);
}



//
void HelloBubble::menuSettingCallback(Ref* pSender)
{
	auto scene = Setting::createScene();
	Director::getInstance()->pushScene(scene);
}



//
void HelloBubble::menuHelpCallback(Ref* pSender)
{
	auto scene = Help::createScene();
	Director::getInstance()->pushScene(scene);
}