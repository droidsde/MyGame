///尘粒的布局类
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
	static DustGrid* create(int row,int col);  //通过行和列来确定布局
	bool init(int row, int col);
	Dust* createADust(int row,int col);  //创建一粒新尘粒
	bool isDustLegal(Dust* dust, int x, int y); ///判断尘粒是否合法
	bool onTouchBegan(Touch *t, Event *e);  //作为回调函数

	void onTouchMoved(Touch *t, Event *e);  ///作为回调函数
	void swapDusts(Dust *a,Dust *b);  //交换选中和被选中的尘粒
	void moveToNewPosition(Dust* d);
	void updateMap();  //重新加载地图
	bool isDeadMap();   //是否是死地图


	bool canCrush();   //判断是否能消除
	void goCrush();     //开始消除
	void refreshDustsGrid();
	void refreshDustsToNewPos(int col);

	//捕捉函数
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
	vector<vector<Dust*>>  m_DustsBox;  //存放尘粒的容器
	Vector<Dust*> m_crushDustBox;  //准备消除的尘粒容器
	Vector<Dust*> m_newDustBox;   //准备加入布局的尘粒容器

	int m_row, m_col;
	Dust *m_selectedDust, *m_swapedDust;

//	LabelTTF* nl;  //


	
};

#endif;