#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;

class GameClient :public LayerColor
{
private:
	Size size;
	Button* btnS;
	Button* btnE;
	LabelTTF* title;
public:
	static Scene* createScene();

	virtual bool init();  //初始化

	void sTouchEvent(Ref *pSender, Widget::TouchEventType type);
	void eTouchEvent(Ref *pSender, Widget::TouchEventType type);

	CREATE_FUNC(GameClient);

};