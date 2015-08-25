#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "GameWin.h"
Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//auto rootNode = CSLoader::createNode("MainScene.csb");

	//addChild(rootNode);

	_tileMap = TMXTiledMap::create("map/boxMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap man = group->getObject("pushMan");

	float x = man["x"].asFloat();
	float y = man["y"].asFloat();



	_player = Sprite::create("pushMan.png");
	_player->setAnchorPoint(Vec2(0, 1));
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2, 200);

	for (int i = 0; i < 4; i++)
	{
		stonePush[i] = false;

		ValueMap stone = group->getObject(__String::createWithFormat("stone%d", i)->getCString());
		float x1 = stone["x"].asFloat();
		float y1 = stone["y"].asFloat();
		_stone[i] = Sprite::create("stone.png");
		_stone[i]->setAnchorPoint(Vec2(0, 1));
		_stone[i]->setPosition(Vec2(x1, y1));
		addChild(_stone[i], 2, 200);

		_notReach.pushBack(_stone[i]);

		ValueMap des = group->getObject(__String::createWithFormat("des%d", i)->getCString());
		float x2 = des["x"].asFloat();
		float y2 = des["y"].asFloat();

		_des[i].x = x2;
		_des[i].y = y2;

	}

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//MessageBox(__String::createWithFormat("%f", _des[0].x)->getCString(), "kk");
	return true;
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	_startPos = touch->getLocation();
	return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Vec2 touchLocation = touch->getLocation();

	Vec2 playerPos = _player->getPosition();

	//Vec2 stonePos = _stone->getPosition();

	Vec2 diff = touchLocation - _startPos;

	///确定移动方向
	if (abs(diff.x)>abs(diff.y))
	{
		if (diff.x > 0)  { dir = 'r';    playerPos.x += _tileMap->getTileSize().width; _player->runAction(FlipX::create(true)); }
		else             { dir = 'l';    playerPos.x -= _tileMap->getTileSize().width; _player->runAction(FlipX::create(false)); }
	}
	else
	{
		if (diff.y > 0)  { dir = 'u';    playerPos.y += _tileMap->getTileSize().height; }
		else             { dir = 'd';    playerPos.y -= _tileMap->getTileSize().height; }
	}


	if (isPush(playerPos))  //判断和那个石头相撞了
	{
		pushStone();
	}
	setPlayerPosition(playerPos);
	checkSucess();

}

////判断 人和石头是不是相撞了
bool GameScene::isPush(Vec2 &pos)
{
	bool isPush = false;

	for (int i = 0; i < 4; i++)
	{
		if (pos == _stone[i]->getPosition())
		{
			stonePush[i] = true;   //某个箱子被撞了
			isPush = true;  //被撞了
		}
	}
	return isPush;
}

//人把石头推动了
void GameScene::pushStone()
{

	for (int i = 0; i < 4; i++)
	{
		if (stonePush[i])
		{
			if (!isCollideWall(_stone[i]->getPosition() + move(dir)))   //石头没撞墙
			{

				///记录到达目的地了没
				Vec2 newPos = _stone[i]->getPosition() + move(dir);
				for (int j = 0; j < 4; j++)
				{
					if (j != i)   //如果石头撞石头的话 也不能动
					{
						if (newPos == _stone[j]->getPosition())
						{
							return;
						}
					}
					
					if (newPos == _des[j])  //如果新位置是目标位置
					{
						_notReach.eraseObject(_stone[i]);  //记录没到达的容器减那个目标
					}
				
				}

				_stone[i]->setPosition(newPos);  //石头进行移动
				stonePush[i] = false;
				break;
			}

		}
	}

}


//判断某坐标是否撞墙
bool GameScene::isCollideWall(Vec2 position)
{
	bool isCollide = false;
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			isCollide = true;
		}
	}

	return isCollide;
}

///设定人的位置
void GameScene::setPlayerPosition(cocos2d::Vec2 pos)
{
	bool manCollideWall = false;
	bool stoneCollideWall = false;

	manCollideWall = isCollideWall(pos);

	for (int i = 0; i < 4; i++)
	{
		if (pos == _stone[i]->getPosition())   { stoneCollideWall = true; }
	}

	if (manCollideWall || stoneCollideWall)
	{
		return;
	}
	else
	{
		_player->setPosition(pos);
	}

}

Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}



//精灵移动
Vec2 GameScene::move(char dir)
{
	Vec2 m = Vec2(0, 0);
	switch (dir)
	{
	case 'u':
		m = Vec2(0, _tileMap->getTileSize().height);
		break;
	case 'd':
		m = Vec2(0, -_tileMap->getTileSize().height);
		break;
	case 'l':
		m = Vec2(-_tileMap->getTileSize().width, 0);
		break;
	case 'r':
		m = Vec2(_tileMap->getTileSize().width, 0);
		break;
	}
	return m;
}

void GameScene::checkSucess()
{
	int num = _notReach.size();
	if (num == 0)
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, GameWin::createScene()));

}