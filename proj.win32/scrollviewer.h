#pragma once
#define SCROLL_VIEWER_H
#include "cocos2d.h"  

USING_NS_CC;

// ��Ļ�ߴ�  
const float WINDOW_WIDTH = 1024;
const float WINDOW_HEIGHT = 768;

// �������  
const int TOUCH_DELTA = 5;

class ScrollView : public CCLayer
{
private:
	// ���µ�  
	CCPoint m_TouchDownPoint;
	// ̧��� ���ʹ���ж��Ƿ�Ϊ����¼�  
	CCPoint m_TouchUpPoint;
	// ��ǰ������  
	CCPoint m_TouchCurPoint;

private:
	// ��ҳ��  
	int m_Page;
	// ��ǰ��ʾҳ  
	int m_CurPage;

private:
	// �洢����ҳ��  
	CCArray *m_PageLayer;

private:
	// ��תҳ  
	void goToPage();

public:
	ScrollView();
	~ScrollView();

	virtual bool init();

	CREATE_FUNC(ScrollView);

public:
	// ��ʼ�����  
	virtual void onEnter();
	virtual void onExit();

	// �����¼����  
	virtual bool TouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void TouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void TouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void TouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

public:
	// ���ҳ  
	void addPage(CCLayer *pPageLayer);

};
class scrollviewer
{
public:
	scrollviewer();
	~scrollviewer();
};

