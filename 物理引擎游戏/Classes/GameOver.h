
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "cocos2d.h"

USING_NS_CC;

class GameOver:public LayerColor
{
public:

	static Scene* createScene();
	bool init();
	void onMenuCallBack(Ref* ref);
	
	CREATE_FUNC(GameOver);
};

#endif;