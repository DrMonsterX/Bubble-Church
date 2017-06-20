#include "Setting.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


//init setting scene 
Scene* Setting::createScene()
{
	return Setting::create();
}



//init setting scene
bool Setting::init()
{

	if (!Scene::init())
	{
		return false;
	}

    //get visible size of the game
	auto visibleSize = Director::getInstance()->getVisibleSize();


    //create a button to play the background music
	MenuItemImage* openItem = MenuItemImage::create(
		"OpenNormal.png",
		"OpenSelect.png",
		CC_CALLBACK_1(Setting::menuMusicStartCallback, this));
	openItem->setPosition(Vec2(226, 435));
	openItem->setScale(1.3f);
	Menu* openMenu = Menu::create(openItem, NULL);
	openMenu->setPosition(Vec2::ZERO);
	this->addChild(openMenu, 2);


	//create a button to stop the background music
	MenuItemImage* closeItem = MenuItemImage::create(
		"CloseMNormal.png",
		"CloseMSelect.png",
		CC_CALLBACK_1(Setting::menuMusicCloseCallback, this));
	closeItem->setPosition(Vec2(384, 435));
	closeItem->setScale(1.3f);
	Menu* closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 2);


    //create a button to make sure your select and go back to the root scene
	auto backItem = MenuItemImage::create(
		"SelectNormal.png",
		"SelectSelect.png",
		CC_CALLBACK_1(Setting::menuBackCallback, this));
	backItem->setPosition(Vec2(120, 45));
	backItem->setScale(2);
	auto backMenu = Menu::create(backItem, NULL);
	backMenu->setPosition(Vec2::ZERO);
	this->addChild(backMenu, 1);


    //set the background picture
	auto sprite = Sprite::create("Setting.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	return true;
}



//to play the background music
void Setting::menuMusicStartCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
}



//to stop the background music
void Setting::menuMusicCloseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}



//to make sure your select and go back to the root scene
void Setting::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
