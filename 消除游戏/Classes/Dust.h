///������

#ifndef DUST_H
#define DUST_H

#include "cocos2d.h"
USING_NS_CC;

class Dust:public NodeGrid
{
public:
	static Dust* createByType(int x,int y,int type);
	bool initWithType(int x,int y, int type);
	void setPos();

	void crush();
	
	bool isSwaping() { return m_isSwaping; }
	bool isCrushing() { return m_isCrushing; }

	void setSwapingState(bool state) { m_isSwaping = state; }


	void setX(int x) { m_x = x;}
	void setY(int y) {	m_y = y;}
	int getX()       {	return m_x;}
	int getY()       {	return m_y;}

	void setType(int type){	m_type = type;}

	int getType()    { return m_type;}

	//void setStr();

	//LabelTTF* id;  //�������

	
private:
	int m_x, m_y,m_type; // x,y�������� ��1-8�� 1-8��

	bool m_isSwaping, m_isCrushing; //������ڽ���������
};

#endif;