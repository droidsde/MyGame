#include "GameOverScene.h"
#include "MenuScene.h"
#include "GameScene.h"

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	Layer::init();

	auto background = Sprite::create("gameOverScene.png");
	background->setAnchorPoint(Vec2(0,0));
	addChild(background);

//	auto ns = UserDefault::getStringForKey("NewScore");
	auto newScore = Label::createWithTTF("new score:" + UserDefault::getInstance()->getStringForKey("NewScore"),"arial.ttf",64);
	newScore->setColor(Color3B::WHITE);
	newScore->enableOutline(Color4B::BLACK,1);
	addChild(newScore);
	newScore->setPosition(Vec2(270,800));

	auto bestScore = Label::createWithTTF("best score:" + UserDefault::getInstance()->getStringForKey("BestScore"), "arial.ttf", 64);
	bestScore->setColor(Color3B::WHITE);
	bestScore->enableOutline(Color4B::BLACK, 1);
	addChild(bestScore);
	bestScore->setPosition(Vec2(270,700));

	auto homeItem = MenuItemImage::create("home1.png","home2.png",CC_CALLBACK_1(GameOver::onMenuItem,this));
	homeItem->setTag(1);
	auto replayItem = MenuItemImage::create("replay1.png", "replay2.png", CC_CALLBACK_1(GameOver::onMenuItem, this));
	replayItem->setTag(2);

	auto mu = Menu::create(homeItem,replayItem,nullptr);
	addChild(mu);
	mu->alignItemsHorizontallyWithPadding(12);

	return true;
}

void GameOver::onMenuItem(Ref* ref)
{
	auto item = (MenuItem*)ref;
	switch (item->getTag())
	{
	case 1:
		Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, MenuScene::createScene()));
		break;
	case 2:
		Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, GameScene::createScene()));
		break;
	}

}