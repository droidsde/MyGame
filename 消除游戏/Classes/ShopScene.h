#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

class ShopScene:public Layer
{
public:
	static Scene* createScene();
	bool init();
	
	void onTouchBack(Ref* ref,Widget::TouchEventType type);
	CREATE_FUNC(ShopScene);


private:
};



#endif;