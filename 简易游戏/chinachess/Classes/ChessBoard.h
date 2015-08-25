#include "cocos2d.h"


USING_NS_CC;

class ChessBoard :public Layer
{
	public:
	virtual bool init();   //虚方法可以继承，也可以在子类里面直接重写
	CREATE_FUNC(ChessBoard);
};