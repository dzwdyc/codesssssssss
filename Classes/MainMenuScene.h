
#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/cocosgui.h"
#include "cocostudio/cocostudio.h"

class MainMenuScene :public cocos2d::Layer
{
public:
    bool init();
	static cocos2d::Scene * createScene();
	void onEnter();
	void onExit();
	CREATE_FUNC(MainMenuScene);

	void StartBtnClick(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};



#endif /* defined(__MAIN_MENU__) */
