#include "GameOver.h"
#include "GameScene.h"

Scene* GameOver::createScene()
{
	Scene* scene = Scene::create();
	GameOver* layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	LayerColor::initWithColor(Color4B::WHITE);

	Size size = Director::getInstance()->getVisibleSize();
	auto label = LabelTTF::create("Game Over","arial",36);

	label->setColor(Color3B::BLACK);
	
	label->setPosition(size.width/2,size.height/2);
	addChild(label);

	
	MenuItemFont::setFontSize(60);
	MenuItemFont::setFontName("arial");


	MenuItemFont* item = MenuItemFont::create("play again", CC_CALLBACK_1(GameOver::onMenuCallBack, this));

	item->setColor(Color3B::BLACK);
	Menu* mu = Menu::create(item, nullptr);

	mu->setPosition(size.width / 2, size.height / 2 - 60);
	addChild(mu);
	
	return true;
}

void GameOver::onMenuCallBack(Ref* ref)
{
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1.0f, GameScene::createScene()));
}