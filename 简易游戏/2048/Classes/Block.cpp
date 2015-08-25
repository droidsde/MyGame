

#include "Block.h"

Block* Block::createBlock(int num,Vec2 pos)

{
	Block* block = new Block();
	block->initWithArgs( num, pos);

		block->autorelease();
		return block;

}


///初始化块的参数
bool Block::initWithArgs(int num,Vec2 pos)
{

	if (!Sprite::init())
	{
		return false;
	}
	
	

	setContentSize(Size(100,100));
	setTextureRect(Rect(0,0,100,100));

    label = Label::create();

	label->setSystemFontSize(36);

	addChild(label);
	label->setPosition(Vec2(50,50));
	
	setPos(pos);
	setNumber(num);

	return true;
}


void Block::setNumber(int num)
{
	number = num;
	
	label->setString(__String::createWithFormat("%d", number)->getCString());
	switch (number)
	{

	case 0:
		this->setColor(Color3B::WHITE);
		label->setString("");
		break;

	case 2:
		this->setColor(Color3B::RED);
		break;
	case 4:
		this->setColor(Color3B::BLUE);
		break;
	case 8:
		this->setColor(Color3B::GREEN);
		break;
	case 16:
		this->setColor(Color3B::ORANGE);
		break;
	case 32:
		this->setColor(Color3B::ORANGE);
		break;
	case 64:
		this->setColor(Color3B::ORANGE);
		break;
	case 128:
		this->setColor(Color3B::MAGENTA);
		break;
	case 256:
		this->setColor(Color3B::YELLOW);
		break;
	case 512:
		this->setColor(Color3B::GRAY);
		break;
	case 1024:
		this->setColor(Color3B::BLACK);
		break;
	case 2048:
		this->setColor(Color3B::ORANGE);
		break;
	}

}

int Block::getNumber()
{
	return number;
}

void Block::setPos(Vec2 pos)
{
	position = pos;

	this->setPosition((position + Vec2(1,1))* 100);
}

Vec2 Block::getPos()
{
	return position;
}