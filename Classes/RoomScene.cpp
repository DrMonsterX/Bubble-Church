#include "RoomScene.h"
#include"HelloWorldScene.h"
#include"OffLineDoublePlayer.h"
#include"ControlLayer.h"
#include"Chatter.h"

#include"vector"
#include"utility"


USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace std;
vector<string> strvec;
Scene* RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RoomScene::create();
	scene->addChild(layer,0,1111);
	//log("-----,------%d--------", Director::getInstance()->getRunningScene()->getChildByTag(1111));
	return scene;
}
message *pppm;
bool RoomScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("GameScene.png");
	background->setScale(1.25,1.03);
	//background->setAnchorPoint(Point(0.5, 0.5));
	background->setPosition(Vec2(481,315));
	addChild(background,0,1010);
	//auto ttt = dynamic_cast <Sprite *>(this->getChildByTag(1010));
	//log("ttt---------------%d-----------", ttt);
	//create sprite
	/*
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
	addChild(roomrole4);*/


	//exit to helloworld
	Button *Return = Button::create("exit.png", "exit.png");
	Return->setPosition(Vec2(849, 64.8));
	Return->setScale(0.342, 0.441);
	Return->addClickEventListener(CC_CALLBACK_1(RoomScene::ReturnHomeCallback, this));
	Return->setPressedActionEnabled(true);
	addChild(Return);
	//ready button
	//personvec.clear();
	//mapvec.clear();
	//enter temp
	enter = Button::create("enter1.png", "enter1.png");
	enter->setPosition(Vec2(129,69));//remaining
	enter->setScale(0.423,0.434);
	enter->addClickEventListener(CC_CALLBACK_1(RoomScene::EnterSceneCallback, this));
	enter->setPressedActionEnabled(false);
	enter->setEnabled(false);
	addChild(enter);
	//auto sc = RoomScene::getScene();
	player1select= Button::create("b2b.png", "b2b.png", "b2b.png");
	player1select->setPosition(Vec2(85.9, 530));//remaining
	player1select->setScale(0.143, 0.139);
	player1select->addClickEventListener(CC_CALLBACK_1(RoomScene::SelectCallback1, this));
	player1select->setEnabled(true);
	player1select->setTag(10);
	addChild(player1select);
	player1determ = Button::create("b2b.png", "b2b.png","b2b.png");
	player1determ->setPosition(Vec2(85.9, 278));//remaining
	player1determ->setScale(0.143, 0.139);
	player1determ->addClickEventListener(CC_CALLBACK_1(RoomScene::DetermCallback1, this));
	player1determ->setEnabled(false);
	player1select->setTag(11);
	addChild(player1determ);
	strvec.clear();
	player2select= Button::create("b3b.png", "b3b.png", "b3b.png");
	player2select->setPosition(Vec2(867, 533));//remaining
	player2select->setScale(0.158, 0.146);
	player2select->addClickEventListener(CC_CALLBACK_1(RoomScene::SelectCallback2, this));
	player2select->setEnabled(false);
	player2select->setTag(20);
	addChild(player2select);
	player2determ = Button::create("b3b.png", "b3b.png","b3b.png");
	player2determ->setPosition(Vec2(877, 291));//remaining
	player2determ->setScale(0.158, 0.146);
	player2determ->addClickEventListener(CC_CALLBACK_1(RoomScene::DetermCallback2, this));
	player2determ->setEnabled(false);
	player2select->setTag(21);
	addChild(player2determ);
	//chatter
	Button *chat = Button::create("exit.png", "exit.png");
	chat->setPosition(Vec2(849, 64.8));
	chat->setScale(0.342, 0.441);
	chat->addClickEventListener(CC_CALLBACK_1(RoomScene::ChatterCallback, this));
	chat->setPressedActionEnabled(true);
	addChild(chat);

	auto sp1 = Sprite::create("player1select.png");
	sp1->setPosition(Vec2(94, 477));
	sp1->setScale(0.48, 0.58);
	addChild(sp1);
	auto sp12 = Sprite::create("player2select.png");
	sp12->setPosition(Vec2(872, 479));
	sp12->setScale(0.42,0.58);
	addChild(sp12);
	auto sp13 = Sprite::create("player1determ.png");
	sp13->setPosition(Vec2(91, 188));
	sp13->setScale(0.47, 0.67);
	addChild(sp13);
	auto sp14 = Sprite::create("player2determ.png");
	sp14->setPosition(Vec2(906-20, 189));
	sp14->setScale(0.40, 0.77);
	addChild(sp14, 4);
	log("%d  sp", sp14);
	//checkbox ready
	/*CheckBox *check = CheckBox::create("play1.png", "play2.png");
	check->setPosition(Vec2(849,64.8));
	check->addEventListener(CC_CALLBACK_2(RoomScene::onChangedCheckBox, this));
	addChild(check);*/


	radiobuttongroupmap = RadioButtonGroup::create();
	radiobuttongroupmap->setTag(200);
	addChild(radiobuttongroupmap);
	float startposx = 326;
	int i;
	int num = 3;
	int width = 100;
	RadioButton *radiobutton1 = RadioButton::create("enter.png", "enter.png");
	float posx = startposx + width * 0;
	radiobutton1->setPosition(Vec2(335, 500));
	radiobutton1->setScale(0.54, 0.57);
	radiobuttongroupmap->addRadioButton(radiobutton1);
	radiobuttongroupmap->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroupmap, this));
	addChild(radiobutton1);

	radiobutton3 = RadioButton::create("enter.png", "enter.png");
	posx = startposx + width * 2;
	radiobutton3->setPosition(Vec2(609,498));
	radiobutton1->setScale(0.54, 0.57);
	radiobuttongroupmap->addRadioButton(radiobutton3);
	radiobuttongroupmap->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroupmap, this));
	addChild(radiobutton3);

	radiobutton2 = RadioButton::create("enter.png", "enter.png");
	posx = startposx + width * 1;
	radiobutton2->setPosition(Vec2(334,279));
	radiobutton1->setScale(0.54, 0.57);
	radiobuttongroupmap->addRadioButton(radiobutton2);
	radiobuttongroupmap->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroupmap, this));
	addChild(radiobutton2);

	radiobutton4 = RadioButton::create("enter.png", "enter.png");
	posx = startposx + width * 2;
	radiobutton4->setPosition(Vec2(608,284));
	radiobutton1->setScale(0.54, 0.57);
	radiobuttongroupmap->addRadioButton(radiobutton4);
	radiobuttongroupmap->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroupmap, this));
	addChild(radiobutton4);
	RoomScene();
	//auto ly = dynamic_cast<Layer *> (Director::getInstance()->getRunningScene()->getChildByTag(1111));
	//log("-------%d-------------%d-----%d----", ly, player1determ, Director::getInstance()->getRunningScene()->getChildByTag(1111),this);
	return true;
}
void RoomScene::DetermCallback1(Ref *pSender) {
	//auto radiobutton = this->radiobuttongroup;
	//log("-------------%d-------------",radiobuttongroup);
	radiobuttongroup->runAction(RemoveSelf::create(true));
	tradiobutton1->removeFromParent();
	tradiobutton2->removeFromParent();
	tradiobutton3->removeFromParent();
	//auto button1 = player1select;
	player1select->setEnabled(false);
	//auto button2 = player1determ;
	player1determ->setEnabled(false);
	//auto button3 = player2select;
	player2select->setEnabled(true);
	//auto button4 = player2determ;
	player2determ->setEnabled(true);
}
void RoomScene::DetermCallback2(Ref *pSender) {
	//auto radiobutton = this->radiobuttongroup;
	log("-------------valid-------------");
	radiobuttongroup->runAction(RemoveSelf::create(true));
	tradiobutton1->removeFromParent();
	tradiobutton2->removeFromParent();
	tradiobutton3->removeFromParent();
	//auto button3 = player2select;
	player2select->setEnabled(false);
	//auto button4 = player2determ;
	player2determ->setEnabled(false);
}
void RoomScene::SelectCallback1(Ref *pSender){
	/*Button *role1 = Button::create("ssxstand41.png", "ssxstand41.png");
	role1->addClickEventListener(CC_CALLBACK_1(RoomScene::roleSelectedCallback2, this));
	role1->setPosition(Vec2(45, 68.8));
	role1->setPressedActionEnabled(true);
	addChild(role1);
	auto role2 = Sprite::create("zystand41.png");
	role2->setPosition(Vec2(326, 64.77));
	auto role2 = Sprite::create("zystand41.png");
	role2->setPosition(Vec2(568,67.77));*/

	radiobuttongroup = RadioButtonGroup::create();
	radiobuttongroup->setTag(000);
	addChild(radiobuttongroup);
	float startposx = 326;
	int i;
	int num = 3;
	int width = 100;
		tradiobutton1 = RadioButton::create("zystand41.png", "zystand41.png");
		float posx = startposx + width*0;
		tradiobutton1->setPosition(Vec2(posx, 64));
		radiobuttongroup->addRadioButton(tradiobutton1);
		radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup1, this));
		addChild(tradiobutton1);
		tradiobutton3 = RadioButton::create("zystand41.png", "zystand41.png");
		posx = startposx + width * 2;
		tradiobutton3->setPosition(Vec2(posx, 64));
		radiobuttongroup->addRadioButton(tradiobutton3);
		radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup1, this));
		addChild(tradiobutton3);

		tradiobutton2= RadioButton::create("zystand41.png", "zystand41.png");
		posx = startposx + width * 1;
		tradiobutton2->setPosition(Vec2(posx, 64));
		radiobuttongroup->addRadioButton(tradiobutton2);
		radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup1, this));
		addChild(tradiobutton2);
		
}
void RoomScene::SelectCallback2(Ref *pSender) {
	/*Button *role1 = Button::create("ssxstand41.png", "ssxstand41.png");
	role1->addClickEventListener(CC_CALLBACK_1(RoomScene::roleSelectedCallback2, this));
	role1->setPosition(Vec2(45, 68.8));
	role1->setPressedActionEnabled(true);
	addChild(role1);
	auto role2 = Sprite::create("zystand41.png");
	role2->setPosition(Vec2(326, 64.77));
	auto role2 = Sprite::create("zystand41.png");
	role2->setPosition(Vec2(568,67.77));*/

	radiobuttongroup = RadioButtonGroup::create();
	radiobuttongroup->setTag(000);
	addChild(radiobuttongroup);
	float startposx = 326;
	int i;
	int num = 3;
	int width = 100;
	tradiobutton1 = RadioButton::create("ssxstand41.png", "ssxstand41.png");
	float posx = startposx + width * 0;
	tradiobutton1->setPosition(Vec2(posx, 64));
	radiobuttongroup->addRadioButton(tradiobutton1);
	radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup2, this));
	addChild(tradiobutton1);

	tradiobutton3 = RadioButton::create("ssxstand41.png", "ssxstand41.png");
	posx = startposx + width * 2;
	tradiobutton3->setPosition(Vec2(posx, 64));
	radiobuttongroup->addRadioButton(tradiobutton3);
	radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup2, this));
	addChild(tradiobutton3);

	tradiobutton2 = RadioButton::create("ssxstand41.png", "ssxstand41.png");
	posx = startposx + width * 1;
	tradiobutton2->setPosition(Vec2(posx, 64));
	radiobuttongroup->addRadioButton(tradiobutton2);
	radiobuttongroup->addEventListener(CC_CALLBACK_3(RoomScene::onChangedRadioButtonGroup2, this));
	addChild(tradiobutton2);
	

}

