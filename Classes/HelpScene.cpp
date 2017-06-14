#include "HelpScene.h"
#include "SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"ui/CocosGUI.h"

USING_NS_CC;

using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *Help::createScene() {
	auto sc = BaseLayer::createScene();
	auto ly = Help::create();
	sc->addChild(ly);
	return sc;
}
bool Help::init() {
	if (!BaseLayer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*auto background = Sprite::create("play1.png");
	background->setScale(1024 / 500, 768 / 375);
	background->setPosition(Vec2(512, 384));
	addChild(background);*/
	//txt
	/*auto txt = Label::createWithBMFont("fonts / BMFont.fnt", "help");//remaining
	txt->setColor(Color3B(14, 83, 204));//color
	//txt->setPosition(95, background->getPosition().y - 70);//position
	//txt->setAnchorPoint(Vec2(0, 0));
	txt->setPosition(Vec2(1024 * 0.1, 768 * 0.1));
	addChild(txt, 1);
	*/
	auto label = Label::createWithTTF("Help", "fonts/Marker Felt.ttf", 124);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label);
	//scrollview
	scrollpng = Sprite::create("enter.png");
	scrollpng->setAnchorPoint(Point(0.5, 0.5));
	scrollpng->setScale(1.5, 1.5);
	Size innersize = scrollpng->getContentSize();

	scroll = ScrollView::create();
	//scroll->getInnerContainer()->setAnchorPoint(Vec2(0.5*innersize.width,0.5*innersize.height));
	//scroll->getInnerContainer()->setPosition(Vec2(0.5 * 1024 , 0.5 * 768));
	scroll->setInnerContainerSize(Size(1.5*innersize.width,1.5*innersize.height));                  //设置滑动框的内容大小  
	scroll->setContentSize(Size(innersize.width, innersize.height));
	scroll->setScrollBarEnabled(true);//是否显示滚动条 //设置滑动框的大小  
	scroll->setDirection(ScrollView::Direction::VERTICAL);          //设置上下左右都可以滑动  
	scroll->setBackGroundImage("play1.png");         //设置背景图片       
	scroll->setBackGroundImageScale9Enabled(true);            //设置layout背景的capInsets,它只在开启scale9后影响背景图的渲染  
	scroll->addChild(scrollpng);                         //添加内容，这里我添加了一个Sprite，也可以是其他的对象，如果想显示丰富的内容可以添加layer  

	scrollpng->setPosition(Vec2(innersize.width / 2, innersize.height / 2));              //布局，把添加的Sprite位置调到中心点  

	scroll->setScrollBarColor(Color3B(255, 0, 0));                  //修改滑块颜色，给滑块添加图片，没有找到API，可能要自己添加  
	scroll->setAnchorPoint(Vec2(0.5, 0.5));									//ScrollViewBar* ScrollviewBar_H = ScrollViewBar::create(scroll, ScrollView::Direction::HORIZONTAL);               //获取滑动框的滑块对象  
	scroll->setPosition(Vec2(0.5*1024,0.5*768));
	this->addChild(scroll);
	scroll->addEventListener(CC_CALLBACK_2(Help::scrollCallback, this));


	//button resource only

	/*Button *Return = Button::create("returnnormal.png", "returnselected.png");
	Return->setPosition(Vec2(origin.x + visibleSize.width - Return->getContentSize().width / 2,
	origin.y + Return->getContentSize().height / 2));
	Return->addTouchEventListener(CC_CALLBACK_2(Help::HelpCloseCallback, this));
	Return->setPressedActionEnabled(true);
	addChild(Return);*/

	return true;
}
void Help::scrollCallback(Ref *pSender, ScrollView::EventType type) {
	switch (type)
	{
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_TOP:
		/*if (scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2) {
			moveby = MoveBy::create(0.1f, Vec2(0, 15));
			scrollpng->runAction(moveby);
		}
		//std::cout << scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2;
		log("%d", scrollpng->getPosition().y - scrollpng->getContentSize().height / 2 >= scroll->getPosition().y - scroll->getSize().height / 2);
		*/
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
		/*if (scrollpng->getPosition().y + scrollpng->getContentSize().height / 2 <= scroll->getPosition().y + scroll->getSize().height / 2) {
			moveby = MoveBy::create(0.1f, Vec2(0, -15));
			scrollpng->runAction(moveby);
		}*/
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_LEFT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLL_TO_RIGHT:
		break;
	case cocos2d::ui::ScrollView::EventType::SCROLLING:

		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
		//scrollpng->stopAction(moveby);
		break;
	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
		//scrollpng->stopAction(moveby);
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
Help::Help()
{
}


Help::~Help()
{
}
