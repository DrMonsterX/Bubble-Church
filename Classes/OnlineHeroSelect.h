#ifndef __ONLINEHEROSELECT_H__
#define __ONLINEHEROSELECT_H__


#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <client.hpp> 
#include <boost/order_message.hpp>
#include "cocos2d.h"


using boost::asio::ip::tcp;
using namespace std;
typedef std::deque<order_message> order_message_queue;


class OnlineHeroSelect : public cocos2d::Layer
{
public:

	friend class client;
	char* hero1 = "ssx";

	static cocos2d::Scene* createScene();


	virtual bool init();

	order_message roleChoice;
	order_message loginMsg;


	char name[7] = "stupid";
	

	int getPlayer1(order_message msg);
	void progressOrder1(order_message msg);
	
	
	// a selector callback
	void menuHeroCallback1(cocos2d::Ref* pSender);
	void menuHeroCallback2(cocos2d::Ref* pSender);
	void menuHeroCallback3(cocos2d::Ref* pSender);
	void menuHeroCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	static OnlineHeroSelect* create();
};

#endif