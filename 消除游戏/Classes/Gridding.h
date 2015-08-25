#ifndef GRIDDING_H
#define GRIDDING_H

#include "cocos2d.h"
USING_NS_CC;

class Gridding:public Node
{
public:

	bool init()
	{
		Node::init();
		
		auto draw = DrawNode::create();

		for (int i = 0; i < 9; i++)
		{
			draw->drawLine(Vec2(70 + i * 50, 400), Vec2(70 + i * 50, 800), Color4F::RED);//Êú
			draw->drawLine(Vec2(70, 400+i*50), Vec2(470, 400+i*50), Color4F::RED);  //ºá
		}

		addChild(draw);

		return true;
	}

	CREATE_FUNC(Gridding);

};


#endif;