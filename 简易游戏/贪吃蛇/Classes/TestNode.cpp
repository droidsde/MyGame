#include "TestNode.h"

bool TestNode::init()
{
	if (!Sprite::init())
	{
		return false;
	}

//	setContentSize(Size(100, 100));
	//setColor(Color3B::WHITE);
	//setCont

	setContentSize(Size(1030, 1500));
//	setColor(Color3B::YELLOW);

//	auto draw = DrawNode::create();
//	////draw->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::WHITE);
//	draw->drawDot(Vec2(0, 0),100, Color4F::WHITE);
//	//draw->drawSolidCircle();
//	draw->setAnchorPoint(Vec2(0, 0));
////	draw->setAnchorPoint(Vec2(0, 0));
//	addChild(draw);

	//auto a = Sprite::create("a.png");
	//a->setAnchorPoint(Vec2(0, 0));
	//addChild(a);

	setTextureRect(Rect(0, 0, 1000, 1000));



	return true;
}


