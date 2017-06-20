#ifndef __ONLINEHEROSELECT_H__
#define __ONLINEHEROSELECT_H__


#include <cstdlib>    
#include <iostream>  
#include <boost/asio.hpp>   
#include <client.hpp> 
#include <orderMessage.hpp>
#include "cocos2d.h"


using namespace std;


class OnlineHeroSelect : public cocos2d::Layer
{
public:

	friend class client;
	char* hero1 = "ssx";

	static cocos2d::Scene* createScene();


	virtual bool init();

	orderMessage roleChoice;
	orderMessage loginMsg;


	char name[7] = "stupid";//Default login name
	

	int getPlayer1(orderMessage msg);
	void progressOrder1(orderMessage msg);
	
	
	// a selector callback
	void menuHeroCallback1(cocos2d::Ref* pSender);
	void menuHeroCallback2(cocos2d::Ref* pSender);
	void menuHeroCallback3(cocos2d::Ref* pSender);
	void menuHeroCallback4(cocos2d::Ref* pSender);
	void menuSelectCallBack(cocos2d::Ref* pSender);

	static OnlineHeroSelect* create();
};

#endif
