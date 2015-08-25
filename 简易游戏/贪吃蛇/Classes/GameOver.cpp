

#include "GameOver.h"
#include "HelloWorldScene.h"

Scene* GameOver::createScene()
{
	auto s = Scene::create();
	auto l = GameOver::create();
	s->addChild(l);
	return s;
}

bool GameOver::init()
{
	LayerColor::initWithColor(Color4B::BLACK);

	visibleSize = Director::getInstance()->getVisibleSize();

	auto label = Label::create();
	label->setString("Game Over");
	label->setSystemFontSize(50);
	label->setColor(Color3B::WHITE);
	addChild(label);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);


	auto btn = Button::create("a.png","b.png");
	btn->setTitleText("renew");
	btn->setPosition(Vec2(100, 100));
	btn->addTouchEventListener(CC_CALLBACK_2(GameOver::touchEvent,this));
	//btn->addClickEventListener(CC_CALLBACK_2(GameOver::touchEvent,this));

	addChild(btn);




	return true;
}
void GameOver::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	//switch (type)
	//{
	//case Widget::TouchEventType::BEGAN:
	//	MessageBox("click1", "click2");
	//	break;
	//}
	if (type == Widget::TouchEventType::BEGAN)
	{
		//MessageBox("click1", "click2");
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}