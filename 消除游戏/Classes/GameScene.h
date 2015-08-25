#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "DustGrid.h"

USING_NS_CC;
using namespace ui;

class GameScene :public Layer
{
public:
	static Scene* createScene();

	static void getScore();
	bool init();

	void publishScore();
	void onReducingScore(float dt);

	void onToolMenu(Ref* ref);

	void onSettingCallBack(Ref *ref, Widget::TouchEventType type);
	CREATE_FUNC(GameScene);

private:
	static Label* m_recordScore;
	static int m_score;
	static LoadingBar* m_bonusbar;

	//技能的数量
	Label* m_tool1;
	Label* m_tool2;
	Label* m_tool3;

	int m_num1;
	int m_num2;
	int m_num3;
	DustGrid* dustgrid;

	bool isPause;
};

#endif;