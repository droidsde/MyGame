#include "Snake.h"

Snake* Snake::createSnake(Vec2 dir)
{
	auto snake = new Snake();
	snake->initSnake(dir);
	snake->autorelease();
	return snake;

}

bool Snake::initSnake(Vec2 dir)
{
	//gameLayer = layer;
	sDir = dir;
	snakes.pushBack(SnakeNode::createNode(2, 4));
	snakes.pushBack(SnakeNode::createNode(2, 3));
	snakes.at(0)->sNode->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::YELLOW);
	//snakes.pushBack(SnakeNode::createNode(2, 3, Vec2(0, 1)));
	//snakes.pushBack(SnakeNode::createNode(2, 2, Vec2(0, 1)));
	//snakes.pushBack(SnakeNode::createNode(2, 1, Vec2(0, 1)));

	

	for (int i = 0; i < snakes.size(); i++)
	{
		//snakes.at(i)->setColor(Color3B::RED);
		addChild(snakes.at(i));


	}


	//schedule(schedule_selector(Snake::update), 1.0f);
	return true;


}


void Snake::setDir(Vec2 dir)
{
	sDir = dir;
}

void Snake::goDir()
{
	for (int i = 1; i < snakes.size(); i++)
	{
		snakes.at(snakes.size() - i)->setPosition(snakes.at(snakes.size() - i - 1)->getPosition());
	}
	snakes.at(0)->setPosition(snakes.at(0)->getPosition() + sDir * 50);
}

//void Snake::update(float dt)
//{
//	//this->goDir();
//}

///要记录以前和现在的向量
///实现不能反着走
///实现不能自己吃自己
//实现不能撞墙
//实现不能吃东西


void Snake::eat(SnakeNode* egg)
{
	snakes.insert(0, egg);
	snakes.at(0)->sNode->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::YELLOW);
	snakes.at(1)->sNode->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::BLUE);

}

bool Snake::checkEat(SnakeNode* egg)
{
	if ((snakes.at(0)->getPosition() + this->getDir()*50) == egg->getPosition())
		return true;
}

Vec2 Snake::getDir()
{
	return sDir;
}


bool Snake::isOut()
{
	int x = snakes.at(0)->getPosition().x;
	int y = snakes.at(0)->getPosition().y;
	if (x < 50 || x>300||y<50||y>500)
	{
		return false;
	}

	return true;
}

bool Snake::touchItself()
{
	Vec2 a = snakes.at(0)->getPosition();
	for (int i = 1; i < snakes.size(); i++)
	{
		if (a == snakes.at(i)->getPosition())
		{
			//MessageBox("Boom", "tip");
			return true;
		}
	}
	return false;
}
