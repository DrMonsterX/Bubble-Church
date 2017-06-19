//#include "OnlineHeroSelect.h"
//#include "OnLinePlay.h"
#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <client.hpp> 
#include <boost/order_message.hpp>
;
USING_NS_CC;
using boost::asio::ip::tcp;
using namespace std;


bool ifGetClient = false;
static client * getSelectClient = nullptr;
char ip[8] = "player";
static boost::asio::io_service io_service;
static tcp::resolver resolver(io_service);
static tcp::resolver::query query("115.159.199.161", "33668");
static tcp::resolver::iterator cIterator = resolver.resolve(query);
static client cClient(io_service, cIterator);
static boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
	

Scene* OnlineHeroSelect::createScene()
{
	
	auto scene = Scene::create();
	auto layer = OnlineHeroSelect::create();
	scene->addChild(layer);
	return scene;
}


OnlineHeroSelect* OnlineHeroSelect::create()
{
	OnlineHeroSelect* pRet = new OnlineHeroSelect();
	
	
	
	

	bool x = pRet->init();
	if (pRet&&x)
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





bool OnlineHeroSelect::init()
{

	if (!Layer::init())
	{
		return false;
	}
	
	getSelectClient = &cClient;
	getSelectClient->getPSelect(this);
	login_msg.get_name(name, strlen(name));
	login_msg.login();
	cClient.write(login_msg);
	
	Sprite* select1 = Sprite::create("SelectHeroOnline.jpg");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	ccMenuCallback x = CC_CALLBACK_1(OnlineHeroSelect::menuHeroCallback1, this);
	//Sprite* normal1 = Sprite::create("zystand41.png");

	std::string normal2 = "zystand41.png";
	std::string select2 = "HeroSelect.png";
	MenuItemImage* heroItem1 = MenuItemImage::create(
		normal2, select2,
		x/*CC_CALLBACK_1(OnlineHeroSelect::menuHeroCallback1, this)*/);
	heroItem1->setPosition(Vec2(210, 530));
	heroItem1->setScale(1.5f);
	Menu* heroMenu1 = Menu::create(heroItem1, NULL);
	heroMenu1->setPosition(Vec2::ZERO);
	this->addChild(heroMenu1, 2);


	MenuItemImage* heroItem2 = MenuItemImage::create(
		"ssxstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(OnlineHeroSelect::menuHeroCallback2, this));
	heroItem2->setPosition(Vec2(600, 530));
	heroItem2->setScale(1.5f);
	Menu* heroMenu2 = Menu::create(heroItem2, NULL);
	heroMenu2->setPosition(Vec2::ZERO);
	this->addChild(heroMenu2, 2);


	MenuItemImage* heroItem3 = MenuItemImage::create(
		"hyystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(OnlineHeroSelect::menuHeroCallback3, this));
	heroItem3->setPosition(Vec2(210, 236));
	heroItem3->setScale(2);
	Menu* heroMenu3 = Menu::create(heroItem3, NULL);
	heroMenu3->setPosition(Vec2::ZERO);
	this->addChild(heroMenu3, 2);


	MenuItemImage* heroItem4 = MenuItemImage::create(
		"ddstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(OnlineHeroSelect::menuHeroCallback4, this));
	heroItem4->setPosition(Vec2(600, 236));
	heroItem4->setScale(1.4f);
	Menu* heroMenu4 = Menu::create(heroItem4, NULL);
	heroMenu4->setPosition(Vec2::ZERO);
	this->addChild(heroMenu4, 2);


	MenuItemImage* SelectItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(OnlineHeroSelect::menuSelectCallBack, this));
	SelectItem->setPosition(Vec2(405, 60));
	SelectItem->setScale(1.8f);
	Menu* selectMenu = Menu::create(SelectItem, NULL);
	selectMenu->setPosition(Vec2::ZERO);
	this->addChild(selectMenu, 2);



	auto sprite = Sprite::create("SelectHeroOnline.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);


	TTFConfig ttfconfig("use.ttf", 80);
	auto lable = Label::createWithTTF(ttfconfig, "HERO NEVER DIE");
	lable->setPosition(Vec2(405, 383));
	this->addChild(lable, 1);
	
	return true;
}

void OnlineHeroSelect::progress_order1(order_message msg)
{
	char type = msg.get_order();

	if (type == '8') {
		;//
	}
	else if (type == '9') {
		if (ifGetClient == false) {
			if (get_player1(msg) == 0)
			{
				ip[6] = '1';
			}
			else if (get_player1(msg) == 1)
			{
				ip[6] = '2';
			}        //player id ��¼
			role_choice.get_ip(ip);
			ifGetClient = true;
		}
		
	}

	else if (type == 'a') {
		;//choose mapA
	}
	else if (type == 'b') {
		;//choose mapB
	}
	else if (type == 'c') {
		;//choose mapC
	}
	else if (type == 'd') {
		;//choose mapD
	}

}



int OnlineHeroSelect::get_player1(order_message msg)
{
	if (msg.player_num() == '1')
		return 0;//player1->progress_order(msg);
	else	if (msg.player_num() == '2')
		return 1;	//player2->progress_order(msg);
	else	if (msg.player_num() == '3')
		return 2;//player3->progress_order(msg);
	else	if (msg.player_num() == '4')
		return 3; // player4->progress_order(msg);
}


void OnlineHeroSelect::menuHeroCallback1(cocos2d::Ref* pSender)
{
	hero1 = "zy";
}



void OnlineHeroSelect::menuHeroCallback2(cocos2d::Ref* pSender)
{
	hero1 = "ssx";
}



void OnlineHeroSelect::menuHeroCallback3(cocos2d::Ref* pSender)
{
	hero1 = "hyy";
}



void OnlineHeroSelect::menuHeroCallback4(cocos2d::Ref* pSender)
{
	hero1 = "dd";
}


void OnlineHeroSelect::menuSelectCallBack(cocos2d::Ref* pSender)
{

	if (hero1 == "zy")
	{
		role_choice.roleA();
	}
	else if (hero1 == "ssx")
	{
		role_choice.roleB();
	}
	else if (hero1 == "hyy")
	{
		role_choice.roleC();
	}
	else if (hero1 == "dd")
	{
		role_choice.roleD();
	}
	(*getSelectClient).write(role_choice);

	
	auto scene = OnLinePlay::createScene(getSelectClient, ip);
	Director::getInstance()->pushScene(scene);
}