#include "DoubleMapSelect.h"
#include "SimpleAudioEngine.h"
#include "OffLineDoublePlayer.h"


USING_NS_CC;


//init scene
Scene* DoubleMapSelect::createScene(char* aimhero1,char* aimhero2)
{
	auto scene = Scene::create();
	auto layer = DoubleMapSelect::create(aimhero1, aimhero2);
	scene->addChild(layer);
	return scene;
}



//overload DoubleMapSelect::create() to accept the information of hero1 and hero2
DoubleMapSelect* DoubleMapSelect::create(char* aimhero1,char* aimhero2)
{
	DoubleMapSelect* pRet = new DoubleMapSelect();
	//save hero1's and hero2's information into a variable
	pRet->hero1 = aimhero1;
	pRet->hero2 = aimhero2;
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



//init map select scene
bool DoubleMapSelect::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();


    //create a button to select map1
	MenuItemImage* mapItem1 = MenuItemImage::create(
		"Map1.png",
		"MapSelect.png",
		CC_CALLBACK_1(DoubleMapSelect::menuMapCallback1, this));
	mapItem1->setPosition(Vec2(695, 565));
	mapItem1->setScale(0.5f);
	Menu* mapMenu1 = Menu::create(mapItem1, NULL);
	mapMenu1->setPosition(Vec2::ZERO);
	this->addChild(mapMenu1, 2);


    //create a button to select map2
	MenuItemImage* mapItem2 = MenuItemImage::create(
		"Map2.png",
		"MapSelect.png",
		CC_CALLBACK_1(DoubleMapSelect::menuMapCallback2, this));
	mapItem2->setPosition(Vec2(1079, 565));
	mapItem2->setScale(0.5f);
	Menu* mapMenu2 = Menu::create(mapItem2, NULL);
	mapMenu2->setPosition(Vec2::ZERO);
	this->addChild(mapMenu2, 2);


    //create a button to select map3
	MenuItemImage* mapItem3 = MenuItemImage::create(
		"Map.png",
		"MapSelect.png",
		CC_CALLBACK_1(DoubleMapSelect::menuMapCallback3, this));
	mapItem3->setPosition(Vec2(695, 251));
	mapItem3->setScale(0.5f);
	Menu* mapMenu3 = Menu::create(mapItem3, NULL);
	mapMenu3->setPosition(Vec2::ZERO);
	this->addChild(mapMenu3, 2);


    //create a button to select map4
	MenuItemImage* mapItem4 = MenuItemImage::create(
		"Map3.png",
		"MapSelect.png",
		CC_CALLBACK_1(DoubleMapSelect::menuMapCallback4, this));
	mapItem4->setPosition(Vec2(1079, 251));
	mapItem4->setScale(0.5f);
	Menu* mapMenu4 = Menu::create(mapItem4, NULL);
	mapMenu4->setPosition(Vec2::ZERO);
	this->addChild(mapMenu4, 2);


    //create a button to make sure your select and go into the next scene
	MenuItemImage* SelectItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(DoubleMapSelect::menuSelectCallBack, this));
	SelectItem->setPosition(Vec2(887, 60));
	SelectItem->setScale(1.8f);
	Menu* selectMenu = Menu::create(SelectItem, NULL);
	selectMenu->setPosition(Vec2::ZERO);
	this->addChild(selectMenu, 2);


    //set the background picture
	auto sprite = Sprite::create("SelectMap.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	return true;
}



//to choose map1
void DoubleMapSelect::menuMapCallback1(cocos2d::Ref* pSender)
{
	map = "map1.tmx";
}



//to choose map2
void DoubleMapSelect::menuMapCallback2(cocos2d::Ref* pSender)
{
	map = "map2.tmx";
}



//to choose map3
void DoubleMapSelect::menuMapCallback3(cocos2d::Ref* pSender)
{
	map = "map.tmx";
}



//to choose map4
void DoubleMapSelect::menuMapCallback4(cocos2d::Ref* pSender)
{
	map = "map3.tmx";//the filename is not the same as "map4"
}



//to make sure your select and change into the next scene
void DoubleMapSelect::menuSelectCallBack(cocos2d::Ref* pSender)
{
	Scene* scene = OffLineDoublePlayer::createScene(map, hero1, hero2);
	Director::getInstance()->replaceScene(scene);
}
