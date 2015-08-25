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

	///ȷ���ƶ�����
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


	if (isPush(playerPos))  //�жϺ��Ǹ�ʯͷ��ײ��
	{
		pushStone();
	}
	setPlayerPosition(playerPos);
	checkSucess();

}

////�ж� �˺�ʯͷ�ǲ�����ײ��
bool GameScene::isPush(Vec2 &pos)
{
	bool isPush = false;

	for (int i = 0; i < 4; i++)
	{
		if (pos == _stone[i]->getPosition())
		{
			stonePush[i] = true;   //ĳ�����ӱ�ײ��
			isPush = true;  //��ײ��
		}
	}
	return isPush;
}

//�˰�ʯͷ�ƶ���
void GameScene::pushStone()
{

	for (int i = 0; i < 4; i++)
	{
		if (stonePush[i])
		{
			if (!isCollideWall(_stone[i]->getPosition() + move(dir)))   //ʯͷûײǽ
			{

				///��¼����Ŀ�ĵ���û
				Vec2 newPos = _stone[i]->getPosition() + move(dir);
				for (int j = 0; j < 4; j++)
				{
					if (j != i)   //���ʯͷײʯͷ�Ļ� Ҳ���ܶ�
					{
						if (newPos == _stone[j]->getPosition())
						{
							return;
						}
					}
					
					if (newPos == _des[j])  //�����λ����Ŀ��λ��
					{
						_notReach.eraseObject(_stone[i]);  //��¼û������������Ǹ�Ŀ��
					}
				
				}

				_stone[i]->setPosition(newPos);  //ʯͷ�����ƶ�
				stonePush[i] = false;
				break;
			}

		}
	}

}


//�ж�ĳ�����Ƿ�ײǽ
bool GameScene::isCollideWall(Vec2 position)
{
	bool isCollide = false;
	//�����ص�����ת��Ϊ��Ƭ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //��ײ���ɹ�
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			isCollide = true;
		}
	}

	return isCollide;
}

///�趨�˵�λ��
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



//�����ƶ�
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