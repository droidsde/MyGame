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

	Sprite* _stone[4];  //������ʯͷ

	Vector<Sprite*> _notReach; //��¼�����ʯͷ

	bool stonePush[4];  //��¼�Ŀ�ʯͷ����

	TMXLayer *_collidable;

	Vec2 _startPos;  //��ʼ����
	char dir;                  //����


	cocos2d::Vec2 _des[4];  //��¼Ŀ�ĵ�����

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

	bool isPush(Vec2 &pos);   ///�ж���û���ƶ�ʯͷ

	void pushStone();  //�ƶ�ʯͷ

	void checkSucess();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
