#include "DoubleHeroSelect2.h"
#include "DoubleMapSelect.h"


USING_NS_CC;

//init scene 
Scene* DoubleHeroSelect2::createScene(char* hero1)
{
	auto scene = Scene::create();
	auto layer = DoubleHeroSelect2::create(hero1);
	scene->addChild(layer);
	return scene;
}



//overload DoubleHeroSelect2::create()
DoubleHeroSelect2* DoubleHeroSelect2::create(char* aimhero1)
{
	DoubleHeroSelect2* pRet = new DoubleHeroSelect2();
	//save hero1's information into a variable
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



//init hero select scene
bool DoubleHeroSelect2::init()
{

	if (!Layer::init())
	{
		return false;
	}
    //get visible size of the game
	auto visibleSize = Director::getInstance()->getVisibleSize();

    
    //create a button to select hero "Zhao Yun"
	MenuItemImage* heroItem1 = MenuItemImage::create(
		"zystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback1, this));
    //set button's attribute
	heroItem1->setPosition(Vec2(210, 530));
	heroItem1->setScale(1.5f);
	//create menu and add it
	Menu* heroMenu1 = Menu::create(heroItem1, NULL);
	heroMenu1->setPosition(Vec2::ZERO);
	this->addChild(heroMenu1, 2);


    //create a button to select hero "Sun Shangxiang"
	MenuItemImage* heroItem2 = MenuItemImage::create(
		"ssxstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback2, this));
    //set button's attribute
	heroItem2->setPosition(Vec2(600, 530));
	heroItem2->setScale(1.5f);
	//create menu and add it
	Menu* heroMenu2 = Menu::create(heroItem2, NULL);
	heroMenu2->setPosition(Vec2::ZERO);
	this->addChild(heroMenu2, 2);


    //create a button to select hero "Huang Yueying"
	MenuItemImage* heroItem3 = MenuItemImage::create(
		"hyystand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback3, this));
	//set button's attribute
	heroItem3->setPosition(Vec2(210, 236));
	heroItem3->setScale(2);
	//create menu and add it
	Menu* heroMenu3 = Menu::create(heroItem3, NULL);
	heroMenu3->setPosition(Vec2::ZERO);
	this->addChild(heroMenu3, 2);


    //create a button to select hero "Zhou Yu"
	MenuItemImage* heroItem4 = MenuItemImage::create(
		"ddstand41.png",
		"HeroSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuHeroCallback4, this));
	//set button's attribute
	heroItem4->setPosition(Vec2(600, 236));
	heroItem4->setScale(1.4f);
	//create menu and add it
	Menu* heroMenu4 = Menu::create(heroItem4, NULL);
	heroMenu4->setPosition(Vec2::ZERO);
	this->addChild(heroMenu4, 2);


    //create a button to make sure your select and go into the next scene
	MenuItemImage* SelectItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(DoubleHeroSelect2::menuSelectCallBack, this));
	//set button's attribute
	SelectItem->setPosition(Vec2(405, 60));
	SelectItem->setScale(1.8f);
	//create menu and add it
	Menu* selectMenu = Menu::create(SelectItem, NULL);
	selectMenu->setPosition(Vec2::ZERO);
	this->addChild(selectMenu, 2);


    //set the background picture
	auto sprite = Sprite::create("SelectHero.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);


    //set the tips of this scene
	TTFConfig ttfconfig("use.ttf", 80);
	auto lable = Label::createWithTTF(ttfconfig, "Player 2");
	lable->setPosition(Vec2(405, 383));
	this->addChild(lable, 1);

	return true;
}



//to select the hero "Zhao Yun"
void DoubleHeroSelect2::menuHeroCallback1(cocos2d::Ref* pSender)
{
	hero2 = "zy";
}



//to select the hero "Sun Shangxiang"
void DoubleHeroSelect2::menuHeroCallback2(cocos2d::Ref* pSender)
{
	hero2 = "ssx";
}



//to select the hero "Huang Yueying"
void DoubleHeroSelect2::menuHeroCallback3(cocos2d::Ref* pSender)
{
	hero2 = "hyy";
}



//to select the hero "Zhou Yu"
void DoubleHeroSelect2::menuHeroCallback4(cocos2d::Ref* pSender)
{
	hero2 = "dd";
}



//to make sure your select and change into the next scene
void DoubleHeroSelect2::menuSelectCallBack(cocos2d::Ref* pSender)
{
	auto scene = DoubleMapSelect::createScene(hero1, hero2);
	Director::getInstance()->replaceScene(scene);
}
