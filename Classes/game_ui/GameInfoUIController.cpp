

#include "GameInfoUIController.h"
#include "LMenu.h"
#include "PlayerController.h"
#include "Player.h"
GameInfoUIController::GameInfoUIController()
:m_operationMenu(NULL)
,m_isShowTabBar(true)
,m_headIcon(NULL)
,m_headBtn(NULL)
,m_levelTTF(NULL)
,m_nickNameTTF(NULL)
,m_bloodPro(NULL)
,m_magicPro(NULL)
,m_gameTabBarMenu(NULL)
,m_attackEnemyInfo(NULL)
,m_chatInterface(NULL)
,m_pMenuBig(NULL)
, m_pDelegate(NULL)
, isPressDown(false)
{

}

GameInfoUIController::~GameInfoUIController()
{

}


bool GameInfoUIController::init()
{
    if (!Layer::init())
        return false;
    
    m_winSize = Director::getInstance()->getWinSize();
    // 头像 血条
    this->initWithHeadUI();
    //右上小地图
   // m_mapThumbnailMenu = MapThumbnailMenu::create();
   // m_mapThumbnailMenu->setPosition((Vec2)m_winSize - Point(100, 100));
   // this->addChild(m_mapThumbnailMenu);
    //操作界面
    m_operationMenu = LOperationMenu::create();
    this->addChild(m_operationMenu);

    //初始化敌人信息（血条 名字）一开始隐藏
    m_attackEnemyInfo = AttackEnemyInfo::create();
    m_attackEnemyInfo->setPosition(Point(m_winSize.width/2-125, m_winSize.height-110));
    this->addChild(m_attackEnemyInfo);
    m_attackEnemyInfo->hide();

#if 0
    //频道 
    m_chatInterface = ChatInterface::create();
    m_chatInterface->setPosition(Point(220, 0));
    this->addChild(m_chatInterface);
    //工具条
    m_gameTabBarMenu = GameTabBarMenu::create();
    m_gameTabBarMenu->setPosition(Point(m_winSize.width-960, -100));
    this->addChild(m_gameTabBarMenu);
#endif
	setKeyboardEnabled(true);
	scheduleUpdate();
    return true;
}

void GameInfoUIController::initWithHeadUI()
{
 
    //Layer* layer = Layer::create();
    //this->addChild(layer);
    
    Node* pNode= CSLoader::createNode("ui/cocostudio/GameUI.csb");
	pNode->setAnchorPoint(Vec2(0, 0));
    addChild(pNode);
    
    const char* nickName = PlayerController::sharePlayerController()->getPlayerName().c_str();
    m_nickNameTTF = static_cast<ui::Text *>(pNode->getChildByName("nickName"));
    if (m_nickNameTTF)
    {
        m_nickNameTTF->setString(nickName);
    }

    m_headIcon = dynamic_cast<ImageView*>(pNode->getChildByName("ImageView"));
    if (m_headIcon)
    {
        m_headIcon->setTouchEnabled(true);
    }
      //TextAtlas
    m_levelTTF = dynamic_cast<TextAtlas*>(pNode->getChildByName("level"));

    if (m_levelTTF)
    {
        m_levelTTF->setString("3");
    }

    m_bloodPro = dynamic_cast<LoadingBar*>(pNode->getChildByName("redBar"));
    if (m_bloodPro)
    {
        m_bloodPro->setPercent(100);
    }
    
    m_magicPro = dynamic_cast<LoadingBar*>(pNode->getChildByName("blueBar"));
    if (m_magicPro)
    {
        m_magicPro->setPercent(100);
    }

    m_headBtn = dynamic_cast<Button*>(pNode->getChildByName("head"));
    if (m_headBtn)
    {
        m_headBtn->setTouchEnabled(true);
        m_headBtn->addTouchEventListener(this, toucheventselector(GameInfoUIController::modeSwitch));
    }
    
}

