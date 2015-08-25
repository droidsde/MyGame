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

	bool isExist[8][9];  //��¼�������ǲ��������Ӵ���



    CREATE_FUNC(HelloWorld);


	Chess* rChess[16];   // ������
	Chess* gChess[16];   //������

	Vector<Chess*> rVChess;
	Vector<Chess*> gVChess;

	/// char* name[7] = {"��","��","��","��","��","ʿ","��"};


	Chess* pChess;  // ������ǰ���Ǹ�����
	Chess* lChess;  // �ƶ�����Ǹ�����
	int xL, yL;

	bool isLocked;  //�Ƿ�����һ������
	//bool isM;  //�Ƿ��ƶ�һ������

	bool isRed;  //�Ƿ��Ǻ�ɫ

	Vec2 p; //ǰʸ��
	Vec2 l;  //��ʸ��
	DrawNode* draw;

	bool isT(Vec2 p,Vec2 l,char type,char name);   //�Ƿ����(ǰʸ������ʸ�������Ӻ������� ��������)


	
	int checkExitP(Vec2 p,Vec2 l);   /// �� ����м��Ƿ�������
	int checkExitC(Vec2 p, Vec2 l);   ///�� ����м��Ƿ�������
	bool checkExitM(Vec2 p, Vec2 l);   ///��  �����
	bool checkExitX(Vec2 p, Vec2 l);   ///��  �����

};

#endif // __HELLOWORLD_SCENE_H__
