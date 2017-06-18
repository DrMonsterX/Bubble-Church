#include "SingleHeroSelect.h"
#include "SinglePuzzle.h"

USING_NS_CC;

Scene* SingleHeroSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = SingleHeroSelect::create();
	scene->addChild(layer);
	return scene;
}


bool SingleHeroSelect::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();


	MenuItemImage* heroItem1 = MenuItemImage::create(
		"zystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(SingleHeroSelect::menuHeroCallback1, this));
	heroItem1->setPosition(Vec2(210, 530));
	heroItem1->setScale(1.5f);
	Menu* heroMenu1 = Menu::create(heroItem1, NULL);
	heroMenu1->setPosition(Vec2::ZERO);
	this->addChild(heroMenu1, 2);


	MenuItemImage* heroItem2 = MenuItemImage::create(
		"ssxstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(SingleHeroSelect::menuHeroCallback2, this));
	heroItem2->setPosition(Vec2(600, 530));
	heroItem2->setScale(1.5f);
	Menu* heroMenu2 = Menu::create(heroItem2, NULL);
	heroMenu2->setPosition(Vec2::ZERO);
	this->addChild(heroMenu2, 2);


	MenuItemImage* heroItem3 = MenuItemImage::create(
		"hyystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(SingleHeroSelect::menuHeroCallback3, this));
	heroItem3->setPosition(Vec2(210, 236));
	heroItem3->setScale(2);
	Menu* heroMenu3 = Menu::create(heroItem3, NULL);
	heroMenu3->setPosition(Vec2::ZERO);
	this->addChild(heroMenu3, 2);


	MenuItemImage* heroItem4 = MenuItemImage::create(
		"ddstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(SingleHeroSelect::menuHeroCallback4, this));
	heroItem4->setPosition(Vec2(600, 236));
	heroItem4->setScale(1.4f);
	Menu* heroMenu4 = Menu::create(heroItem4, NULL);
	heroMenu4->setPosition(Vec2::ZERO);
	this->addChild(heroMenu4, 2);


	MenuItemImage* SelectItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(SingleHeroSelect::menuSelectCallBack, this));
	SelectItem->setPosition(Vec2(405, 60));
	SelectItem->setScale(1.8f);
	Menu* selectMenu = Menu::create(SelectItem, NULL);
	selectMenu->setPosition(Vec2::ZERO);
	this->addChild(selectMenu, 2);



	auto sprite = Sprite::create("SelectHero.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);


	TTFConfig ttfconfig("use.ttf", 80);
	auto lable = Label::createWithTTF(ttfconfig, "Single Puzzle");
	lable->setPosition(Vec2(405, 383));
	this->addChild(lable, 1);

	return true;
}


void SingleHeroSelect::menuHeroCallback1(cocos2d::Ref* pSender)
{
	hero1 = "zy";
}



void SingleHeroSelect::menuHeroCallback2(cocos2d::Ref* pSender)
{
	hero1 = "ssx";
}



void SingleHeroSelect::menuHeroCallback3(cocos2d::Ref* pSender)
{
	hero1 = "hyy";
}



void SingleHeroSelect::menuHeroCallback4(cocos2d::Ref* pSender)
{
	hero1 = "dd";
}


void SingleHeroSelect::menuSelectCallBack(cocos2d::Ref* pSender)
{
	auto scene = SinglePuzzle::createScene(hero1);
	Director::getInstance()->replaceScene(scene);
}