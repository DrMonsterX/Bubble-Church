#include "ModeSelect.h"
#include "SimpleAudioEngine.h"
#include "DoubleHeroSelect1.h"
#include "SingleHeroSelect.h"
#include "OnlineHeroSelect.h"
#include "FateHeroSelect1.h"
#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <client.hpp> 
#include <boost/order_message.hpp>

USING_NS_CC;
using boost::asio::ip::tcp;
using namespace std;


Scene* ModeSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = ModeSelect::create();
	scene->addChild(layer);
	return scene;
}


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
		CC_CALLBACK_1(ModeSelect::menuDoubleCallback, this));
	doubleItem->setPosition(Vec2(929, 210));
	doubleItem->setScale(1.5f);
	Menu* doubleMenu = Menu::create(doubleItem, NULL);
	doubleMenu->setPosition(Vec2::ZERO);
	this->addChild(doubleMenu, 2);


	MenuItemImage* fateBeatItem = MenuItemImage::create(
		"FateBeatNormal.png",
		"FateBeatSelect.png",
		CC_CALLBACK_1(ModeSelect::menuFateBeatCallback, this));
	fateBeatItem->setPosition(Vec2(929, 160));
	fateBeatItem->setScale(1.5f);
	Menu* fateBeatMenu = Menu::create(fateBeatItem, NULL);
	fateBeatMenu->setPosition(Vec2::ZERO);
	this->addChild(fateBeatMenu, 2);


	MenuItemImage* singlePuzzleItem = MenuItemImage::create(
		"SinglePuzzleNormal.png",
		"SinglePuzzleSelect.png",
		CC_CALLBACK_1(ModeSelect::menuSinglePuzzleCallback, this));
	singlePuzzleItem->setPosition(Vec2(929, 110));
	singlePuzzleItem->setScale(1.5f);
	Menu* singlePuzzleMenu = Menu::create(singlePuzzleItem, NULL);
	singlePuzzleMenu->setPosition(Vec2::ZERO);
	this->addChild(singlePuzzleMenu, 2);


	MenuItemImage* onLineItem = MenuItemImage::create(
		"OnLineNormal.png",
		"OnLineSelect.png",
		CC_CALLBACK_1(ModeSelect::menuOnLineCallback, this));
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

/*void ModeSelect::connect()
{
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("115.159.199.161", "1000");
	tcp::resolver::iterator iterator = resolver.resolve(query);
	client cClient(io_service, iterator);
	client &c = cClient;
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
	t.join();
	auto scene = OnlineHeroSelect::createScene(c);
	Director::getInstance()->pushScene(scene);
	while (1)
	{
		;
	}
}*/

void ModeSelect::menuOnLineCallback(Ref* pSender)
{
	/*boost::thread t_connect(boost::bind(&ModeSelect::connect, this));      
	t_connect.join();*/
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