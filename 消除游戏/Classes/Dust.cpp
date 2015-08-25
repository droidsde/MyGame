#include "Dust.h"
#include "GameScene.h"

Dust* Dust::createByType(int x,int y,int type)
{
	Dust* dust = new Dust();
	dust->initWithType(x,y,type);
	dust->autorelease();
	return dust;
}

bool Dust::initWithType(int x, int y, int type)
{
	NodeGrid::init();

	this->setAnchorPoint(Vec2(0,0));


	m_x = x;
	m_y = y;
	m_type = type;

	auto sp = Sprite::create();
	__String *tn = __String::createWithFormat("d%d.png",type);
	sp->setTexture(tn->getCString());
	sp->setAnchorPoint(Vec2(0, 0));
	addChild(sp);

	setPos();

	/*id = LabelTTF::create(__String::createWithFormat("%d,%d",m_x,m_y)->getCString(),"arial",24);
	id->setColor(Color3B::BLACK);
	id->setPosition(25, 25);
	addChild(id);*/



	return true;
}

void Dust::setPos()
{
	this->setPosition(Vec2(m_x*50,m_y*50));
}

void Dust::crush()
{
	GameScene::getScore();
	//开始消除，消除状态为真，直到消除动作结束，将尘粒移除渲染节点，并置消除状态为假
	m_isCrushing = true;
	
	auto action1 = Waves3D::create(0.3f, Size(50, 50), 5, 10);
	//auto action1 = Shaky3D::create(0.5f, Size(50, 50), 5, false);
	auto action2 = FadeOut::create(0.1);
	
	auto call = CallFunc::create([this](){
		this->removeFromParent();
		m_isCrushing = false;
		
	});
	this->runAction(Sequence::create(action1,action2, call, nullptr));
}

//void Dust::setStr()
//{
//	id->setString(__String::createWithFormat("%d,%d",this->getX(),this->getY())->getCString());
//}