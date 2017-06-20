#include "Help.h"
#include "SimpleAudioEngine.h"
#include "HelloWorld.h"


USING_NS_CC;


//init the scene
Scene* Help::createScene()
{
	return Help::create();
}



//init the help scene
bool Help::init()
{

	if (!Scene::init())
	{
		return false;
	}
	
    //get visible size of the game
	auto visibleSize = Director::getInstance()->getVisibleSize();


    //create a button to go back to the root scene
	MenuItemImage* helpItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(Help::menuSelectCallback, this));
	helpItem->setPosition(Vec2(759, 65));
	helpItem->setScale(1.8f);
	Menu* helpmenu = Menu::create(helpItem, NULL);
	helpmenu->setPosition(Vec2::ZERO);
	this->addChild(helpmenu, 2);

    //set the background picture
	auto sprite = Sprite::create("Help.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	return true;
}



//to go back to the root scene
void Help::menuSelectCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
