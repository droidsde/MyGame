//
//  Hero.cpp
//  NoOneDies
//
//  Created by plter on 14-6-2.
//
//

#include "Hero.h"
#include "FlashTool.h"


bool Hero::init(){
    Sprite::init();
    
    Size s = Size(44, 52);
    
    runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json", 0.2f)));
    
	PhysicsMaterial a;
	a.density = 1.0;
	a.friction = 0.5;
	a.restitution = 0.0;

	auto body = PhysicsBody::createBox(s,a);

	

    setPhysicsBody(body);
    setContentSize(s);
    
//	setTextureRect(Rect(0, 0, 44, 52));
//	setColor(Color3B::WHITE);
    getPhysicsBody()->setRotationEnable(false);
	//getPhysicsBody()->setDynamic(false);
    //getPhysicsBody()->setContactTestBitmask(1);
	//getPhysicsBody()->setContactTestBitmask(2);
//	getPhysicsBody()->setEnable(false);
	//setEnable
	//getPhysicsBody()->setGravityEnable(false);
	//getPhysicsBody()->getShape(0)->setRestitution(0.1);
//	getPhysicsBody()->getShape(0)->setFriction(1.0);
    return true;
}


void Hero::move(char dir)
{
	switch (dir)
	{
		case 'l':
			this->getPhysicsBody()->setVelocity(Vec2(-100,0));
			this->runAction(FlipX::create(true));
			break;

		case 'r':
			this->getPhysicsBody()->setVelocity(Vec2(100,0));
			this->runAction(FlipX::create(false));
			break;
	}
}