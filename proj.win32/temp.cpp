#include "BaseLayer.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"SettingScene.h"
#include"HelloWorldScene.h"
#include"HelpScene.h"



USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::ui;
Scene *BaseLayer::createScene() {
	auto scene = Scene::create();
	auto layer = BaseLayer::create();
	scene->addChild(layer);
	return scene;
}
bool BaseLayer::init() {
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//return
	auto button = ui::Button::create("play1.png", "play2.png");
	button->setScale(0.5);
	button->setPosition(Vec2(197 * 0.9, 0.1 * 768));
	button->setPressedActionEnabled(true);
	//button->setTitleText("menu");
	button->addClickEventListener(CC_CALLBACK_1(BaseLayer::onButtonClicked, this));
	this->addChild(button);

	//init the background
	AddBackground(visibleSize);

	//init the sprite

	//init the menu
	CreateMenu();
	addButton();
	Layout *ly = Layout::create();
	ly->setBackGroundImage("enter.png");
	ly->setPosition(Vec2(0.5 * 1024, 0.5 * 768));
	addChild(ly);
	//complete slider but not done
	Text *label1 = Text::create("slider", "fonts/Marker Felt.ttf", 24);
	label1->setColor(Color3B(159, 168, 176));
	label1->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	addChild(label1, 0);
	Slider *slider = Slider::create();
	slider->loadBarTexture("slider.png");
	slider->loadSlidBallTextures("slideball.png", "slideball.png", "");
	//slider->loadProgressBarTexture("sliderProgress.png");
	slider->setMaxPercent(1000);
	slider->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	slider->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	slider->addEventListener(CC_CALLBACK_2(BaseLayer::onChangedSlider, this));//remaining
	this->addChild(slider, 0);
	auto label2 = Text::create("0", "fonts/Marker Felt.ttf", 24);
	label2->setPosition(slider->getPosition() - Vec2(0, 60));
	addChild(label2);
	//radiobutton
	RichText *richtext = RichText::create();
	richtext->ignoreContentAdaptWithSize(false);
	richtext->setContentSize(Size(200, 200));

	RadioButtonGroup *radiobuttongroup = RadioButtonGroup::create();
	addChild(radiobuttongroup, 0);
	float startposx = 100;
	int i;
	int num = 5;
	int width = 100;
	for (i = 0; i < num; i++) {
		RadioButton *radiobutton = RadioButton::create("play1.png", "play2.png");
		float posx = startposx + width*i;
		radiobutton->setPosition(Vec2(posx, 300));
		radiobuttongroup->addRadioButton(radiobutton);
		radiobuttongroup->addEventListener(CC_CALLBACK_3(BaseLayer::onChangedRadioButtonGroup, this));
		addChild(radiobutton);
	}
	/*Sprite *temp = Sprite::create("play1.png");
	temp->setPosition(Vec2(500, 500));
	addChild(temp);
	moveby= MoveBy::create(2, Vec2(0, -15));
	temp->runAction(moveby);*/

	Text *checkboxlabel1 = Text::create("checkbox", "fonts/Marker Felt.ttf", 24);
	checkboxlabel1->setColor(Color3B(159, 168, 178));
	checkboxlabel1->setPosition(Vec2(100, 100));
	addChild(checkboxlabel1, 0);

	CheckBox *check = CheckBox::create("play1.png", "play2.png");
	check->setPosition(checkboxlabel1->getPosition() - Vec2(0, 60));
	check->addEventListener(CC_CALLBACK_2(BaseLayer::onChangedCheckBox, this));
	addChild(check);

	Text *checkboxlabel2 = Text::create("checkbox unselected", "fonts/Marker Felt.ttf", 24);
	checkboxlabel2->setPosition(Vec2(check->getPosition() - Vec2(0, 60)));
	addChild(checkboxlabel2);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("E:\temp1\Resources\1.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("E:\temp1\Resources\1.mp3", true);

	//ldbar
	ldbar = LoadingBar::create("");
	ldbar->setPosition(Vec2());
	ldbar->setDirection(LoadingBar::Direction::LEFT);
	addChild(ldbar);

	count = 0;
	this->scheduleUpdate();
	//scrollview
	scrollpng = Sprite::create("enter.png");
	scrollpng->setAnchorPoint(Point(0.5, 0.5));
	Size innersize = scrollpng->getContentSize();

	scroll = ScrollView::create();
	scroll->setInnerContainerSize(Size(1000, 1000));                  //设置滑动框的内容大小  
	scroll->setContentSize(Size(100, 100));
	scroll->setScrollBarEnabled(true);//是否显示滚动条 //设置滑动框的大小  
	scroll->setDirection(ScrollView::Direction::BOTH);          //设置上下左右都可以滑动  
	scroll->setBackGroundImage("play1.png");         //设置背景图片       
	scroll->setBackGroundImageScale9Enabled(true);            //设置layout背景的capInsets,它只在开启scale9后影响背景图的渲染  
	scroll->addChild(scrollpng);                         //添加内容，这里我添加了一个Sprite，也可以是其他的对象，如果想显示丰富的内容可以添加layer  

	scrollpng->setPosition(Vec2(innersize.width / 2, innersize.height / 2));              //布局，把添加的Sprite位置调到中心点  

	scroll->setScrollBarColor(Color3B(255, 0, 0));                  //修改滑块颜色，给滑块添加图片，没有找到API，可能要自己添加  
																	//ScrollViewBar* ScrollviewBar_H = ScrollViewBar::create(scroll, ScrollView::Direction::HORIZONTAL);               //获取滑动框的滑块对象  
	scroll->setPosition(Vec2(700, 100));
	this->addChild(scroll, 1);
	//	auto scroll = cocos2d::ui::ScrollView::create();

	scroll->addEventListener(CC_CALLBACK_2(BaseLayer::scrollCallback, this));//设置监听事件  
																			 //textfield	
	eventDispatcher = Director::getInstance()->getEventDispatcher();
	keylisten = EventListenerKeyboard::create();
	keylisten->onKeyPressed = CC_CALLBACK_2(BaseLayer::onKeyPressed, this);
	keylisten->onKeyReleased = CC_CALLBACK_2(BaseLayer::onKeyReleased, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(keylisten, this);
	keylisten->setEnabled(false);

	textField = TextField::create();
	displaylabel = Text::create("No Event", "Marker Felt.ttf", 32);
	addChild(displaylabel);
	textField->setPosition(Vec2(500, 100));

	textField->addEventListener(CC_CALLBACK_2(BaseLayer::textFieldEvent, this));

	this->addChild(textField, 0);
	/*{
	#include"cocos-ext.h"

	using namespace cocos2d::extension;
	using namespace cocos2d;
	using namespace CocosDenshion;
	using namespace cocos2d::ui;
	auto m_pEditName = cocos2d::extension::CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/green_edit.png"));  m_pEditName->setPosition(ccp(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height * 3 / 4));
	m_pEditName->setFontColor(ccRED);
	m_pEditName->setPlaceHolder("Name:");
	m_pEditName->setMaxLength(8);
	m_pEditName->setReturnType(kKeyboardReturnTypeDone);
	m_pEditName->setDelegate(this);
	addChild(m_pEditName);
	}*/







	return true;
}
void BaseLayer::update(float dt) {
	count++;
	if (count > 100) {
		count = 0;
	}
	ldbar->setPercent(count);

}
/*void BaseLayer::textFieldKeyboardEvent(Ref *pSender, EventKeyboard::KeyCode key) {
switch (key)
{
case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
{
textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
Size screenSize = CCDirector::getInstance()->getWinSize();
//display sent to control
displaylabel->setString("");
}
break;
}
}*/
void BaseLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event * even) {
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		//message sent
		displaylabel->setString("");
		break;
	default:
		break;
	}
}
void BaseLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event * even) {

}
void BaseLayer::textFieldEvent(Ref *pSender, TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		Size screenSize = CCDirector::getInstance()->getWinSize();
		//textField->runAction(CCMoveTo::create(0.225f,Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
		displaylabel->setString(String::createWithFormat("attach with IME max length %d", textField->getMaxLength())->getCString());
		keylisten->setEnabled(true);

	}
	break;

	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		Size screenSize = CCDirector::getInstance()->getWinSize();
		//textField->runAction(CCMoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
		displaylabel->setString(String::createWithFormat("detach with IME max length %d", textField->getMaxLength())->getCString());
		keylisten->setEnabled(false);
	}
	break;

	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		displaylabel->setString(String::createWithFormat("insert words max length %d", textField->getMaxLength())->getCString());
	}
	break;

	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		displaylabel->setString(String::createWithFormat("delete word max length %d", textField->getMaxLength())->getCString());
	}
	break;

	default:
		break;
	}

}
void BaseLayer::scrollCallback(Ref *pSender, ScrollView::EventType type) {
	switch (type)
	{
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_TOP:
		if (scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2) {
			moveby = MoveBy::create(0.1f, Vec2(0, 15));
			scrollpng->runAction(moveby);
		}
		//std::cout << scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2;
		log("%d", scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2);
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
		if (scrollpng->getPosition().y + scrollpng->getContentSize().height / 2 <= scroll->getPosition().y + scroll->getSize().height / 2) {
			moveby = MoveBy::create(0.1f, Vec2(0, -15));
			scrollpng->runAction(moveby);
		}
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_LEFT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_RIGHT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLLING:

		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
		scrollpng->stopAction(moveby);
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
		scrollpng->stopAction(moveby);
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_LEFT:
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_RIGHT:
		break;
	case cocos2d::ui::ScrollView::EventType::CONTAINER_MOVED:
		break;
	case cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED:
		break;
	default:
		break;
	}
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
//loading and save scene
void BaseLayer::menuCheckCallback4(Ref *pSender) {

}
/*void BaseLayer::onEnterTransitionDidFinish() {
Layer::onEnterTransitionDidFinish();
UserDefault *userdefaults = UserDefault::getInstance();
if (userdefaults->getBoolForKey("music_key"))
SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic", true);
}//remaining*/

void BaseLayer::AddBackground(Size visibleSize) {
	auto sprite = Sprite::create("enter.png");
	sprite->setScale(1024 / 500, 768 / 375);
	//position the sprite on the center of the screen
	sprite->setPosition(Vec2(512, 384));
	nodegrid = NodeGrid::create();
	this->addChild(nodegrid);
	// add the sprite as a child to this layer
	nodegrid->addChild(sprite, 0);
	nodegrid->runAction(PageTurn3D::create(3.0f, Size(15, 10)));
}
void BaseLayer::CreateMenu() {
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
	menu->setPosition(Vec2(0.1 * 1024, 0.7 * 768));//remaining
	addChild(menu);
}
//function needed to be disintegrated
void BaseLayer::addButton() {
	auto button = ui::Button::create("1.png", "2.png");

	button->setPosition(Vec2(1024 - 100, 100));
	button->setPressedActionEnabled(true);
	//button->setTitleText("menu");
	button->addClickEventListener(CC_CALLBACK_1(BaseLayer::onButtonClicked, this));
	this->addChild(button);

}
void BaseLayer::onButtonClicked(Ref *pSender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}
void BaseLayer::onChangedSlider(Ref * pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider * slider = dynamic_cast<Slider *>(pSender);
		int percent = slider->getPercent();
		//获取当前滑动的百分比
		//auto label = dynamic_cast<Label *>(getChildByName("label1"));
		//label->setString(String::createWithFormat("Perfecnt %d", percent)->getCString());
		//使用该百分比
	}
}
void BaseLayer::onChangedRadioButtonGroup(RadioButton *radiobutton, int index, RadioButtonGroup::EventType type) {

}
void BaseLayer::onChangedCheckBox(Ref *pSender, CheckBox::EventType type) {
	switch (type) {
	case CheckBox::EventType::SELECTED:
		//auto label2 = dynamic_cast<Text *>(getChildByName("checkboxlabel2"));
		break;
	case CheckBox::EventType::UNSELECTED:
		break;
	default:
		break;
	}
}
BaseLayer::BaseLayer()
{
}


BaseLayer::~BaseLayer()
{
}
