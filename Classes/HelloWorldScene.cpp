#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"SettingScene.h"
#include"HelpScene.h"
#include"RoomScene.h"
#include"LoadingScene.h"
#include"Chatter.h"
//#include"LoginScene.h"


USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("enter.png");
	sprite->setScale(1024 / 500, 768 / 375);
	//position the sprite on the center of the screen
	sprite->setPosition(Vec2(512, 384));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "kongjian1.png",
                                           "kongjian2.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(menu, 1);
	//setting
	auto button = ui::Button::create("fsetting.png", "fsetting.png");
	button->setPosition(Vec2(0.5*1024,0.6*768-50));
	button->setPressedActionEnabled(true);
	button->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClicked, this));
	this->addChild(button);
	
	//quit
	auto button2 = ui::Button::create("fexit.png", "fexit.png");
	button2->setPosition(Vec2(0.5 * 1024, 0.5 * 768-50));
	button2->setPressedActionEnabled(true);
	button2->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClicked2, this));
	this->addChild(button2);
	//help
	auto button3 = ui::Button::create("fhelp.png", "fhelp.png");
	button3->setPosition(Vec2(0.5 * 1024, 0.4 * 768-50));
	button3->setPressedActionEnabled(true);
	button3->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClicked3, this));
	this->addChild(button3,0);
	//enter
	auto button4 = ui::Button::create("fenter.png", "fenter.png");
	button4->setPosition(Vec2(0.5 * 1024, 0.3 * 768-50));
	button4->setPressedActionEnabled(true);
	button4->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClicked4, this));
	this->addChild(button4, 0);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_scene_bg.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game_scene_bg.mp3",true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	/*DataBase pDB(-1);
	log("-------------------%d-----------------",SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying());
	log("%d------", pDB.OpenDBWithFileName("E:\temp1\sqlite\temp.db"));
	log("%d------", pDB.CreateTableWithContent("create table users"));
	pDB.InsertTableDataWithContent(string("insert into users (num,role,level) values('1','player1','1')"));
	log("%d------", pDB.GetTableDataWithContent(string("select num from users where num=1")));
	log("%d------", pDB.DeleteTableDataWithContent(string("delete from users where num=1")));
	pDB.CloseDB();*/
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("pao pao tang", "fonts/Marker Felt.ttf", 124);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label);

    
    
    return true;
}
void HelloWorld::onButtonClicked(Ref *pSender)
{
	//auto ld = LoadingScene::create();
	//auto sc = Director::getInstance()->getRunningScene();
	//sc->addChild(ld);
	auto sc2 = Setting::createScene();
	//ld->removeFromParent();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->replaceScene(sc2);
}

void HelloWorld::onButtonClicked3(Ref *pSender)
{
	//auto ly = Chatter::create();
	//Director::getInstance()->getRunningScene()->addChild(ly);
	/*auto sc = Help::createScene();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->replaceScene(sc);*/

	auto sc = Help::createScene();
	Director::getInstance()->replaceScene(sc);
}
void HelloWorld::onButtonClicked2(Ref *pSender)
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->end();
}
void HelloWorld::onButtonClicked4(Ref *pSender)
{
	auto sc = RoomScene::createScene();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->replaceScene(sc);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
