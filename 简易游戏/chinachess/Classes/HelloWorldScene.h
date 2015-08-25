#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Chess.h"
//#include "ToC.h"

using namespace std;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();


	virtual bool  onTouchBegan(Touch *t, Event *e);

	virtual void  onTouchMoved(Touch *t, Event *e);

	virtual void  onTouchEnded(Touch *t, Event *e);


    // implement the "static create()" method manually

	bool isExist[8][9];  //记录棋盘上是不是有棋子存在



    CREATE_FUNC(HelloWorld);


	Chess* rChess[16];   // 红棋子
	Chess* gChess[16];   //绿棋子

	Vector<Chess*> rVChess;
	Vector<Chess*> gVChess;

	/// char* name[7] = {"兵","车","马","炮","相","士","将"};


	Chess* pChess;  // 被锁定前的那个棋子
	Chess* lChess;  // 移动后的那个棋子
	int xL, yL;

	bool isLocked;  //是否锁定一个棋子
	//bool isM;  //是否移动一个棋子

	bool isRed;  //是否是红色

	Vec2 p; //前矢量
	Vec2 l;  //后矢量
	DrawNode* draw;

	bool isT(Vec2 p,Vec2 l,char type,char name);   //是否合理(前矢量，后矢量，棋子红蓝方， 棋子名称)


	
	int checkExitP(Vec2 p,Vec2 l);   /// 炮 检查中间是否有棋子
	int checkExitC(Vec2 p, Vec2 l);   ///车 检查中间是否有棋子
	bool checkExitM(Vec2 p, Vec2 l);   ///马  阻马脚
	bool checkExitX(Vec2 p, Vec2 l);   ///相  阻马脚

};

#endif // __HELLOWORLD_SCENE_H__
