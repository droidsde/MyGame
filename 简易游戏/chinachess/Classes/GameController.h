#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;


//////////该类
class GameController : public Ref
{
private:

	Chess* rChess[16];        ///红色棋子
	Chess* gChess[16];        //绿色棋子

	Vector<Chess*> rVChess;   //装红棋的容器
	Vector<Chess*> gVChess;   //装绿棋的容器

	Layer* gameLayer;         //游戏界面





public:
	static GameController* createGame(Layer &layer);   //静态方法创造游戏
	
	bool initGame();   ///初始化游戏

	void resetName();  //重新游戏    重新设置棋子

	void resetChessBoard();
	 
private:
};
