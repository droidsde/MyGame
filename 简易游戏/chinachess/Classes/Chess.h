#include "Cocos2d.h"

USING_NS_CC;

//棋子类  封装棋子名字   棋子某方  棋子位置

class Chess: public Sprite
{
	
public:
	
	static Chess* createChess(std::string name,char type,int x,int y,char cname);

	virtual bool initChess(std::string name, char type, int x, int y,char cname);

	void move(int x, int y);

	int getX();
	int getY();

	void eat(Chess *e);

	char getName();
	char getType();

private:
	int xL, yL;  //棋子在棋盘上的位置
	char cName;  //棋子的种类
	char cType;
	/*static Chess* createChess();

	virtual bool initChess();*/
};
