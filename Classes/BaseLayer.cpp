#include "BaseLayer.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"SettingScene.h"
#include"HelloWorldScene.h"
#include"HelpScene.h"
#include"RoomScene.h"



USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::ui;
Scene *BaseLayer::createScene() {
	auto psc = Scene::create();
	auto layer = BaseLayer::create();
	psc->addChild(layer);
	return psc;
}
bool BaseLayer::init() {
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//background
	auto sprite = Sprite::create("enter.png");
	sprite->setScale(1024 / 500, 768 / 375);
	sprite->setPosition(Vec2(512, 384));
	addChild(sprite);
	//layout
	Layout *ly = Layout::create();
	ly->setBackGroundImage("enter.png");
	ly->setScale(1.5, 1.5);
	ly->setPosition(Vec2(0.5 * 1024, 0.5 * 768));
	addChild(ly);
	//four button
	auto button1MenuNormal = Sprite::create("play1.png");
	auto button1MenuSelected = Sprite::create("play2.png");
	auto button2MenuNormal = Sprite::create("play1.png");
	auto button2MenuSelected = Sprite::create("play2.png");
	auto button3MenuNormal = Sprite::create("play1.png");
	auto button3MenuSelected = Sprite::create("play2.png");
	auto button4MenuNormal = Sprite::create("play1.png");
	auto button4MenuSelected = Sprite::create("play2.png");
	//return 
	auto checkMenu1 = MenuItemSprite::create(button1MenuNormal, button1MenuSelected, CC_CALLBACK_1(BaseLayer::menuCheckCallback1, this));
	//setting
	auto checkMenu2 = MenuItemSprite::create(button2MenuNormal, button2MenuSelected, CC_CALLBACK_1(BaseLayer::menuCheckCallback2, this));
	//help
	auto checkMenu3 = MenuItemSprite::create(button3MenuNormal, button3MenuSelected, CC_CALLBACK_1(BaseLayer::menuCheckCallback3, this));
	//continue
	auto checkMenu4 = MenuItemSprite::create(button4MenuNormal, button4MenuSelected, CC_CALLBACK_1(BaseLayer::menuCheckCallback4, this));
	auto menu = Menu::create(checkMenu1, checkMenu2, checkMenu3, checkMenu4, NULL);//remaining
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->setScale(0.9, 0.9);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(0.1 * 1024, 0.5 * 768));//remaining
	addChild(menu);
	popul = PopuLayer::create();
	addChild(popul, 1);


	return true;
}
//return
void BaseLayer::menuCheckCallback1(Ref *pSender) {
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
	//if (UserDefault::getInstance()->getBoolForKey("sound_key"))
	//SimpleAudioEngine::getInstance()->playEffect("sound");//remaining
}
//setting scene
void BaseLayer::menuCheckCallback2(Ref *pSender) {
	auto sc = Setting::createScene();
	Director::getInstance()->replaceScene(sc);
	//if (UserDefault::getInstance()->getBoolForKey("sound_key"))
	//SimpleAudioEngine::getInstance()->playEffect("sound");//remaining
}
//help scene
void BaseLayer::menuCheckCallback3(Ref *pSender) {
	auto sc = Help::createScene();
	Director::getInstance()->replaceScene(sc);
	//if (UserDefault::getInstance()->getBoolForKey("sound_key"))
	//SimpleAudioEngine::getInstance()->playEffect("sound");//remaining
}
//enter
void BaseLayer::menuCheckCallback4(Ref *pSender) {
	auto sc= RoomScene::createScene();
	Director::getInstance()->replaceScene(sc);
}
BaseLayer::BaseLayer()
{
}


BaseLayer::~BaseLayer()
{
}
