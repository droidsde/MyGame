#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	TMXTiledMap *_tileMap;

	Sprite *_player;

	Sprite* _stone[4];  //保存块个石头

	Vector<Sprite*> _notReach; //记录到达的石头

	bool stonePush[4];  //记录哪块石头被推

	TMXLayer *_collidable;

	Vec2 _startPos;  //开始触摸
	char dir;                  //方向


	cocos2d::Vec2 _des[4];  //记录目的地坐标

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	void setPlayerPosition(Vec2 pos);

	bool isCollideWall(Vec2 position);

	cocos2d::Vec2 move(char dir);


	cocos2d::Vec2 tileCoordFromPosition(Vec2 position);

	bool isPush(Vec2 &pos);   ///判断有没有推动石头

	void pushStone();  //推动石头

	void checkSucess();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
