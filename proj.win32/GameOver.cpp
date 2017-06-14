#include "GameOver.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"Settingscene.h"
#include"RoomScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;
Scene* GameOver::createScene()
{
	return GameOver::create();
}

bool GameOver::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//not determined
															  //create scorepad sprite



	return true;
}
void GameOver::closeButtonClicked(Ref *pSender) {
	auto sc = RoomScene::createScene();
	Director::getInstance()->replaceScene(sc);
}
GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}
