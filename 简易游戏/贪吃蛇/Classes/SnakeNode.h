#include "cocos2d.h"

USING_NS_CC;

class SnakeNode:public Sprite
{
public:

	static SnakeNode*  createNode(int x,int y);
	bool initNode(int x, int y);

	void setPos(int x, int y);
	//void move(Vec2 dir);  //运动

//	void update(float dt);

	//void setDir(Vec2 newDir);
	//Vec2 getDir();

	//void eat(SnakeNode* egg);

	//int getX();
	//int getY();

	//void setNodeColor(Color3B color);
	 

//	CREATE_FUNC(SnakeNode);
	DrawNode* sNode;
private:
	//int nx; //节点x坐标
	//int ny; //节点y坐标
//	Vec2 nDir; //节点运动方向

	
	//SnakeNode* egg;
	//Vec2 pDir; //初始向量
};