void GameInfoUIController::modeSwitch(cocos2d::Ref *sender)
{
    if (this->getActionByTag(0xacff))
        return;
#if 0
    if (m_isShowTabBar)
    {
        m_isShowTabBar = false;
        m_operationMenu->hideOperationMenu();
        m_chatInterface->hideChatInterface();
        
        DelayTime* delay = DelayTime::create(0.3f);
        CallFunc* finish = CallFunc::create(m_gameTabBarMenu, callfunc_selector(GameTabBarMenu::showGameTabBarMenu));
        Sequence* actions = Sequence::create(delay, finish, NULL);
        actions->setTag(0xacff);
        this->runAction(actions);
    }
    else
    {
        m_isShowTabBar = true;
        m_gameTabBarMenu->hideGameTabBarMenu();
    
        DelayTime* delay = DelayTime::create(0.3f);
        CallFunc* finish = CallFunc::create(m_operationMenu, callfunc_selector(LOperationMenu::showOperationMenu));
        CallFunc* finish2 = CallFunc::create(m_chatInterface, callfunc_selector(ChatInterface::showChatInterface));
        Sequence* actions = Sequence::create(delay, finish, finish2, NULL);
        actions->setTag(0xacff);
        this->runAction(actions);
    }
#endif
}

void GameInfoUIController::updateBloodPro()
{
    //m_bloodPro->setPercent(100*Player::sharePlayer()->getBlood()/Player::sharePlayer()->getBloodCap());
}

void GameInfoUIController::updateMagicPro()
{
    //m_bloodPro->setPercent(100*Player::sharePlayer()->getMagic()/Player::sharePlayer()->getMagicCap());
}

void GameInfoUIController::updateLevelTTF()
{

}

void GameInfoUIController::addSmallMenu(cocos2d::Node *node)
{
    this->removeBigMenuAndButton(this,Control::EventType::TOUCH_UP_INSIDE);
    
    for (std::deque<Node*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
    {
        if (typeid(*node) == typeid(**itr))
            return;
    }
    
    if (m_pMenuSmall.size() >= 2)
    {
        m_pMenuSmall.at(0)->removeFromParent();
        m_pMenuSmall.pop_front();
        m_pMenuSmall.at(0)->setPosition(Point(m_winSize.width/4, (m_winSize.height+80)/2));
    }
    
    node->setPosition(Point(m_winSize.width/4 * (m_pMenuSmall.size()*2+1), (m_winSize.height+80)/2));
    this->addChild(node);
    m_pMenuSmall.push_back(node);
    
    this->setTouchEnabled(true);
}

void GameInfoUIController::removeSmallMenu(Node *node)
{
    if (node == NULL)
        return;
    
    std::deque<Node*>::iterator* pItr = NULL;
    for (std::deque<Node*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
    {
        if (node==(*itr))
        {
            pItr = &itr;
            break;
        }
    }
    
    if (pItr)
    {
        m_pMenuSmall.erase(*pItr);
        node->removeFromParent();
    }
    
    if (m_pMenuSmall.size() > 0)
    {
        m_pMenuSmall.at(0)->setPosition(Point(m_winSize.width/4, (m_winSize.height+80)/2));
    }
    else
    {
        this->setTouchEnabled(false);
    }
}

void GameInfoUIController::removeSmallMenuAndButton(Ref *node, Control::EventType controlEvent)
{
    this->removeSmallMenu((Node*)node);
}

void GameInfoUIController::addBigMenu(cocos2d::Node *node)
{
    this->removeBigMenuAndButton(this,Control::EventType::TOUCH_UP_INSIDE);
    
    if (m_pMenuSmall.size() > 0)
    {
        for (std::deque<Node*>::iterator itr=m_pMenuSmall.begin(); itr!=m_pMenuSmall.end(); itr++)
            (*itr)->removeFromParent();
        
        m_pMenuSmall.clear();
    }
    
    
    node->setPosition(Point(m_winSize.width/2, (m_winSize.height+80)/2));
    this->addChild(node);
    m_pMenuBig = node;
    
    this->setTouchEnabled(true);
}

void GameInfoUIController::removeBigMenuAndButton(Ref* node, Control::EventType controlEvent)
{
    if (m_pMenuBig)
    {
        m_pMenuBig->removeFromParent();
        m_pMenuBig = NULL;
    }
//    this->setTouchEnabled(false);
}

bool GameInfoUIController::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}
void GameInfoUIController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		isPressDown = true;
		m_iDirection = Vec2(-1.0, 0.0);
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		isPressDown = true;
		m_iDirection = Vec2(1.0, 0.0);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		isPressDown = true;
		m_iDirection = Vec2(0.0, 1.0);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		isPressDown = true;
		m_iDirection = Vec2(0.0, -1.0);
	}
}
void GameInfoUIController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	isPressDown = false;
	m_iDirection = Vec2(0.0,0.0);
	m_pDelegate->simpleDPadTouchEnded();
}
void GameInfoUIController::update(float delta)
{
	if (isPressDown)
	{
		m_pDelegate->isHoldingDirection(m_iDirection);
	}
}