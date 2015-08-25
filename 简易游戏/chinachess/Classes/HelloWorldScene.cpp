#include "HelloWorldScene.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
#include "ChessBoard.h"
#include "ToC.h"


USING_NS_CC;

//using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


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
	// 1. super init first  继承重写方法需要super一次
	if (!Layer::init())
	{
		return false;
	}

	// auto rootNode = CSLoader::createNode("MainScene.csb");

	//  addChild(rootNode);

	auto  l1 = LabelTTF::create(UTEXT("楚河"), "arial", 30);
	l1->setPosition(150, 275);

	auto  l2 = LabelTTF::create(UTEXT("汉界"), "arial", 30);
	l2->setPosition(350, 275);
	addChild(l1);
	addChild(l2);


	isLocked = false;  //没有锁定
	//isM = false;  //没有移动
	isRed = true;   //红色先走
	auto chessBoard = ChessBoard::create();

	addChild(chessBoard, 0);

	draw = DrawNode::create();
	draw->drawRect(Vec2(-50, -50), Vec2(0, 0), Color4F::BLUE);
	addChild(draw, 1);

	//auto chessBoard1 = ChessBoard::create();

	//
	////chessBoard1->setPosition(chessBoard1->getPosition()-Vec2(25,25));
	////addChild(chessBoard1, 0);
	int i;


	//摆红棋子

	for ( i = 0; i < 16; i++)
	{
		if (i < 5)
		{
			rChess[i] = Chess::createChess(UTEXT("兵"), 'r', 2*i, 6,'b');
		//	rChess[i]->move(2*i, 6);
			addChild(rChess[i], 2);
		}
		if (i == 5 || i == 6)
		{
			rChess[i] = Chess::createChess(UTEXT("炮"), 'r', 1 + 6 * (i - 5), 7,'p');
			//rChess[i]->move(1 + 6 * (i - 5), 7);
			addChild(rChess[i], 2);
		}
		if (i == 7||i==8)
		{
			rChess[i] = Chess::createChess(UTEXT("车"), 'r', 0 + 8 * (i - 7), 9,'c');
			//rChess[i]->move(0 + 8 * (i - 7), 9);
			addChild(rChess[i], 2);
		}
		if (i == 9 || i == 10)
		{
			rChess[i] = Chess::createChess(UTEXT("马"), 'r', 1 + 6 * (i - 9), 9,'m');
			//rChess[i]->move(1 + 6 * (i - 9), 9);
			addChild(rChess[i], 2);
		}

		if (i == 11 || i == 12)
		{
			rChess[i] = Chess::createChess(UTEXT("相"), 'r', 2 + 4 * (i - 11), 9,'x');
		//	rChess[i]->move(2 + 4 * (i - 11), 9);
			addChild(rChess[i], 2);
		}

		if (i == 13 || i == 14)
		{
			rChess[i] = Chess::createChess(UTEXT("士"), 'r', 3 + 2 * (i - 13), 9,'s');
		//	rChess[i]->move(3 + 2 * (i - 13), 9);
			addChild(rChess[i], 2);
		}

		if (i == 15)
		{
			rChess[i] = Chess::createChess(UTEXT("将"), 'r', 4, 9,'j');
			//rChess[i]->move(4, 9);
			addChild(rChess[i], 2);
		}

	
	}
	for (i = 0; i < 16; i++)
	{
		rVChess.pushBack(rChess[i]);
	}



	//摆绿棋子

	for ( i = 0; i < 16; i++)
	{
		
		if (i < 5)
		{
			gChess[i] = Chess::createChess(UTEXT("兵"), 'g', 2 * i, 3,'b');
			//gChess[i]->move(2*i,3);

			addChild(gChess[i], 2);
		}
		if (i == 5 || i == 6)
		{
			gChess[i] = Chess::createChess(UTEXT("炮"), 'g', 1 + 6 * (i - 5), 2,'p');
		//	gChess[i]->move(1 + 6 * (i - 5), 2);
			addChild(gChess[i], 2);
		}
		if (i == 7 || i == 8)
		{
			gChess[i] = Chess::createChess(UTEXT("车"), 'g', 0 + 8 * (i - 7), 0,'c');
		//	gChess[i]->move(0 + 8 * (i - 7), 0);
			addChild(gChess[i], 2);
		}
		if (i == 9 || i == 10)
		{
			gChess[i] = Chess::createChess(UTEXT("马"), 'g', 1 + 6 * (i - 9), 0,'m');
		//	gChess[i]->move(1 + 6 * (i - 9), 0);
			addChild(gChess[i], 2);
		}

		if (i == 11 || i == 12)
		{
			gChess[i] = Chess::createChess(UTEXT("相"), 'g', 2 + 4 * (i - 11), 0,'x');
		//	gChess[i]->move(2 + 4 * (i - 11), 0);
			addChild(gChess[i], 2);
		}

		if (i == 13 || i == 14)
		{
			gChess[i] = Chess::createChess(UTEXT("士"), 'g', 3 + 2 * (i - 13), 0,'s');
		//	gChess[i]->move(3 + 2 * (i - 13), 0);
			addChild(gChess[i], 2);
		}

		if (i == 15)
		{
			gChess[i] = Chess::createChess(UTEXT("将"), 'g', 4, 0,'j');
		//	gChess[i]->move(4, 0);
			addChild(gChess[i], 2);
		}


	}

	for (i = 0; i < 16; i++)
	{
		gVChess.pushBack(gChess[i]);
	}


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
    return true;
}

