

#include "ChessBoard.h"





bool ChessBoard::init()
{

	auto size = Director::getInstance()->getVisibleSize();

	auto draw = DrawNode::create(); 
	for (int i = 1; i <= 10; i++)
	{
		draw->drawLine(Vec2(50, 50*i), Vec2(450, 50*i), Color4F::RED);   //»­ºáÏß
		draw->drawLine(Vec2(50 * i,50), Vec2(50 * i,250), Color4F::RED);  //»­ÊúÏß
		draw->drawLine(Vec2(50 * i, 300), Vec2(50 * i, 500), Color4F::RED);  //»­ÊúÏß
	}
	draw->drawLine(Vec2(50, 250), Vec2(50, 300), Color4F::RED);  //»­ÊúÏß
	draw->drawLine(Vec2(450, 250), Vec2(450, 300), Color4F::RED);  //»­ÊúÏß
	addChild(draw);

	//std::string a = UTEXT("³þºÓ");
	//std::string b = UTEXT("ºº½ç");
	//auto  l1 = LabelTTF::create(UTEXT("³þºÓ"), "arial", 28);
	//l1->setPosition(100,275);

	//auto  l2 = LabelTTF::create(UTEXT("ºº½ç"), "arial", 28);
	//l2->setPosition(300, 275);
	//addChild(l1);

//	addChild(l2);
	//auto draw1 = DrawNode::create();
	//for (int i = 1; i <= 11; i++)
	//{
	//	draw1->drawLine(Vec2(25, 50 * i-25), Vec2(475, 50 * i-25), Color4F::YELLOW);   //
	//	draw1->drawLine(Vec2(50 * i-25, 25), Vec2(50 * i-25, 525), Color4F::YELLOW);  //
	//}
	//addChild(draw1);

	return true;
}