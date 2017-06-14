#pragma once
#ifndef _CHATTER_H
#define _CHATTER_H


#include"cocos2d.h"
#include"ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
class Chatter :public Layer
{
public:
	Chatter();
	virtual bool init();
	virtual void ButtonCallback1(Ref *pSender);
	virtual void ButtonCallback2(Ref *pSender);
	void textFieldEvent(Ref *pSender, TextField::EventType type);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event * even);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event * even);
	TextField *textField;
	TextField *temp;
	EventListenerKeyboard *keylisten;
	EventDispatcher *eventDispatcher;
	Text *displaylabel;

	CREATE_FUNC(Chatter);
	~Chatter();
};
#endif // !_POPULAYER_H
