#include "Settingscene.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *Setting::createScene() {
	auto sc = BaseLayer::createScene();
	auto ly = Setting::create();
	sc->addChild(ly);
	return sc;
}
bool Setting::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//music
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_scene_bg.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game_scene_bg.mp3", true);
	//text bmp
	auto header = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 124);

	// position the label on the center of the screen
	header->setPosition(Vec2(273,547));

	// add the label as a child to this layer
	this->addChild(header);
	//slider1
	Label *label1 = Label::createWithTTF("music", "fonts/Marker Felt.ttf", 24);
	label1->setColor(Color3B(159, 168, 176));
	label1->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	addChild(label1);
	/*Slider *slider1 = Slider::create();
	slider1->loadBarTexture("slider.png");
	slider1->setScale(0.5, 0.5);
	slider1->loadSlidBallTextures("slideball.png", "slideball.png", "");
	//slider->loadProgressBarTexture("sliderProgress.png");
	slider1->setMaxPercent(100);
	slider1->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	slider1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	slider1->addEventListener(CC_CALLBACK_2(Setting::onChangedSlider1, this));//remaining
	this->addChild(slider1);
	//slider2

	
	Label *label2 = Label::createWithTTF("effect", "fonts/Marker Felt.ttf", 24);
	label2->setColor(Color3B(159, 168, 176));
	label2->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	addChild(label2);*/
	/*Slider *slider2= Slider::create();
	slider2->loadBarTexture("slider.png");
	slider2->setScale(0.5, 0.5);
	slider2->loadSlidBallTextures("slideball.png", "slideball.png", "");
	//slider->loadProgressBarTexture("sliderProgress.png");
	slider2->setMaxPercent(1000);
	slider2->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	slider2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));
	slider2->addEventListener(CC_CALLBACK_2(Setting::onChangedSlider2, this));//remaining
	this->addChild(slider2);*/
	//checkbox complete
	Label *checkboxlabel1 = Label::createWithTTF("music", "fonts/Marker Felt.ttf", 24);
	checkboxlabel1->setColor(Color3B(255, 255, 255));
	checkboxlabel1->setScale(2.27, 2.83);
	checkboxlabel1->setPosition(Vec2(422,427));
	addChild(checkboxlabel1, 0);
	CheckBox *check1 = CheckBox::create("check1.png", "check2.png");
	check1->setScale(0.4,0.38);
	check1->setPosition(Vec2(653,440));
	check1->addEventListener(CC_CALLBACK_2(Setting::onChangedCheckBox1, this));
	addChild(check1);

	Label *checkboxlabel2 = Label::createWithTTF("effect", "fonts/Marker Felt.ttf", 24);
	checkboxlabel2->setColor(Color3B(255, 255, 255));
	checkboxlabel2->setScale(2.25, 3.4);
	checkboxlabel2->setPosition(Vec2(411, 322));
	addChild(checkboxlabel2, 0);
	CheckBox *check2 = CheckBox::create("check1.png", "check2.png");
	check2->setScale(0.4, 0.38);
	check2->setPosition(Vec2(653,335));
	check2->addEventListener(CC_CALLBACK_2(Setting::onChangedCheckBox1, this));
	addChild(check2);

	
	/*auto label2 = Text::create("0", "fonts/Marker Felt.ttf", 24);
	label2->setPosition(slider->getPosition() - Vec2(0, 60));
	addChild(label2,3);*/
	/*auto background = Sprite::create("play1.png");
	background->setScale(1024 / 500, 768 / 375);
	background->setPosition(Vec2(512, 384));
	addChild(background);*/
	//txt
	/*auto txt = Label::createWithBMFont("fonts / BMFont.fnt", "Setting");//remaining
	txt->setColor(Color3B(14, 83, 204));//color
										//txt->setPosition(95, background->getPosition().y - 70);//position
										//txt->setAnchorPoint(Vec2(0, 0));
	txt->setPosition(Vec2(1024 * 0.1, 768 * 0.1));
	addChild(txt, 1);
	auto label = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 124);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label);*/

	/*//sound
	auto SoundOn = Sprite::create("check1.png");
	auto SoundOff = Sprite::create("check2.png");
	auto SoundOnMenu = MenuItemSprite::create(SoundOn, NULL);
	auto SoundOffMenu = MenuItemSprite::create(SoundOff, NULL);
	auto SoundToggleMenu = MenuItemToggle::createWithCallback(
	CC_CALLBACK_1(Setting::menuSoundCallback, this),
	SoundOnMenu, SoundOffMenu, NULL);
	//music
	auto MusicOn = Sprite::create("check1.png");
	auto MusicOff = Sprite::create("check1.png");
	auto MusicOnMenu = MenuItemSprite::create(MusicOn, NULL);
	auto MusicOffMenu = MenuItemSprite::create(MusicOff, NULL);
	auto MusicToggleMenu = MenuItemToggle::createWithCallback(
	CC_CALLBACK_1(Setting::menuMusicCallback, this),
	MusicOnMenu, MusicOffMenu, NULL);

	auto menu = Menu::create(SoundToggleMenu, MusicToggleMenu, NULL);
	//menu position remaining
	menu->alignItemsHorizontally();
	menu->setPosition(Vec2(200, 200));
	addChild(menu);*/
	/*//sound label
	auto LabelSound = Label::createWithBMFont("fonts/BMFont.fnt", "sound");
	LabelSound->setPosition(Vec2());//remaining
	addChild(LabelSound, 1);
	auto LabelMusic = Label::createWithBMFont("fonts/BMFont.fnt", "music");
	LabelMusic->setPosition(Vec2());//remaining
	addChild(LabelMusic, 1);
	//userdefault remaining
	UserDefault *userdefault = UserDefault::getInstance();*/

	//soundslider
	/*Text *soundlabel1 = Text::create("slider", "fonts/Marker Felt.ttf", 24);
	soundlabel1->setColor(Color3B(159, 168, 176));
	soundlabel1->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	addChild(soundlabel1, 0);
	Slider *soundslider = Slider::create();
	soundslider->loadBarTexture("sliderTrack.png");
	soundslider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	soundslider->loadProgressBarTexture("sliderProgress.png");
	soundslider->setMaxPercent(1000);
	soundslider->setPosition(Vec2(0.5 * 1024, 0.3 * 768));
	soundslider->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	soundslider->addEventListener(CC_CALLBACK_2(Setting::onChangedSlider1, this));//remaining
	this->addChild(soundslider);
	auto soundlabel2 = Text::create("0", "fonts/Marker Felt.ttf", 24);
	soundlabel2->setPosition(soundslider->getPosition() - Vec2(0, 60));
	addChild(soundlabel2);
	
	//musicslider
	Text *musiclabel1 = Text::create("slider", "fonts/Marker Felt.ttf", 24);
	musiclabel1->setColor(Color3B(159, 168, 176));
	musiclabel1->setPosition(Vec2(0.5 * 1024, 0.1 * 768));
	addChild(musiclabel1, 0);
	Slider *musicslider = Slider::create();
	musicslider->loadBarTexture("sliderTrack.png");
	musicslider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	musicslider->loadProgressBarTexture("sliderProgress.png");
	musicslider->setMaxPercent(1000);
	musicslider->setPosition(Vec2(0.5 * 1024, 0.3 * 768));
	musicslider->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
	musicslider->addEventListener(CC_CALLBACK_2(Setting::onChangedSlider2, this));//remaining
	this->addChild(musicslider);
	auto musiclabel2 = Text::create("0", "fonts/Marker Felt.ttf", 24);
	musiclabel2->setPosition(musicslider->getPosition() - Vec2(0, 60));
	addChild(musiclabel2);*/




	return true;
}
/*void Setting::menuSoundCallback(Ref *pSender) {
UserDefault *userdefault = UserDefault::getInstance();
if (userdefault->getBoolForKey("sound_key")) {
userdefault->setBoolForKey("sound_key", false);
}
else {
userdefault->setBoolForKey("sound_key", true);
SimpleAudioEngine::getInstance()->playEffect("sound");//remaining
}
}
void Setting::menuMusicCallback(Ref *pSender) {
UserDefault *userdefault = UserDefault::getInstance();
if (userdefault->getBoolForKey("music_key")) {
userdefault->setBoolForKey("music_key", false);
SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
else {
userdefault->setBoolForKey("music_key", true);
SimpleAudioEngine::getInstance()->playBackgroundMusic("music", true);//remaining
}
}*/

