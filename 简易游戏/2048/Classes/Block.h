#include "cocos2d.h"
#include "string"

USING_NS_CC;
using namespace std;

class Block :public Sprite
{
private:
	//Size size;
	//float side;
	Vec2 position;  //������Ϊ����

	int number;  //  ʵʱ�Ŀ�ķ���

	Label* label;

public:
	static Block* createBlock(int num,Vec2 pos);
	
	 bool initWithArgs(int num,Vec2 pos);   //��ʼ�������ɫ�� ����

	//string getPointString();

	//void go(char dir);

	//void move(char dir);
	void setPos(Vec2 pos);  //����ʲôλ��

	Vec2 getPos();

	int getNumber();

	void setNumber(int num);




	//bool isEat(Block* b);  //�ܲ��ܳ�


	//void eat(Block* b);    //�̲�

	//int getX();
	//int getY();

	//void setX(int x);
	//void setY(int y);


};