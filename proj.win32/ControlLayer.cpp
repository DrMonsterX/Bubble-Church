#include "ControlLayer.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"GameOver.h"

USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocos2d;
struct direction {
	char up;
	int down;
	int left;
	int right;
}Dire;
Scene* ControlLayer::createScene()
{
	auto scene = Scene::create();
	auto ly = ControlLayer::create();//remianing						   //add the background child
	scene->addChild(ly);
	return scene;
}
bool ControlLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	this->schedule(schedule_selector(ControlLayer::timeupdatebegin), 1.0f);
	this->schedule(schedule_selector(ControlLayer::untimeupdatebegin), 1.0f);
	this->schedule(schedule_selector(ControlLayer::timeupdate), 1.0f);

	return true;
}
void ControlLayer::gameover() {
	if (isover) {
		auto sc = GameOver::createScene();
		Director::getInstance()->replaceScene(sc);
	}

}
void ControlLayer::timeupdatebegin(float) {
	//change time
	begin++;
	if (begin == 5) {
		isbegin = true;
	}
	//allow moving
}
void ControlLayer::timeupdate(float) {
	//change time
	if (isbegin) {
		if (++sec == 60) {
			sec = 0;
			min++;
		}
		if (min == 15) {
			isbegin = false;
			isover = true;
		}
	}
	//ban moving
}
void ControlLayer::untimeupdate(float) {
	if (isover)
		this->unschedule(schedule_selector(ControlLayer::timeupdate));
}
void ControlLayer::untimeupdatebegin(float) {
	if (isbegin)
		this->unschedule(schedule_selector(ControlLayer::timeupdatebegin));
}
void ControlLayer::onEnter() {
	Layer::onEnter();
	/*auto keylisten = EventListenerKeyboard::create();
	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	keylisten->setEnabled(true);
	keylisten->onKeyPressed = CC_CALLBACK_2(ControlLayer::onKeyPressed, this);
	keylisten->onKeyReleased = CC_CALLBACK_2(ControlLayer::onKeyReleased, this);

	auto mouselisten = EventListenerMouse::create();
	mouselisten->setEnabled(true);
	mouselisten->onMouseDown = CC_CALLBACK_1(ControlLayer::MouseDown, this);
	mouselisten->onMouseUp = CC_CALLBACK_1(ControlLayer::MouseUp, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(keylisten, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouselisten, this);
	pMainScene->init();*/
}

/*void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event * even) {
	if ((int)keycode == Dire.up)
		pMainScene->player1->moveUp();
	else if ((int)keycode == Dire.down)
		pMainScene->player1->moveDown();
	else if ((int)keycode == Dire.left)
		pMainScene->player1->moveLeft;
	else if ((int)keycode == Dire.right)
		pMainScene->player1->moveRight();
	else if ((int)keycode == '1')
		pMainScene->myTool1->Use();
	else if ((int)keycode == '2')
		pMainScene->myTool2->Use();
	else if ((int)keycode == '3')
		pMainScene->myTool3->Use();
	else if ((int)keycode == '4')
		pMainScene->myTool4->Use();
	else if ((int)keycode == '5')
		pMainScene->myTool5->Use();
	else if ((int)keycode == '6')
		pMainScene->myTool6->Use();
	else if ((int)keycode == ' ')
		pMainScene->player1->attack();


};
void ControlLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event * even) {
	if ((int)keycode == Dire.up)
		pMainScene->player1->halt();
	else if ((int)keycode == Dire.down)
		pMainScene->player1->halt();
	else if ((int)keycode == Dire.left)
		pMainScene->player1->halt();
	else if ((int)keycode == Dire.right)
		pMainScene->player1->halt();
};
void ControlLayer::MouseDown(Event  *even) {
	//district judge
};
void ControlLayer::MouseUp(Event  *even) {
	//district judge
};
void ControlLayer::MouseMove(Event  *even) {
	//district judge
};*/
bool ControlLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//not determined


	return true;
}
ControlLayer::ControlLayer()
{
}


ControlLayer::~ControlLayer()
{
}