#ifndef __MODESELECT_H__
#define __MODESELECT_H__

#include "cocos2d.h"
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <client.hpp> 
#include <boost/order_message.hpp>
;
using boost::asio::ip::tcp;
using namespace std;

class ModeSelect : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	
	
	
	// a selector callback
	void menuSinglePuzzleCallback(cocos2d::Ref* pSender);
	void menuFateBeatCallback(cocos2d::Ref* pSender);
	void menuDoubleCallback(cocos2d::Ref* pSender);
	void menuOnLineCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ModeSelect);
};

#endif