#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Hero.h"
#include "Block.h"
USING_NS_CC;

class GameScene :public LayerColor
{
private:
	Size _size;
	Vec2 startPos;
	Hero* h;
	LabelTTF* score;
	LabelTTF* nowScore;
	int s;
public:
	static Scene* createScene();
	virtual bool init();

	void blockUpdate(float dt);

	void failUpdate(float dt);

	void createABlock();

	virtual bool onTouchBegan(Touch* t, Event* e);
	virtual void onTouchMoved(Touch* t, Event* e);
	virtual void onTouchEnded(Touch* t, Event* e);



	CREATE_FUNC(GameScene);
};

#endif;