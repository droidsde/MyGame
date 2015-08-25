#include "Block.h"

bool Block::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_size = Director::getInstance()->getVisibleSize();

	 Size size = Size(100,10);


	 PhysicsMaterial a;
	 a.density = 1.0;
	 a.friction = 0.5;
	 a.restitution = 0.0;

	 setPhysicsBody(PhysicsBody::createBox(size,a));

	setTextureRect(Rect(0,0,size.width,size.height));
	setColor(Color3B::BLACK);

	setAnchorPoint(Vec2(0, 0));

	scheduleUpdate();
	getPhysicsBody()->setDynamic(false);
	getPhysicsBody()->setGravityEnable(false);

	

	return true;
}

void Block::update(float dt)
{
	this->setPositionY(this->getPositionY()+1);
	if (this->getPositionY()>(_size.height+this->getContentSize().height/2))
	{
		this->removeFromParent();
	}
	
}