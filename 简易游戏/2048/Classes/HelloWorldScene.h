#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{

private:
	Size size;
	
	Vec2 bP;
	Vec2 eP;

	bool isMove;

	Block* blocks[4][4];
	char dir;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	bool touchBegan(Touch* t,Event* e);

	void touchEnded(Touch* t, Event* e);


	bool goUp();

	bool goDown();

	bool goLeft();

	bool goRight();

	void createBlockNumber();

	bool canCreateBlock();

    // implement the "static create()" method manually
     CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
