

#include "Chess.h"

Chess* Chess::createChess(std::string name, char type, int x, int y,char cname)
{
	auto chess = new Chess();
	chess->initChess( name,type,  x,  y,cname);
	chess->autorelease();
	return chess;
}

bool Chess::initChess(std::string name, char type, int x, int y,char cname)
{
	////通过文字标签来标记棋子先

	
	Sprite::init();


	move(x, y);
	cName = cname;
	cType = type;

	if (type == 'r')
	{
		this->setTexture("rChess.png");
	}
	else
	{
		this->setTexture("gChess.png");
	}

	auto size = this->getContentSize();
	auto  chessType= LabelTTF::create(name, "arial", 28);
	chessType->setColor(Color3B::BLACK);
	chessType->setAnchorPoint(Vec2(0.5, 0.5));
	chessType->setPosition(size.width / 2, size.height / 2);
	addChild(chessType);
	
	this->setAnchorPoint(Vec2(0, 0));
	//this->setPosition(Vec2((x+2)*50,(y+2)*50));
	
	return true;
}


void Chess::move(int x,int y)
{
	xL = x;
	yL = y;
	this->setPosition(Vec2(xL * 50 +25, yL * 50 + 25));
}


int Chess::getX()
{
	return xL;
}

int Chess::getY()
{
	return yL;
}

char Chess::getName()
{
	return cName;
}

char Chess::getType()
{
	return cType;
}

void Chess::eat(Chess *e)
{
	//e->setVisible(false);
	//e->removeFromParent();
//	MessageBox("吃了"+e->getName(),"提示");
	if (e->getName() == 'j')
	{
		MessageBox("恭喜你,你赢了", "提示");
	}
}
