#include "cocos2d.h"
#include "string"

USING_NS_CC;
using namespace std;

class Block :public Sprite
{
private:
	//Size size;
	//float side;
	Vec2 position;  //格子作为坐标

	int number;  //  实时的块的分数

	Label* label;

public:
	static Block* createBlock(int num,Vec2 pos);
	
	 bool initWithArgs(int num,Vec2 pos);   //初始化块的颜色， 数字

	//string getPointString();

	//void go(char dir);

	//void move(char dir);
	void setPos(Vec2 pos);  //处于什么位置

	Vec2 getPos();

	int getNumber();

	void setNumber(int num);




	//bool isEat(Block* b);  //能不能吃


	//void eat(Block* b);    //吞并

	//int getX();
	//int getY();

	//void setX(int x);
	//void setY(int y);


};