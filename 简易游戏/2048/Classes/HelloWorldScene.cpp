#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MeshBoard.h"


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
    
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4; j++)
	{
		blocks[i][j] = Block::createBlock(0,Vec2(i,j));
		addChild(blocks[i][j]);
	}

	isMove = false;

	//blocks[0][0]->setNumber(2);

	//blocks[0][1]->setNumber(2);

	//blocks[1][2]->setNumber(2);

	//blocks[1][1]->setNumber(2);

	//blocks[2][2]->setNumber(2);

	createBlockNumber();

	auto mesh = MeshBoard::create();
	
	addChild(mesh);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan,this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    return true;
}


bool HelloWorld::touchBegan(Touch* t, Event* e)
{
	bP = t->getLocation();
	return true;
}

void HelloWorld::touchEnded(Touch* t, Event* e)
{
	eP = t->getLocation();

	Vec2 d = eP - bP;

	//if (d.x>)
	if (d.x >= 0 && d.y >= 0)
	{
		if (d.x > d.y)
		{
			dir = 'r';
		}
		
		else
		{
			dir = 'u';
		}
	}
	if (d.x<0 && d.y>0)
	{
		if (abs(d.x) > d.y)
		{
			dir = 'l';
		}
		else
		{
			dir = 'u';
		}
	}

	if (d.x<=0 && d.y<=0)
	{
		if (abs(d.x) > abs(d.y))
		{
			dir = 'l';
		}
		else
		{
			dir = 'd';
		}
	}

	if (d.x>0 && d.y<0)
	{
		if (d.x > abs(d.y))
		{
			dir = 'r';
		}
		else
		{
			dir = 'd';
		}
	}

	switch (dir)
	{
	case 'u':
		goUp();
		
		break;

	case 'd':
		goDown();
		
		break;

	case 'l':
		goLeft();
		break;

	case 'r':
		goRight();
		break;


	}
	if (isMove == true)
	{
		createBlockNumber();
	}
}


bool HelloWorld::goUp()
{
	isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >=0 ; y--)
		{
			for (int y1 = y - 1; y1 >= 0 ; y1--)
			{
				if (blocks[x][y1]->getNumber() > 0)
				{
					if (blocks[x][y]->getNumber() == 0)
					{
						blocks[x][y]->setNumber(blocks[x][y1]->getNumber());
						blocks[x][y1]->setNumber(0);
						y++;  //??  可以确定在空白之后确定能不能抵消
						isMove = true;
					}

					else if (blocks[x][y]->getNumber() == blocks[x][y1]->getNumber())
					{
						blocks[x][y]->setNumber(blocks[x][y1]->getNumber() * 2);
						blocks[x][y1]->setNumber(0);
						isMove = true;
					}
					break; 
				}
			
			}
		}
	}
	return isMove;
}

bool HelloWorld::goDown()
{
	isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y <4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (blocks[x][y1]->getNumber() > 0)
				{
					if (blocks[x][y]->getNumber() == 0)
					{
						blocks[x][y]->setNumber(blocks[x][y1]->getNumber());
						blocks[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}

					else if (blocks[x][y]->getNumber() == blocks[x][y1]->getNumber())
					{
						blocks[x][y]->setNumber(blocks[x][y1]->getNumber() * 2);
						blocks[x][y1]->setNumber(0);
						isMove = true;
					}
					break;
				}

			}
		}
	}
	return isMove;
}

bool HelloWorld::goLeft()
{
	isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x<4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (blocks[x1][y]->getNumber() > 0)
				{
					if (blocks[x][y]->getNumber() == 0)
					{
						blocks[x][y]->setNumber(blocks[x1][y]->getNumber());
						blocks[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}

					else if (blocks[x][y]->getNumber() == blocks[x1][y]->getNumber())
					{
						blocks[x][y]->setNumber(blocks[x1][y]->getNumber() * 2);
						blocks[x1][y]->setNumber(0);
						isMove = true;
					}
					break;
				}

			}
		}
	}
	return isMove;
}

bool HelloWorld::goRight()
{
	isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x>=0; x--)
		{
			for (int x1 = x - 1; x1 >=0; x1--)
			{
				if (blocks[x1][y]->getNumber() > 0)
				{
					if (blocks[x][y]->getNumber() == 0)
					{
						blocks[x][y]->setNumber(blocks[x1][y]->getNumber());
						blocks[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}

					else if (blocks[x][y]->getNumber() == blocks[x1][y]->getNumber())
					{
						blocks[x][y]->setNumber(blocks[x1][y]->getNumber() * 2);
						blocks[x1][y]->setNumber(0);
						isMove = true;
					}
					break;
				}

			}
		}
	}
	return isMove;
}

void HelloWorld::createBlockNumber()
{
	int i, j;
	while (1)
	{
		i = CCRANDOM_0_1() * 4;
		j = CCRANDOM_0_1() * 4;

		if (blocks[i][j] ->getNumber() == 0)
		{
			blocks[i][j]->setNumber(CCRANDOM_0_1() * 10 > 1 ? 2 : 4);
			break;
			//blocks[i][j]->setNumber(2);
		}

		if (!canCreateBlock()) {
			break;
		}
	}
}

bool HelloWorld::canCreateBlock()
{
	bool isCreate = false;
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4; j++)
	{
		if (blocks[i][j] ->getNumber() == 0)
		{
			isCreate = true;
			break;
		}
	}
	return isCreate;
}