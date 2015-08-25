///�����Ĳ�����
#ifndef DUSTGRID_H
#define DUSTGRID_H

#include "cocos2d.h"
#include "Dust.h"
#include <vector>
USING_NS_CC;
using namespace std;

#define GridWidth 50
#define MoveTime 0.5

class DustGrid :public Node
{
public:
	static DustGrid* create(int row,int col);  //ͨ���к�����ȷ������
	bool init(int row, int col);
	Dust* createADust(int row,int col);  //����һ���³���
	bool isDustLegal(Dust* dust, int x, int y); ///�жϳ����Ƿ�Ϸ�
	bool onTouchBegan(Touch *t, Event *e);  //��Ϊ�ص�����

	void onTouchMoved(Touch *t, Event *e);  ///��Ϊ�ص�����
	void swapDusts(Dust *a,Dust *b);  //����ѡ�кͱ�ѡ�еĳ���
	void moveToNewPosition(Dust* d);
	void updateMap();  //���¼��ص�ͼ
	bool isDeadMap();   //�Ƿ�������ͼ


	bool canCrush();   //�ж��Ƿ�������
	void goCrush();     //��ʼ����
	void refreshDustsGrid();
	void refreshDustsToNewPos(int col);

	//��׽����
	void onDustsSwaping(float dt);
	void onDustsSwapingBack(float dt);
	void onDustsCrushing(float dt);
	void onDustsRefreshing(float dt);

	void onCountNew(float dt);
	
	void setTool(int type);
	void checkTool();

	bool tool1;
	bool tool2;

	int getRow()	{ return m_row; }
	int getCol()    { return m_col; }

private:
	vector<vector<Dust*>>  m_DustsBox;  //��ų���������
	Vector<Dust*> m_crushDustBox;  //׼�������ĳ�������
	Vector<Dust*> m_newDustBox;   //׼�����벼�ֵĳ�������

	int m_row, m_col;
	Dust *m_selectedDust, *m_swapedDust;

//	LabelTTF* nl;  //


	
};

#endif;