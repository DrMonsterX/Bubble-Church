#include "PopuLayer.h"
#include"Chatter.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocos2d::ui;
bool Chatter::init() {
	if (!Layer::init())
	{
		return false;
	}
	
	
	auto background = Sprite::create("enter.png");
	background->setScale(300 / background->getContentSize().width, 150 / background->getContentSize().height);
	background->setPosition(Vec2(1024 * 0.5, 768 * 0.5));
	addChild(background);//opacity background layer
	Button* buttonyes = Button::create("play1.png", "play2.png");
	buttonyes->setPosition(Vec2(0.4 * 1024, 0.5 * 768));//remaining
	buttonyes->addClickEventListener(CC_CALLBACK_1(Chatter::ButtonCallback1, this));
	addChild(buttonyes);
	Button* buttonno = Button::create("play1.png", "play2.png");
	buttonno->setPosition(Vec2(0.6 * 1024, 0.5 * 768));//remaining
	buttonno->addClickEventListener(CC_CALLBACK_1(Chatter::ButtonCallback2, this));
	addChild(buttonno);
	//textfield
	textField = TextField::create();
	displaylabel = Text::create("No Event", "Marker Felt.ttf", 32);
	addChild(displaylabel);
	textField->setPosition(Vec2(500, 100));

	textField->addEventListener(CC_CALLBACK_2(Chatter::textFieldEvent, this));

	this->addChild(textField, 0);

	eventDispatcher = Director::getInstance()->getEventDispatcher();
	keylisten = EventListenerKeyboard::create();
	keylisten->onKeyPressed = CC_CALLBACK_2(Chatter::onKeyPressed, this);
	keylisten->onKeyReleased = CC_CALLBACK_2(Chatter::onKeyReleased, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(keylisten, this);
	keylisten->setEnabled(false);

	return true;
}
void Chatter::onKeyPressed(EventKeyboard::KeyCode keycode, Event * even) {
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		temp = textField;
		textField = TextField::create();
		textField->setPosition(Vec2(500, 100));

		textField->addEventListener(CC_CALLBACK_2(Chatter::textFieldEvent, this));
		temp->removeFromParent();
		this->addChild(textField, 0);
		textField->attachWithIME();
		break;
	}
}
void Chatter::onKeyReleased(EventKeyboard::KeyCode keycode, Event * even) {}
void Chatter::textFieldEvent(Ref *pSender, TextField::EventType type) {
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		keylisten->setEnabled(true);
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		keylisten->setEnabled(true);
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		keylisten->setEnabled(true);
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		keylisten->setEnabled(true);
		break;
	default:
		break;
	}
}
void Chatter::ButtonCallback1(Ref *pSender) {
	
}
void Chatter::ButtonCallback2(Ref *pSender) {

}
Chatter::Chatter()
{
}

Chatter::~Chatter()
{
}