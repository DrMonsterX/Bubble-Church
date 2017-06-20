#include <cstdlib>  
#include <iostream>  
#include <boost/asio.hpp>  
#include <client.hpp> 
#include <orderMessage.hpp>


USING_NS_CC;


using boost::asio::ip::tcp;
using namespace std;


bool ifGetClient = false;
static client * getSelectClient = nullptr;                  
static char id[8] = "player";  //Record player ID
//Building links to servers
static boost::asio::io_service ioService;
static tcp::resolver resolver(ioService);
static tcp::resolver::query query("115.159.199.161", "33668");
static tcp::resolver::iterator cIterator = resolver.resolve(query);
static client cClient(ioService, cIterator);
	

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
	getSelectClient->getPSelect(this); //Save the scene class object in the client class object, which is convenient for information processing.
	loginMsg.getName(name, strlen(name)); //Send login message
	loginMsg.login();
	cClient.write(loginMsg);
	
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



//Command information processing
void OnlineHeroSelect::progressOrder1(orderMessage msg) 
{
	char type = msg.getOrder();

	 if (type == '9') 
	 {
		if (ifGetClient == false) 
		{
			if (getPlayer1(msg) == 0)
			{
				id[6] = '1';
			}
			else if (getPlayer1(msg) == 1)
			{
				id[6] = '2';
			}        //save player id
			roleChoice.getId(id);
			ifGetCoginient = true;
		}
		
	}
}



//Determine command information source
int OnlineHeroSelect::getPlayer1(orderMessage msg)
{
	if (msg.playerNum() == '1')
		return 0;//player1->progressOrder(msg);
	else	if (msg.playerNum() == '2')
		return 1;	//player2->progressOrder(msg);
	else	if (msg.playerNum() == '3')
		return 2;//player3->progressOrder(msg);
	else	if (msg.playerNum() == '4')
		return 3; // player4->progressOrder(msg);
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
		roleChoice.roleA();
	}
	else if (hero1 == "ssx")
	{
		roleChoice.roleB();
	}
	else if (hero1 == "hyy")
	{
		roleChoice.roleC();
	}
	else if (hero1 == "dd")
	{
		roleChoice.roleD();
	}
	(*getSelectClient).write(roleChoice);

	
	auto scene = OnLinePlay::createScene(getSelectClient, id);
	Director::getInstance()->pushScene(scene);
}