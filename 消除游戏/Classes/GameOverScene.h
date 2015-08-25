#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameOver:public Layer
{
public:
	static Scene* createScene();
	bool init();

	void onMenuItem(Ref* sender);

	CREATE_FUNC(GameOver);
};

#endif;