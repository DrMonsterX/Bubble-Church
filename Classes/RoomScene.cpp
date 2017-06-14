#include "RoomScene.h"
#include"HelloWorldScene.h"
//#include"ControlLayer.h"

USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::ui;
Scene* RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool RoomScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("room.png");
	background->setScale(1024 / 800, 768 / 600);
	//background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(Vec2(1024*0.5,768*0.5));
	addChild(background);
	//create sprite
	auto roomrole1= Sprite::create("play1.png");//remaining
	roomrole1->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(roomrole1);
	auto roomrole2 = Sprite::create("play1.png");//remaining
	roomrole2->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(roomrole2);
	auto roomrole3 = Sprite::create("play1.png");//remaining
	roomrole3->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(roomrole3);
	auto roomrole4 = Sprite::create("play1.png");//remaining
	roomrole4->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(roomrole4);

	//exit to helloworld
	Button *Return = Button::create("play1.png", "play2.png");
	Return->setPosition(Vec2(0.9*1024,0.1*768));
	Return->addClickEventListener(CC_CALLBACK_1(RoomScene::ReturnHomeCallback, this));
	Return->setPressedActionEnabled(true);
	addChild(Return);
	//ready button
	Button *start = Button::create("play1.png", "play2.png");
	start->setPosition(Vec2(origin.x + visibleSize.width - Return->getContentSize().width / 2,
		origin.y + Return->getContentSize().height / 2));//remaining
	start->addClickEventListener(CC_CALLBACK_1(RoomScene::StartSceneCallback, this));
	start->setPressedActionEnabled(true);
	addChild(start);
	//auto sc = RoomScene::getScene();

	//checkbox ready
	CheckBox *check = CheckBox::create("play1.png", "play2.png");
	check->setPosition(Vec2(0.8*1024,0.2*768));
	check->addEventListener(CC_CALLBACK_2(RoomScene::onChangedCheckBox, this));
	addChild(check);



	return true;
}
void RoomScene::ReturnHomeCallback(Ref *pSender) {
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}
void RoomScene::StartSceneCallback(Ref *pSender) {
	/*if (playerNum >= 2) {
		auto sc = ControlLayer::createScene();
		Director::getInstance()->replaceScene(sc);
	}
	else {

	}*/
}
void RoomScene::onChangedCheckBox(Ref *pSender, CheckBox::EventType type) {
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		myready = true;
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		myready = true;
		break;
	default:
		break;
	}
}



RoomScene::RoomScene()
{
}


RoomScene::~RoomScene()
{
}
