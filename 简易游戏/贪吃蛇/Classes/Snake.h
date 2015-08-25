#include "cocos2d.h"
#include "SnakeNode.h"

USING_NS_CC;

class Snake :public Sprite
{
public:
	static Snake* createSnake(Vec2 dir);

	bool initSnake(Vec2 dir);

//	void update(float dt);

	void setDir(Vec2 dir);

	void goDir();

	Vec2 getDir();

	void eat(SnakeNode* egg); //³Ôµ°

	bool isOut();
	
	bool touchItself();

	bool checkEat(SnakeNode* egg);

	

private:
	Vector<SnakeNode*> snakes;
	Vec2 sDir;
//	Layer* gameLayer;
};