#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;


//////////����
class GameController : public Ref
{
private:

	Chess* rChess[16];        ///��ɫ����
	Chess* gChess[16];        //��ɫ����

	Vector<Chess*> rVChess;   //װ���������
	Vector<Chess*> gVChess;   //װ���������

	Layer* gameLayer;         //��Ϸ����





public:
	static GameController* createGame(Layer &layer);   //��̬����������Ϸ
	
	bool initGame();   ///��ʼ����Ϸ

	void resetName();  //������Ϸ    ������������

	void resetChessBoard();
	 
private:
};
