
#include "GameScene.h"
#include "Gridding.h"

#include "GameOverScene.h"


int GameScene::m_score = 0;
Label* GameScene::m_recordScore = nullptr;
LoadingBar* GameScene::m_bonusbar = nullptr;

Scene* GameScene::createScene()
{

	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	Layer::init();

	 m_num1=3;
	 m_num2=3;
	 m_num3=3;

	auto background = Sprite::create("gameScene.png");
	background->setAnchorPoint(Vec2(0, 0));
	addChild(background);

	auto grids = Gridding::create();

	addChild(grids);
	
	Size size = Director::getInstance()->getVisibleSize();


/////暂停/开始按钮
	isPause = false;
	auto control = Sprite::create("pause.png");
	//control->addTouchEventListener(CC_CALLBACK_2(GameScene::onSettingCallBack,this));
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [control,this](Touch *t,Event *e){
		if (control->getBoundingBox().containsPoint(t->getLocation()))   isPause = !isPause;
		if (isPause)
		{
			control->setTexture("resume.png");
			unschedule(schedule_selector(GameScene::onReducingScore));
		}
		else
		{
			control->setTexture("pause.png");
			schedule(schedule_selector(GameScene::onReducingScore));
		}
		return false;
	};

	addChild(control);
	control->setPosition(Vec2(80,300));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

//////裁剪
	auto stencil = Sprite::create();
	stencil->setTextureRect(Rect(0,0,400,400));
	//stencil->setContentSize(Size(400, 400));
	//stencil->setColor(Color3B::WHITE);
	stencil->setAnchorPoint(Vec2(0, 0));
	stencil->setPosition(70, 400);

	auto clipper = ClippingNode::create();
	clipper->setStencil(stencil);//设置裁剪模板 //
	clipper->setInverted(false);//设置底板可见
	clipper->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
	this->addChild(clipper);//

	 dustgrid = DustGrid::create(8, 8);
	
	dustgrid->setPosition(70,400);
	//	addChild(dustgrid);
	clipper->addChild(dustgrid);//5

	//clipper->setPosition(Vec2(size.width / 2, size.height / 2));

////显示分数
	auto label = Label::createWithTTF("socre:","arial.ttf",48);
	label->setColor(Color3B::RED);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(50, size.height - 80);
	label->enableOutline(Color4B::BLACK, 1);
	addChild(label);

	m_recordScore = Label::createWithTTF("0","arial.ttf",48);
	m_recordScore->setColor(Color3B::RED);
	m_recordScore->setAnchorPoint(Vec2(0, 0));
	m_recordScore->setPosition(200,size.height-80);
	m_recordScore->enableOutline(Color4B::BLACK, 1);
	addChild(m_recordScore);

	////
	//倒计时条外框
	auto bounusbar_frame = Sprite::create("bonusbar.png");
	bounusbar_frame->setPosition(Vec2(size.width / 2, size.height - 100));
	addChild(bounusbar_frame);

	//倒计时条bonusbar_fill.png
	m_bonusbar = LoadingBar::create("bonusbar_fill.png");
	m_bonusbar->setPercent(100);
	m_bonusbar->setPosition(bounusbar_frame->getPosition());
	addChild(m_bonusbar);

	schedule(schedule_selector(GameScene::onReducingScore),0.1f);
	////////////////

	///游戏道具
	auto item1 = MenuItemImage::create("t1.png","p1.png",CC_CALLBACK_1(GameScene::onToolMenu,this));
	item1->setTag(1);
	auto item2 = MenuItemImage::create("t2.png", "p2.png",CC_CALLBACK_1(GameScene::onToolMenu,this));
	item2->setTag(2);
	auto item3 = MenuItemImage::create("t3.png", "p3.png",CC_CALLBACK_1(GameScene::onToolMenu,this));
	item3->setTag(3);
	auto menu = Menu::create(item1,item2,item3,nullptr);

	menu->alignItemsHorizontallyWithPadding(10);
	addChild(menu);

	menu->setPosition(Vec2(size.width/2+60,265));

	m_tool1 = Label::createWithTTF("3","arial.ttf",24);
	m_tool1->setPosition(248,300);

	m_tool2 = Label::createWithTTF("3", "arial.ttf", 24);
	m_tool2->setPosition(358, 300);
	m_tool3 = Label::createWithTTF("3", "arial.ttf", 24);
	m_tool3->setPosition(468, 300);

	addChild(m_tool1);
	addChild(m_tool2);
	addChild(m_tool3);



	return true;
}

//在Node中加入元素，元素的位置是按照它的实际位置所安排，当Node 移动时,里面元素也会跟着移动。

void GameScene::getScore()
{
	m_score += 10;
	m_bonusbar->setPercent(m_bonusbar->getPercent() + 0.1);
	m_recordScore->setString(__String::createWithFormat("%d",m_score)->getCString());
}

void GameScene::onReducingScore(float dt)
{
	m_bonusbar->setPercent(m_bonusbar->getPercent() - 0.2);
	if (m_bonusbar->getPercent() == 0)
	{
		_eventDispatcher->pauseEventListenersForTarget(this);
		publishScore();
		unschedule(schedule_selector(GameScene::onReducingScore));
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameOver::createScene()));
		
	}
}

void GameScene::publishScore()
{
	auto userdefault = UserDefault::getInstance();
	//MessageBox(userdefault->getXMLFilePath().c_str(),"1");
	char score_str[100] = {0};
	sprintf(score_str,"%d",m_score);
	userdefault->setStringForKey("NewScore",score_str);

	auto bestscore = userdefault->getStringForKey("BestScore");
	if (m_score >= atoi(bestscore.c_str()))
	{
		userdefault->setStringForKey("BestScore",score_str);
	}
}

void GameScene::onToolMenu(Ref* ref)
{
	auto item = (MenuItem*)ref;
	switch (item->getTag())
	{
	case 1:
		if (m_num1 > 0)
		{
			m_num1--;
			m_tool1->setString(__String::createWithFormat("%d",m_num1)->getCString());
			dustgrid->setTool(1);
		}
		
		break;
	case 2:
		if (m_num2 > 0)
		{
			m_num2--;
			m_tool2->setString(__String::createWithFormat("%d", m_num2)->getCString());
			//dustgrid->setVisible(false);
			dustgrid->setTool(2);
		}
		break;
	case 3:
		if (m_num3 > 0)
		{
			m_num3--;
			m_tool3->setString(__String::createWithFormat("%d", m_num3)->getCString());
			m_bonusbar->setPercent(m_bonusbar->getPercent()+30);
		}
		break;

	}
}

void GameScene::onSettingCallBack(Ref* ref,Widget::TouchEventType type)
{
//	Director::getInstance()->pushScene(TransitionFade::create(0.5f,SettingLayer::createScene()));
}