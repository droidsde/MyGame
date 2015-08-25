#ifndef BLOCK_H
#define BLOCK_H

#include "cocos2d.h"

USING_NS_CC;

class  Block :public Sprite
{

private:
	Size _size;
public:
	virtual bool init();
	CREATE_FUNC(Block);
	void update(float dt);

};

#endif;