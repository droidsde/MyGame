#include "SnakeNode.h"

SnakeNode* SnakeNode::createNode(int x, int y)
{
	auto snakenode = new SnakeNode();
	snakenode->initNode(x, y);

	snakenode->autorelease();
	return snakenode;
}


bool SnakeNode::initNode(int x, int y)
{
	if (!Sprite::init())
	{
		return false;
	}


	sNode = DrawNode::create();

	sNode->drawSolidRect(Vec2(0, 0), Vec2(50, 50), Color4F::BLUE);

	addChild(sNode);

	this->setPos(x, y);


	//nx = x;
	//ny = y;
	//nDir = dir;

	//schedule(schedule_selector(SnakeNode::update),1.0f);
	return true;

}


void SnakeNode::setPos(int x,int y)
{
	this->setPosition(x*50,y*50);
}


//void SnakeNode::move(Vec2 dir)
//{
//	this->setPosition(this->getPosition()+dir*50);
//	this->nx += dir.x;
//	this->ny += dir.y;
//
//	//if (nx<=1 || nx>=7 || ny<=1 || ny>=10)
//	//{
//	//	
//	////	unschedule(schedule_selector(SnakeNode::update));
//	//	//MessageBox("出界", "提示");
//	//	MessageBox("出界", "提示");   //蛇头出界要注意
//	//}
//
//}

//void SnakeNode::update(float dt)
//{
//	move(nDir);
//}




//void SnakeNode::setDir(Vec2 newDir)
//{
//	nDir = newDir;
//}
//
//Vec2 SnakeNode::getDir()
//{
//	return nDir;
//}

////设置节点
//void SnakeNode::setNodeColor(Color3B color)
//{
//	sNode->setColor(color);
//}