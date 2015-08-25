#include "Edge.h"

bool Edge::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getVisibleSize();

	//Size tSize = Size(size .width,10);

	PhysicsMaterial a;
	a.density = 1.0;
	a.friction = 1.0;
	a.restitution = 0.0;
	
	setPhysicsBody(PhysicsBody::createEdgeBox(size));

	//setContentSize(tSize);
	//setAnchorPoint(Vec2(0, 0));
	//setPosition(0,5);

	getPhysicsBody()->setContactTestBitmask(1);
	return true;
}