#include "PopuLayer.h"

#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocos2d::ui;

bool PopuLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	/*if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100))) {
		return false;
	}*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		CCLOG("touch menu");
		return true;
	};
	listener->onTouchMoved = [](Touch* touch, Event* event) {
	};
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	listener->onTouchEnded = [=](Touch* touch, Event* event) {
	};
	eventDispatcher1 = Director::getInstance()->getEventDispatcher();
	eventDispatcher1->addEventListenerWithSceneGraphPriority(listener, this);
	listener->setEnabled(true);
	auto background = Sprite::create("enter.png");
	background->setScale(300 / background->getContentSize().width, 150 / background->getContentSize().height);
	background->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(background);//opacity background layer
	Button* buttonyes = Button::create("play1.png", "play2.png");
	buttonyes->setPosition(Vec2(0.4*1024,0.5*768));//remaining
	buttonyes->addClickEventListener(CC_CALLBACK_1(PopuLayer::ButtonCallback1, this));
	addChild(buttonyes);
	Button* buttonno = Button::create("play1.png", "play2.png");
	buttonno->setPosition(Vec2(0.6*1024,0.5*768));//remaining
	buttonno->addClickEventListener(CC_CALLBACK_1(PopuLayer::ButtonCallback2, this));
	addChild(buttonno);
	

	return true;
}
void PopuLayer::ButtonCallback1(Ref *pSender) {
	PopuLayer::Layer::cleanup();
}
void PopuLayer::ButtonCallback2(Ref *pSender) {

}
PopuLayer::PopuLayer()
{
}

PopuLayer::~PopuLayer()
{
}
