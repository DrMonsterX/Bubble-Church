#include "DoubleHeroSelect2.h"
#include "DoubleMapSelect.h"

USING_NS_CC;

Scene* DoubleHeroSelect2::createScene(char* hero1)
{
	auto scene = Scene::create();
	auto layer = DoubleHeroSelect2::create(hero1);
	scene->addChild(layer);
	return scene;
}


DoubleHeroSelect2* DoubleHeroSelect2::create(char* aimhero1)
{
	DoubleHeroSelect2* pRet = new DoubleHeroSelect2();
	pRet->hero1 = aimhero1;
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


bool DoubleHeroSelect2::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();


	MenuItemImage* heroItem1 = MenuItemImage::create(
		"zystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback1, this));
	heroItem1->setPosition(Vec2(210, 530));
	heroItem1->setScale(1.5f);
	Menu* heroMenu1 = Menu::create(heroItem1, NULL);
	heroMenu1->setPosition(Vec2::ZERO);
	this->addChild(heroMenu1, 2);


	MenuItemImage* heroItem2 = MenuItemImage::create(
		"ssxstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback2, this));
	heroItem2->setPosition(Vec2(600, 530));
	heroItem2->setScale(1.5f);
	Menu* heroMenu2 = Menu::create(heroItem2, NULL);
	heroMenu2->setPosition(Vec2::ZERO);
	this->addChild(heroMenu2, 2);


	MenuItemImage* heroItem3 = MenuItemImage::create(
		"hyystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback3, this));
	heroItem3->setPosition(Vec2(210, 236));
	heroItem3->setScale(2);
	Menu* heroMenu3 = Menu::create(heroItem3, NULL);
	heroMenu3->setPosition(Vec2::ZERO);
	this->addChild(heroMenu3, 2);


	MenuItemImage* heroItem4 = MenuItemImage::create(
		"ddstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback4, this));
	heroItem4->setPosition(Vec2(600, 236));
	heroItem4->setScale(1.4f);
	Menu* heroMenu4 = Menu::create(heroItem4, NULL);
	heroMenu4->setPosition(Vec2::ZERO);
	this->addChild(heroMenu4, 2);


	MenuItemImage* SelectItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuSelectCallBack, this));
	SelectItem->setPosition(Vec2(405, 60));
	SelectItem->setScale(1.8f);
	Menu* selectMenu = Menu::create(SelectItem, NULL);
	selectMenu->setPosition(Vec2::ZERO);
	this->addChild(selectMenu, 2);



	auto sprite = Sprite::create("SelectHero.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);


	TTFConfig ttfconfig("use.ttf", 80);
	auto lable = Label::createWithTTF(ttfconfig, "Player 2");
	lable->setPosition(Vec2(405, 383));
	this->addChild(lable, 1);

	return true;
}


void DoubleHeroSelect2::menuHeroCallback1(cocos2d::Ref* pSender)
{
	hero2 = "zy";
}



void DoubleHeroSelect2::menuHeroCallback2(cocos2d::Ref* pSender)
{
	hero2 = "ssx";
}



void DoubleHeroSelect2::menuHeroCallback3(cocos2d::Ref* pSender)
{
	hero2 = "hyy";
}



void DoubleHeroSelect2::menuHeroCallback4(cocos2d::Ref* pSender)
{
	hero2 = "dd";
}


void DoubleHeroSelect2::menuSelectCallBack(cocos2d::Ref* pSender)
{
	auto scene = DoubleMapSelect::createScene(hero1, hero2);
	Director::getInstance()->replaceScene(scene);
}