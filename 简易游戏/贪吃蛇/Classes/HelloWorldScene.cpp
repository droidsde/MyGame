#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "TileMap.h"
#include "GameOver.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	///网格图
	auto map = TileMap::create();
	addChild(map);

	

	 egg = SnakeNode::createNode(3, 3);
	addChild(egg);
	snakes = Snake::createSnake(Vec2(0,1));
	addChild(snakes);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	schedule(schedule_selector(HelloWorld::update), 0.5f);
    return true;
}


void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W && (snakes->getDir())!=Vec2(0,-1))
	{
		snakes->setDir(Vec2(0, 1));
		if (snakes->checkEat(egg))
		{
			snakes->eat(egg);
			egg = createEgg();
		}
		
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S && (snakes->getDir()) != Vec2(0, 1))
	{
		snakes->setDir(Vec2(0, -1));
		if (snakes->checkEat(egg))
		{
			snakes->eat(egg);
			egg = createEgg();
		}
		
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A && (snakes->getDir()) != Vec2(1, 0))
	{
		snakes->setDir(Vec2(-1,0));
		if (snakes->checkEat(egg))
		{
			snakes->eat(egg);
			egg = createEgg();
		}
		
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D && (snakes->getDir()) != Vec2(-1, 0))
	{
		snakes->setDir(Vec2(1,0));
		if (snakes->checkEat(egg))
		{
			snakes->eat(egg);
			egg = createEgg();
		}
		
	}
}

void HelloWorld::update(float dt)
{
	snakes->goDir();
	if(snakes->checkEat(egg))
	{
		snakes->eat(egg);
		egg = createEgg();
	}
	if (!snakes->isOut()||snakes->touchItself())
	{

		unschedule(schedule_selector(HelloWorld::update));

		Director::getInstance()->replaceScene(GameOver::createScene());
	}
}


SnakeNode* HelloWorld::createEgg()
{

	int x = random(1, 6);
	int y = random(1, 10);

	
	auto negg = SnakeNode::createNode(x, y);

	negg->sNode->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::ORANGE);
	addChild(negg);
	return negg;
}