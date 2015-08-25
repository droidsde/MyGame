#include "GameScene.h"
#include "Block.h"
#include "GameOver.h"
#include "Edge.h"
Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -100));
	
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}
	
	this->setContentSize(Director::getInstance()->getVisibleSize());
	this->setColor(Color3B::WHITE);

	_size = Director::getInstance()->getVisibleSize();

	auto edge = Edge::create();
	edge->setPosition(_size.width/2,_size.height/2);
	addChild(edge);


	h = Hero::create();
	addChild(h);
	h->setPosition(200,300);
	h->setScale(0.5, 0.5);

	schedule(schedule_selector(GameScene::blockUpdate),1.0f);
	schedule(schedule_selector(GameScene::failUpdate), 1.0f);

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	return true;
}
  
void GameScene::blockUpdate(float dt)
{
     createABlock();
	
}

void GameScene::createABlock()
{
	auto block = Block::create();

	float w = _size.width*random(2, 10)/11;

	block->setPosition(w, 0);
	//MessageBox(__String::createWithFormat("%f", block->getPositionY())->getCString(), "1");
	addChild(block);
}

bool GameScene::onTouchBegan(Touch *touch,Event *event)
{
	//startPos = touch->getLocation();
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	
}

void GameScene::onTouchEnded(Touch *touch,Event *event)
{
	auto startPos = h->getPosition();
	auto endPos = touch->getLocation();
	auto diff = endPos - startPos;
	
	char dir;
	
		if (diff.x > 0)  dir = 'r';
		else   dir = 'l';
	
	

	h->move(dir);
}

void GameScene::failUpdate(float dt)
{

	/*if ((h->getPositionX()<0) || (h->getPositionX()>_size.width))
	{
		h->getPhysicsBody()->setVelocity( -h->getPhysicsBody()->getVelocity());
	}*/
	if ((h->getPositionY()< (h->getContentSize().width / 2+20)) || (h->getPositionY()>(_size.height - h->getContentSize().height / 2-20)))
	{
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, GameOver::createScene()));
	}
}