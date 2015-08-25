#include "ShopScene.h"

Scene* ShopScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShopScene::create();
	scene->addChild(layer);
	return scene;
}

bool ShopScene::init()
{
	Layer::init();

	Size ssize = Director::getInstance()->getVisibleSize();
	
	auto background = Sprite::create("shopScene.png");
	background->setAnchorPoint(Vec2(0,0));
	addChild(background);

	auto button = Button::create("back1.png", "back2.png");
	button->addTouchEventListener(CC_CALLBACK_2(ShopScene::onTouchBack, this));
	button->setPosition(Vec2(100, 100));
	addChild(button);

	return true;
}

void ShopScene::onTouchBack(Ref* ref,Widget::TouchEventType type)
{
	auto call = CallFunc::create([]()
	{
		Director::getInstance()->popScene();
	});
	this->runAction(Sequence::create(DelayTime::create(0.5),call,nullptr));
}