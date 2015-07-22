#include "MainMenuScene.h"
#include "RoleCreateLayer.h"
#include "GameScene.h"
#include "PlayerController.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
bool MainMenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }
	do 
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/wanlichengcheng.mp3");

		Node* _pNode = CSLoader::createNode("ui/cocostudio/MainMenu.csb");
		_pNode->setAnchorPoint(Vec2(0, 0));
		addChild(_pNode);

		Widget* _pMenu = static_cast<cocos2d::ui::Widget*>(_pNode->getChildByTag(11));

		Button* _pStart = static_cast<Button*>(_pMenu->getChildByName("Button_1"));
		_pStart->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::StartBtnClick, this));

		Button* _pClose = static_cast<Button*>(_pMenu->getChildByName("Button_4"));
		_pClose->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
				return;
#endif
				Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
#endif
			}
		});
	} while (0);
   
    return true;
}

void MainMenuScene::onEnter()
{
	Layer::onEnter();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/wanlichengcheng.mp3", true);
}

void MainMenuScene::StartBtnClick(Ref *pSender, ui::Widget::TouchEventType type){
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	{
	}
		break;
	case Widget::TouchEventType::ENDED:
	{
		PlayerController* _playerController = PlayerController::sharePlayerController();
		_playerController->setPlayerNumber(11001 + 3000);
	    _playerController->setWeaponsNumber(1000);
	    _playerController->setPlayerName("YKZY");
		Director::getInstance()->replaceScene(GameScene::createScene());
		//mapid 200 born 4
		//Director::getInstance()->replaceScene(RoleCreateLayer::createScene());
	}
		break;
	default:
		break;
	}
    
}

Scene * MainMenuScene::createScene()
{
    auto scene=Scene::create();
	auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

void MainMenuScene::onExit()
{
	CSLoader::destroyInstance();
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/wanlichengcheng.mp3");
	Layer::onExit();
}

