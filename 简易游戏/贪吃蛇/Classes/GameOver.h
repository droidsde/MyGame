#include "cocos2d.h"

#include "ui/CocosGUI.h"
//#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;

USING_NS_CC;
class GameOver :public LayerColor
{

private:
	Size visibleSize;

public:
	virtual bool init();

	void touchEvent(Ref *pSender, Widget::TouchEventType type);

	CREATE_FUNC(GameOver);

	static Scene* createScene();

};