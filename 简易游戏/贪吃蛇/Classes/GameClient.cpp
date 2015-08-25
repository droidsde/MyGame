#include "GameClient.h"
#include "ToC.h"
//#include "SnakeNode.h"
#include "TestNode.h"

Scene* GameClient::createScene()
{
	auto scene = Scene::create();

	auto client = GameClient::create();
	scene->addChild(client);

	return  scene;
}

bool GameClient::init()
{
	
	LayerColor::initWithColor(Color4B::BLACK);
	size = Director::getInstance()->getVisibleSize();

	title = LabelTTF::create(UTEXT("贪吃蛇"),"arial",35);

	title->setPosition(Vec2(size.width/2,size.height*0.75));

	addChild(title);

	btnS = Button::create("start.png","end.png");
	btnS->setScale(0.2);
	btnS->setPosition(Vec2(size.width / 2, size.height/2));




	btnE = Button::create("end.png", "start.png");
	btnE->setScale(0.2);
	btnE->setPosition(Vec2(size.width / 2, size.height / 4));

	addChild(btnS);
	addChild(btnE);

	
	//auto node = SnakeNode::createNode(1,2);
	//addChild(node);

	auto snode = TestNode::create();
	//snode->setPosition(Vec2(50, 50));
	snode->setAnchorPoint(Vec2(0, 0));

	snode->setPosition(Vec2(100,100 ));
	snode->setTexture("a.png");
	addChild(snode);


	int x = snode->getContentSize().width;
	int y = snode->getContentSize().height;

	char a[5];
	sprintf(a, "%d", x);
	char b[5];
	sprintf(b, "%d", y);
	

	MessageBox(a,"width");
	MessageBox(b, "width");

	return true;
}