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
	// 1. super init first  �̳���д������Ҫsuperһ��
	if (!Layer::init())
	{
		return false;
	}

	// auto rootNode = CSLoader::createNode("MainScene.csb");

	//  addChild(rootNode);

	auto  l1 = LabelTTF::create(UTEXT("����"), "arial", 30);
	l1->setPosition(150, 275);

	auto  l2 = LabelTTF::create(UTEXT("����"), "arial", 30);
	l2->setPosition(350, 275);
	addChild(l1);
	addChild(l2);


	isLocked = false;  //û������
	//isM = false;  //û���ƶ�
	isRed = true;   //��ɫ����
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


	//�ں�����

	for ( i = 0; i < 16; i++)
	{
		if (i < 5)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 2*i, 6,'b');
		//	rChess[i]->move(2*i, 6);
			addChild(rChess[i], 2);
		}
		if (i == 5 || i == 6)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 1 + 6 * (i - 5), 7,'p');
			//rChess[i]->move(1 + 6 * (i - 5), 7);
			addChild(rChess[i], 2);
		}
		if (i == 7||i==8)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 0 + 8 * (i - 7), 9,'c');
			//rChess[i]->move(0 + 8 * (i - 7), 9);
			addChild(rChess[i], 2);
		}
		if (i == 9 || i == 10)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 1 + 6 * (i - 9), 9,'m');
			//rChess[i]->move(1 + 6 * (i - 9), 9);
			addChild(rChess[i], 2);
		}

		if (i == 11 || i == 12)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 2 + 4 * (i - 11), 9,'x');
		//	rChess[i]->move(2 + 4 * (i - 11), 9);
			addChild(rChess[i], 2);
		}

		if (i == 13 || i == 14)
		{
			rChess[i] = Chess::createChess(UTEXT("ʿ"), 'r', 3 + 2 * (i - 13), 9,'s');
		//	rChess[i]->move(3 + 2 * (i - 13), 9);
			addChild(rChess[i], 2);
		}

		if (i == 15)
		{
			rChess[i] = Chess::createChess(UTEXT("��"), 'r', 4, 9,'j');
			//rChess[i]->move(4, 9);
			addChild(rChess[i], 2);
		}

	
	}
	for (i = 0; i < 16; i++)
	{
		rVChess.pushBack(rChess[i]);
	}



	//��������

	for ( i = 0; i < 16; i++)
	{
		
		if (i < 5)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 2 * i, 3,'b');
			//gChess[i]->move(2*i,3);

			addChild(gChess[i], 2);
		}
		if (i == 5 || i == 6)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 1 + 6 * (i - 5), 2,'p');
		//	gChess[i]->move(1 + 6 * (i - 5), 2);
			addChild(gChess[i], 2);
		}
		if (i == 7 || i == 8)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 0 + 8 * (i - 7), 0,'c');
		//	gChess[i]->move(0 + 8 * (i - 7), 0);
			addChild(gChess[i], 2);
		}
		if (i == 9 || i == 10)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 1 + 6 * (i - 9), 0,'m');
		//	gChess[i]->move(1 + 6 * (i - 9), 0);
			addChild(gChess[i], 2);
		}

		if (i == 11 || i == 12)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 2 + 4 * (i - 11), 0,'x');
		//	gChess[i]->move(2 + 4 * (i - 11), 0);
			addChild(gChess[i], 2);
		}

		if (i == 13 || i == 14)
		{
			gChess[i] = Chess::createChess(UTEXT("ʿ"), 'g', 3 + 2 * (i - 13), 0,'s');
		//	gChess[i]->move(3 + 2 * (i - 13), 0);
			addChild(gChess[i], 2);
		}

		if (i == 15)
		{
			gChess[i] = Chess::createChess(UTEXT("��"), 'g', 4, 0,'j');
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



	//�ж��Ƿ��ƶ�
	if (isLocked)
	{
		xL = (t->getLocation().x - 25) / 50;
		yL = (t->getLocation().y - 25) / 50;

		if (xL<0 || xL>8 || yL<0 || yL>9)
		{
			isLocked = false;
		}

		////�ж��Ƿ���������
		if (isRed)
		{
			for (int i = 0; i < rVChess.size(); i++)   //ת��������
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
			for (int i = 0; i < gVChess.size(); i++)   //ת��������
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
			if (isT(p, l, lChess->getType(), lChess->getName()))  //�ж��Ƿ������Ϸ�����ӹ���
			{

				///����ƶ���
				lChess->move(xL, yL);

				////�ж��Ƿ��������
				if (isRed)
				{
					for (int i = 0; i < gVChess.size(); i++)   //������ɫ������û�б��ԣ�����������������ȥ������
					{
						if (xL == gVChess.at(i)->getX() && yL == gVChess.at(i)->getY())
						{
							lChess->eat(gVChess.at(i));
							gVChess.at(i)->removeFromParent();
							gVChess.erase(i);

						//	MessageBox("�����", "��ʾ");
						}
					}
				}
				else
				{
					for (int i = 0; i < rVChess.size(); i++)   //������ɫ������û�б��ԣ����˺�����������ȥ������
					{
						if (xL == rVChess.at(i)->getX() && yL == rVChess.at(i)->getY())
						{
							lChess->eat(rVChess.at(i));
							rVChess.at(i)->removeFromParent();
							rVChess.erase(i);

							//MessageBox("�̳���", "��ʾ");
						}
					}
				}
				isLocked = false;   //�ƶ�������
				isRed = !isRed;    //ת���ƶ�������������
				draw->setPosition(Vec2(-100, -100));  //��������ʧ
			}
		}
		
	}



	//��������
	if (isRed)
	{
		
			for (int i = 0; i < rVChess.size(); i++)   //������ɫ������û�б�����
			{
				if (rVChess.at(i)->getBoundingBox().containsPoint(t->getLocation()))
				{

					lChess = rVChess.at(i);   //����ǰ����
					isLocked = true;  //������

					xL = (t->getLocation().x - 25) / 50;
					yL = (t->getLocation().y - 25) / 50;
					p = Vec2(xL, yL);
					draw->setPosition(Vec2(xL * 50 + 75, yL * 50 + 75));  //�������ƶ�


				}
			}
		
	}
		//////����������ӵ��������� ��������
	else
	{
		
			for (int i = 0; i < gVChess.size(); i++)
			{
				if (gVChess.at(i)->getBoundingBox().containsPoint(t->getLocation()))
				{

					lChess = gVChess.at(i);   //����ǰ����

					isLocked = true;  //������

					xL = (t->getLocation().x - 25) / 50;
					yL = (t->getLocation().y - 25) / 50;
					p = Vec2(xL, yL);
					draw->setPosition(Vec2(xL * 50 + 75, yL * 50 + 75));  //�������ƶ�

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





	//���
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

	//�̱�
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

	///��
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
			///��ɫ����  ��ɫ����
			///if ()   ����鿴�Ƿ���������ס
			{

			}
			return true;
	    }*/
		
	}

	///��
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



	///��
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


	


	///��ʿ
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

	//��ʿ
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

	///�콫
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

	///�̽�
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


	/////����
	if (type = 'r' && name == 'x')
	{
		if (l.y >= 5&& p.y>=5)   ////����Ϊʲô��Ҫ����p.y����ʵ�ֹ���
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
	//����
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


	MessageBox("������λ����ȷ", "��ʾ");
		return false;
}



int HelloWorld::checkExitP(Vec2 p, Vec2 l)
{
	int num = 0;
	Vec2 d;

	if (p.x == l.x && p.y != l.y)   //���������ƶ�
	{

		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.x == p.x)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.y >= p.y && d.y <= l.y)||
					(d.y <= p.y && d.y >= l.y))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //�����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.x == p.x)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.y >= p.y&&d.y <= l.y) ||
					(d.y <= p.y&&d.y >= l.y))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}
		}

	}

	if (p.y == l.y && p.x != l.x)  //���Ӻ����ƶ�
	{

		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.y == p.y)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.x >= p.x && d.x <= l.x) ||
					(d.x <= p.x && d.x >= l.x))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //�����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.y == p.y)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.x >= p.x && d.x <= l.x) ||
					(d.x <= p.x && d.x >= l.x))   //�鿴Ŀ�������Ƿ�����������֮��
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

	if (p.x == l.x && p.y != l.y)   //���������ƶ�
	{

		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.x == p.x)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.y > p.y && d.y < l.y) ||
					(d.y < p.y && d.y > l.y))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //�����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.x == p.x)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.y > p.y&&d.y < l.y) ||
					(d.y < p.y&&d.y > l.y))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}
		}

	}

	if (p.y == l.y && p.x != l.x)  //���Ӻ����ƶ�
	{

		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d.y == p.y)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.x > p.x && d.x < l.x) ||
					(d.x < p.x && d.x > l.x))   //�鿴Ŀ�������Ƿ�����������֮��
				{
					num++;
				}
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //�����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d.y == p.y)  //�鿴�����Ƿ���ͬһ��
			{
				if ((d.x > p.x && d.x < l.x) ||
					(d.x < p.x && d.x > l.x))   //�鿴Ŀ�������Ƿ�����������֮��
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

		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if ((p + l) == d * 2)//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;	
			}

		}



		for (int i = 0; i < gVChess.size(); i++)  //�����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			
			if ((p + l) == d * 2 )  //�鿴�����Ƿ���ͬһ��
				{
				MessageBox("������λ����ȷ", "��ʾ");
					o = false;
			
				}
		}

		return o;

}


bool HelloWorld::checkExitM(Vec2 p, Vec2 l)   ///��  �����
{
	Vec2 d;
	bool o = true;
	 

	if ((l - p) == Vec2(2, 1) || (l - p) == Vec2(2, -1))
	{
		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if ( d-p == Vec2(1,0))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(1, 0))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(1, -2) || (l - p) == Vec2(-1, -2))
	{
		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(0, -1))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(0,-1))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(-2, -1) || (l - p) == Vec2(-2, 1))
	{
		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(-1, 0))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(-1, 0))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}
	}

	if ((l - p) == Vec2(1, 2) || (l - p) == Vec2(-1, 2))
	{
		for (int i = 0; i < rVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = rVChess.at(i)->getX();
			d.y = rVChess.at(i)->getY();
			if (d - p == Vec2(0, 1))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}

		for (int i = 0; i < gVChess.size(); i++)  //����������û�ж�ס
		{
			d.x = gVChess.at(i)->getX();
			d.y = gVChess.at(i)->getY();
			if (d - p == Vec2(0, 1))//�鿴�����Ƿ���ͬһ��
			{
				MessageBox("������λ����ȷ", "��ʾ");
				o = false;
			}

		}
	}

	return o;
}

