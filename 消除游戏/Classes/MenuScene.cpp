#include "MenuScene.h"
#include "ShopScene.h"
#include "GameScene.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;

}

bool MenuScene::init()
{
	Layer::init();

	auto ssize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("menuScene.png");
	background->setAnchorPoint(Vec2(0,0));
	addChild(background);

	auto startItem = MenuItemImage::create("startButton1.png", "startButton2.png",CC_CALLBACK_1(MenuScene::onMenuEvent, this));
	startItem->setTag(1);
	auto shopItem = MenuItemImage::create("shopButton1.png", "shopButton2.png", CC_CALLBACK_1(MenuScene::onMenuEvent, this));
	shopItem->setTag(2);
	auto quitItem = MenuItemImage::create("quitButton1.png", "quitButton2.png", CC_CALLBACK_1(MenuScene::onMenuEvent, this));
	quitItem->setTag(3);

	auto menu = Menu::create(startItem,shopItem,quitItem,NULL);

	menu->alignItemsVerticallyWithPadding(12);
	addChild(menu);
	
	menu->setPosition(Vec2(ssize.width/2,ssize.height/2-100));
	return true;

}

void MenuScene::onMenuEvent(Ref* sender)
{
	auto item = (MenuItem*)sender;
	
	switch (item->getTag())
	{
	case 1:
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, GameScene::createScene()));
		break;
	case 2:
	
		Director::getInstance()->pushScene(TransitionFadeTR::create(1.0f, ShopScene::createScene()));
		break;
	case 3:
		auto call = CallFunc::create([](){
			Director::getInstance()->end();
		});
		this->runAction(Sequence::create(DelayTime::create(0.5f),call,nullptr));
		break;
	}
}