bool HelloWorld::onTouchBegan(Touch *t, Event *e)
{



	//判断是否移动
	if (isLocked)
	{
		xL = (t->getLocation().x - 25) / 50;
		yL = (t->getLocation().y - 25) / 50;

		if (xL<0 || xL>8 || yL<0 || yL>9)
		{
			isLocked = false;
		}

		////判断是否重新锁定
		if (isRed)
		{
			for (int i = 0; i < rVChess.size(); i++)   //转换红棋子
			{
				if (xL == rVChess.at(i)->getX() && yL == rVChess.at(i)->getY())
				{
      			
					isLocked = false;
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < gVChess.size(); i++)   //转换绿棋子
			{
				if (xL == gVChess.at(i)->getX() && yL == gVChess.at(i)->getY())
				{
					isLocked = false;
					break;
				}
			}
		}

		if (isLocked)
		{
			l = Vec2(xL, yL);
			if (isT(p, l, lChess->getType(), lChess->getName()))  //判断是否符合游戏的棋子规则
			{

				///如果移动了
				lChess->move(xL, yL);

				////判断是否吃了棋子
				if (isRed)
				{
					for (int i = 0; i < gVChess.size(); i++)   //遍历绿色棋子有没有被吃，吃了绿棋子容器减去该棋子
					{
						if (xL == gVChess.at(i)->getX() && yL == gVChess.at(i)->getY())
						{
							lChess->eat(gVChess.at(i));
							gVChess.at(i)->removeFromParent();
							gVChess.erase(i);

						//	MessageBox("红吃了", "提示");
						}
					}
				}
				else
				{
					for (int i = 0; i < rVChess.size(); i++)   //遍历红色棋子有没有被吃，吃了红棋子容器减去该棋子
					{
						if (xL == rVChess.at(i)->getX() && yL == rVChess.at(i)->getY())
						{
							lChess->eat(rVChess.at(i));
							rVChess.at(i)->removeFromParent();
							rVChess.erase(i);

							//MessageBox("绿吃了", "提示");
						}
					}
				}
				isLocked = false;   //移动后不锁定
				isRed = !isRed;    //转换移动方（红蓝方）
				draw->setPosition(Vec2(-100, -100));  //锁定框消失
			}
		}
		
	}



	//棋子锁定
	if (isRed)
	{
		
			for (int i = 0; i < rVChess.size(); i++)   //遍历红色棋子有没有被锁定
			{
				if (rVChess.at(i)->getBoundingBox().containsPoint(t->getLocation()))
				{

					lChess = rVChess.at(i);   //锁定前棋子
					isLocked = true;  //被锁定

					xL = (t->getLocation().x - 25) / 50;
					yL = (t->getLocation().y - 25) / 50;
					p = Vec2(xL, yL);
					draw->setPosition(Vec2(xL * 50 + 75, yL * 50 + 75));  //锁定框移动


				}
			}
		
	}
		//////解决吃了棋子的数组问题 用容器类
	else
	{
		
			for (int i = 0; i < gVChess.size(); i++)
			{
				if (gVChess.at(i)->getBoundingBox().containsPoint(t->getLocation()))
				{

					lChess = gVChess.at(i);   //锁定前棋子

					isLocked = true;  //被锁定

					xL = (t->getLocation().x - 25) / 50;
					yL = (t->getLocation().y - 25) / 50;
					p = Vec2(xL, yL);
					draw->setPosition(Vec2(xL * 50 + 75, yL * 50 + 75));  //锁定框移动

				}

			}
		
	}

	

	return true;


}

void HelloWorld::onTouchMoved(Touch *t, Event *e)
{
}

void HelloWorld::onTouchEnded(Touch *t, Event *e)
{

}


bool HelloWorld::isT(Vec2 p, Vec2 l, char type, char name)
{





	//红兵
	if (type == 'r'&&name == 'b')
	{
		if (l.y <= 4)
		{
			if (l - p == Vec2(0, -1) || 
				l - p == Vec2(-1, 0) ||
				l - p == Vec2(1, 0))
			{
				return true;
			}

		}
		else
		{
			if (l - p == Vec2(0, -1))
			{
				return true;
			}
		}
	}

	//绿兵
	if (type == 'g'&&name == 'b')
	{
		if (l.y >= 5)
		{
			if (l - p == Vec2(0, 1) ||
				l - p == Vec2(-1, 0) ||
				l - p == Vec2(1, 0))
			{
				return true;
			}

		}
		else
		{
			if (l - p == Vec2(0, 1))
			{
				return true;
			}
		}
	}

	///炮
	if (name == 'p')
	{
		/*if ((l - p).x == 0 || (l - p).y == 0)
			{

			return true;
			}*/

		if (p.x == l.x || p.y == l.y)
		{
			if (checkExitP(p, l) == 1 || checkExitP(p, l) == 3)
			{
				return true;
			}
		}

	/*	if ((l - p).x == 0)
		{
			///绿色棋子  红色棋子
			///if ()   横向查看是否有棋子拦住
			{

			}
			return true;
	    }*/
		
	}

	///车
	if (name == 'c')
	{
		/*if ((l - p).x == 0 || (l - p).y == 0)
		{
		return true;
		}*/
		if (p.x == l.x || p.y == l.y)
		{
			if (checkExitC(p, l) == 0)
			{
				return true;
			}
		}
	}



	///马
	if (name == 'm')
	{
		if ((l - p) == Vec2(2, 1)   ||
			(l - p) == Vec2(2, -1)  ||
			(l - p) == Vec2(1, 2)   ||
			(l - p) == Vec2(1, -2)  ||
			(l - p) == Vec2(-2, 1)  ||
			(l - p) == Vec2(-2, -1) ||
			(l - p) == Vec2(-1, 2)  ||
			(l - p) == Vec2(-1, -2))
		{
			return checkExitM(p, l);
		}
	}


	


	///红士
	if (type == 'r' && name == 's')
	{
		if (l.x >= 3 && l.x<= 5&& l.y>=7 && l.y<=9)
		{
			if ((l - p) == Vec2(1, 1) ||
				(l - p) == Vec2(1, -1) ||
				(l - p) == Vec2(-1, 1) ||
				(l - p) == Vec2(-1, -1))
			{
				return true;
			}
		}
	}

	//绿士
	if (type=='g'&& name == 's')
	{
		if (l.x >= 3 && l.x <= 5 && l.y >= 0 && l.y <= 2)
		{
			if ((l - p) == Vec2(1, 1) ||
				(l - p) == Vec2(1, -1) ||
				(l - p) == Vec2(-1, 1) ||
				(l - p) == Vec2(-1, -1))
			{
				return true;
			}
		}
	}

	///红将
	if (type='r' && name == 'j')
	{
		if (l.x >= 3 && l.x <= 5 && l.y >= 7 && l.y <= 9)
		{
			if ((l - p) == Vec2(0, 1) ||
				(l - p) == Vec2(0, -1) ||
				(l - p) == Vec2(1, 0) ||
				(l - p) == Vec2(-1, 0))
			{
				return true;
			}
		}
	}

	///绿将
	if (type = 'g' && name == 'j')
	{
		if (l.x >= 3 && l.x <= 5 && l.y >= 0 && l.y <= 2)
		{
			if ((l - p) == Vec2(0, 1) ||
				(l - p) == Vec2(0, -1) ||
				(l - p) == Vec2(1, 0) ||
				(l - p) == Vec2(-1, 0))
			{
				return true;
			}
		}
	}


	/////红相
	if (type = 'r' && name == 'x')
	{
		if (l.y >= 5&& p.y>=5)   ////不懂为什么还要限制p.y才能实现功能
		{
			if ((l - p) == Vec2(2, 2) ||
				(l - p) == Vec2(2, -2) ||
				(l - p) == Vec2(-2, 2) ||
				(l - p) == Vec2(-2, -2))
			{
			
				
				return checkExitX(p, l);
				
			}
		}

	}
	//绿相
	if (type = 'g' && name == 'x')
	{
		if (l.y <= 4 && p.y <= 4)
		{
			if ((l - p) == Vec2(2, 2) ||
				(l - p) == Vec2(2, -2) ||
				(l - p) == Vec2(-2, 2) ||
				(l - p) == Vec2(-2, -2))
			{
				
				return checkExitX(p, l);
			}
		}
	}


	MessageBox("棋子走位不正确", "提示");
		return false;
}



int HelloWorld::checkExitP(Vec2 p, Vec2 l)
{
	int num = 0;
	Vec2 d;

	if (p.x == l.x && p.y != l.y)   //棋子竖向移动
	{

		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.x == p.x)  //查看棋子是否在同一列
			{
				if ((d.y >= p.y && d.y <= l.y)||
					(d.y <= p.y && d.y >= l.y))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //检查绿棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.x == p.x)  //查看棋子是否在同一列
			{
				if ((d.y >= p.y&&d.y <= l.y) ||
					(d.y <= p.y&&d.y >= l.y))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}
		}

	}

	if (p.y == l.y && p.x != l.x)  //棋子横向移动
	{

		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.y == p.y)  //查看棋子是否在同一行
			{
				if ((d.x >= p.x && d.x <= l.x) ||
					(d.x <= p.x && d.x >= l.x))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查率棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.y == p.y)  //查看棋子是否在同一行
			{
				if ((d.x >= p.x && d.x <= l.x) ||
					(d.x <= p.x && d.x >= l.x))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}
		}

	}

	/*char a[10];
	sprintf(a,"%d",num);
	MessageBox(a,"tip");*/
	return num;

}

