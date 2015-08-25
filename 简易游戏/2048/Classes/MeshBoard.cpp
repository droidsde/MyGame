

#include "MeshBoard.h"


bool MeshBoard::init()
{
	Node::init();
	
//	auto size = Director::getInstance()->getVisibleSize();

//	float side = size.width;

	auto draw=DrawNode::create();

	

	for (int i = 0; i < 5; i++)
	{
		draw->drawLine(Vec2(50, 50+100*i), Vec2(450, 50+100*i), Color4F::YELLOW);
		draw->drawLine(Vec2(50+100*i,50), Vec2(50+100*i, 450), Color4F::YELLOW);
	}
	addChild(draw);

	return true;
}
