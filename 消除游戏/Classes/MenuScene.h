#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "cocos2d.h"

USING_NS_CC;


class MenuScene:public Layer
{
private:


public:
	static Scene* createScene();
	bool init();


	void onMenuEvent(Ref* sender);

	CREATE_FUNC(MenuScene);
};

#endif