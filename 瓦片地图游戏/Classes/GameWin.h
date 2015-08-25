#ifndef GAMEWIN_H
#define GAMEWIN_H

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameWin:public LayerColor
{
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = GameWin::create();
		scene->addChild(layer);
		return scene;
	}

	bool init()
	{
		LayerColor::initWithColor(Color4B::WHITE);

		Size size = Director::getInstance()->getVisibleSize();
		auto label = Label::createWithTTF("YOU WIN","arial.ttf",50);
		label->setPosition(size.width/2,size.height/2);
		label->setColor(Color3B::BLACK);

		addChild(label);


		MenuItemFont::setFontSize(60);
		MenuItemFont::setFontName("arial");
	

		MenuItemFont* item = MenuItemFont::create("play again",CC_CALLBACK_1(GameWin::onMenuCallBack,this));

		item->setColor(Color3B::BLACK);
		Menu* mu = Menu::create(item,nullptr);

		mu->setPosition(size.width/2,size.height/2-60);
		addChild(mu);


		return true;
	}

	void onMenuCallBack(Ref* ref)
	{
		Director::getInstance()->replaceScene(TransitionFadeBL::create(1.0f,GameScene::createScene()));
	}

	CREATE_FUNC(GameWin);
};

#endif;