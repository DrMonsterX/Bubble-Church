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
	auto sprite = Sprite::create("bg1.png");
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setScale(1.28,0.84);
	sprite->setPosition(Vec2(960/2,640/2));
	addChild(sprite);
	//layout
	/*Layout *ly = Layout::create();
	ly->setBackGroundImage("enter.png");
	ly->setScale(1.5, 1.5);
	ly->setPosition(Vec2(0.5 * 1024, 0.5 * 768));
	addChild(ly);*/
	//four button
	
	//return 
	Button *button1Menu = Button::create("b3.png", "b3.png");
	button1Menu->setPosition(Vec2(239, 369));
	button1Menu->setScale(0.37,0.35);
	button1Menu->addClickEventListener(CC_CALLBACK_1(BaseLayer::menuCheckCallback1, this));
	button1Menu->setPressedActionEnabled(true);
	addChild(button1Menu);
	//setting
	Button *button2Menu = Button::create("button1.png", "button1.png");
	button2Menu->setPosition(Vec2(78, 315));
	log("-----------%d------------------", button2Menu->getScale());
	button2Menu->setScale(0.85,0.81);
	button2Menu->addClickEventListener(CC_CALLBACK_1(BaseLayer::menuCheckCallback2, this));
	button2Menu->setPressedActionEnabled(true);
	addChild(button2Menu);
	//help
	Button *button3Menu = Button::create("b4.png", "b4.png");
	button3Menu->setPosition(Vec2(338, 61));
	button3Menu->setScale(0.54,0.58);
	button3Menu->addClickEventListener(CC_CALLBACK_1(BaseLayer::menuCheckCallback3, this));
	button3Menu->setPressedActionEnabled(true);
	button3Menu->runAction(RotateTo::create(2, 36));
	addChild(button3Menu);
	//continue
	Button *button4Menu = Button::create("b2.png", "b2.png");
	button4Menu->setPosition(Vec2(169,139));
	button4Menu->setScale(0.57,0.56);
	button4Menu->addClickEventListener(CC_CALLBACK_1(BaseLayer::menuCheckCallback4, this));
	button4Menu->setPressedActionEnabled(true);
	addChild(button4Menu);
	auto sp1 = Sprite::create("setting.png");
	sp1->setPosition(Vec2(71, 367));
	sp1->setScale(0.76, 0.86);
	addChild(sp1);
	auto sp12 = Sprite::create("enter1 (2).png");
	sp12->setPosition(Vec2(143, 233));
	sp12->setScale(1, 1);
	addChild(sp12);
	auto sp13 = Sprite::create("help.png");
	sp13->setPosition(Vec2(310, 127));
	sp13->setScale(1, 1);
	addChild(sp13);
	auto sp14 = Sprite::create("exit.png");
	sp14->setPosition(Vec2(230, 433));
	sp14->setScale(1, 1);
	addChild(sp14, 4);
	log("%d  sp", sp14);
	//popul = PopuLayer::create();
	//addChild(popul, 1);


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