void RoomScene::onChangedRadioButtonGroup1(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type) {
	switch (type)
	{
	case cocos2d::ui::RadioButtonGroup::EventType::SELECT_CHANGED:
		if (index == 0) {
			if (strvec.size() == 0)
				strvec.push_back(string("zy"));
			else
				strvec.at(0) = string("zy");
		}
		if (index == 2) {
			if (strvec.size() == 0)
				strvec.push_back(string("zy"));
			else
				strvec.at(0) = string("zy");
		}
		if (index == 3) {

			if (strvec.size() == 0)
				strvec.push_back(string("zy"));
			else
				strvec.at(0) = string("zy");
		}
		log("%d size", strvec.size());
		if (strvec.size() == 1) {
			player1determ->setEnabled(true);
			player1select->setEnabled(false);
		}
		break;
	default:
		break;
	}
}
void RoomScene::onChangedRadioButtonGroup2(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type) {
	switch (type)
	{
	case cocos2d::ui::RadioButtonGroup::EventType::SELECT_CHANGED:
		if (index == 0) {
			if (strvec.size() == 1)
				strvec.push_back(string("ssx"));
			else
				strvec.at(1) = string("ssx");
		}
		if (index == 2) {
			if (strvec.size() == 1)
				strvec.push_back(string("ssx"));
			else
				strvec.at(1) = string("ssx");
		}
		if (index == 3) {
			if (strvec.size() == 1)
				strvec.push_back(string("ssx"));
			else
				strvec.at(1) = string("ssx");
		}
		if (strvec.size() == 2) {
			player2determ->setEnabled(true);
			player2select->setEnabled(false);
		}
		log("%d size", strvec.size());
		break;
	default:
		break;
	}
}
void RoomScene::onChangedRadioButtonGroupmap(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type) {
	switch (type)
	{
	case cocos2d::ui::RadioButtonGroup::EventType::SELECT_CHANGED:
		if (index == 0) {
			if (strvec.size() == 2)
				strvec.push_back(string("map1.tmx"));
			else
			strvec.at(2) = string("map1.tmx");
		}
		if (index == 2) {
			if (strvec.size() == 2)
				strvec.push_back(string("map1.tmx"));
			else
				strvec.at(2) = string("map1.tmx");
		}
		if (index == 3) {
			if (strvec.size() == 2)
				strvec.push_back(string("map1.tmx"));
			else
				strvec.at(2) = string("map1.tmx");
		}
		if (strvec.size() == 3) {
			enter->setEnabled(true);
		}
		log("%d size", strvec.size());
		break;
	default:
		break;
	}
}
void RoomScene::ReturnHomeCallback(Ref *pSender) {
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}
void RoomScene::ChatterCallback(Ref *pSender) {
	auto sc = Chatter::createScene();
	Director::getInstance()->pushScene(sc);
}
void RoomScene::EnterSceneCallback(Ref *pSender) {
	auto sc = ControlLayer::createScene();
	Director::getInstance()->replaceScene(sc);//remaining
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