int HelloWorld::checkExitC(Vec2 p, Vec2 l)
{
	int num = 0;
	Vec2 d;

	if (p.x == l.x && p.y != l.y)   //棋子竖向移动
	{

		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.x == p.x)  //查看棋子是否在同一列
			{
				if ((d.y > p.y && d.y < l.y) ||
					(d.y < p.y && d.y > l.y))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //检查绿棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.x == p.x)  //查看棋子是否在同一列
			{
				if ((d.y > p.y&&d.y < l.y) ||
					(d.y < p.y&&d.y > l.y))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}
		}

	}

	if (p.y == l.y && p.x != l.x)  //棋子横向移动
	{

		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.y == p.y)  //查看棋子是否在同一行
			{
				if ((d.x > p.x && d.x < l.x) ||
					(d.x < p.x && d.x > l.x))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查率棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.y == p.y)  //查看棋子是否在同一行
			{
				if ((d.x > p.x && d.x < l.x) ||
					(d.x < p.x && d.x > l.x))   //查看目标棋子是否在两个棋子之间
				{
					num++;
				}
			}
		}

	}

	/*char a[10];
	sprintf(a,"%d",num);
	MessageBox(a,"tip");*/
	return num;

}


bool HelloWorld::checkExitX(Vec2 p, Vec2 l)
{
	int num = 0;
	Vec2 d;

	bool o = true;

		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if ((p + l) == d * 2)//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;	
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //检查绿棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			
			if ((p + l) == d * 2 )  //查看棋子是否在同一列
				{
				MessageBox("棋子走位不正确", "提示");
					o = false;
			
				}
		}

		return o;

}


bool HelloWorld::checkExitM(Vec2 p, Vec2 l)   ///马  阻马脚
{
	Vec2 d;
	bool o = true;
	 

	if ((l - p) == Vec2(2, 1) || (l - p) == Vec2(2, -1))
	{
		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if ( d-p == Vec2(1,0))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(1, 0))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(1, -2) || (l - p) == Vec2(-1, -2))
	{
		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(0, -1))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(0,-1))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(-2, -1) || (l - p) == Vec2(-2, 1))
	{
		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(-1, 0))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(-1, 0))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(1, 2) || (l - p) == Vec2(-1, 2))
	{
		for (int i = 0; i < rVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(0, 1))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //检查红棋子有没有堵住
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(0, 1))//查看棋子是否在同一列
			{
				MessageBox("棋子走位不正确", "提示");
				o = false;
			}

		}
	}

	return o;
}

