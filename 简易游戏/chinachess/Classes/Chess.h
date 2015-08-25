#include "Cocos2d.h"

USING_NS_CC;

//������  ��װ��������   ����ĳ��  ����λ��

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
	int xL, yL;  //�����������ϵ�λ��
	char cName;  //���ӵ�����
	char cType;
	/*static Chess* createChess();

	virtual bool initChess();*/
};
