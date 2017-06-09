#include "cocos2d.h"
USING_NS_CC;
class Boom:public Layer
{
public:
	int flag = 1;
	bool isBoom = false;
	int power = 1;
	cocos2d::Point position;
	Sprite* sprite;

	static Boom* createBoomSprite(cocos2d::Point position);
	virtual bool init();
	void boomInit(cocos2d::Point position);
	Animate* createAnimate(int num);



	CREATE_FUNC(Boom);

	
};