void Setting::onChangedCheckBox1(Ref *pSender, CheckBox::EventType type) {
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		break;	
	default:
		break;
	}
}
void Setting::onChangedCheckBox2(Ref *pSender, CheckBox::EventType type) {
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		SimpleAudioEngine::getInstance()->resumeEffect(0);
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		SimpleAudioEngine::getInstance()->pauseEffect(0);
		break;
	default:
		break;
	}
}
void Setting::onChangedSlider1(Ref * pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider * slider = dynamic_cast<Slider *>(pSender);
		int percent = slider->getPercent();
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent/100);
		log("------------------%d percent----------------", percent);
		//获取当前滑动的百分比
		//auto label = dynamic_cast<Label *>(getChildByName("label1"));
		//label->setString(String::createWithFormat("Perfecnt %d", percent)->getCString());
		//使用该百分比
	}
}
void Setting::onChangedSlider2(Ref * pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider * slider = dynamic_cast<Slider *>(pSender);
		int percent = slider->getPercent();
		SimpleAudioEngine::getInstance()->setEffectsVolume(percent / 100);
		//获取当前滑动的百分比
		//auto label = dynamic_cast<Label *>(getChildByName("label1"));
		//label->setString(String::createWithFormat("Perfecnt %d", percent)->getCString());
		//使用该百分比
	}
}

Setting::Setting()
{
}


Setting::~Setting()
{
}
