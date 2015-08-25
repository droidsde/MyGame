#include "DustGrid.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

DustGrid* DustGrid::create(int row, int col)
{
	auto dustGrid = new DustGrid();
	dustGrid->init(row, col);
	dustGrid->autorelease();
	return dustGrid;
}

bool DustGrid::init(int row, int col)
{
	Node::init();

	tool1 = false;
	tool2 = false;
	//预加载音效
	SimpleAudioEngine::getInstance()->preloadEffect("crush.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("swapback.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("effectMusic.mp3");
	m_row = row;
	m_col = col;

	m_selectedDust = nullptr;
	m_swapedDust = nullptr;

	m_DustsBox.resize(m_row);
	for (auto &vec : m_DustsBox)
		vec.resize(m_col);

	for (int x = 0; x < m_col; x++)
	for (int y = 0; y < m_row; y++)
	{
		m_DustsBox[x][y] = createADust(x,y);
	}

	while (isDeadMap())
	{
		updateMap();
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(DustGrid::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(DustGrid::onTouchMoved,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	////
	/*nl = LabelTTF::create(__String::createWithFormat("left new:%d,%d", m_newDustBox.size(), m_crushDustBox.size())->getCString(), "arial", 32);
	addChild(nl);
	nl->setPosition(0, 500);
	schedule(schedule_selector(DustGrid::onCountNew),1.0);*/
	////
	//setPosition(70, 400);
	
	log("JewelsGrid init!");
	return true;
}

bool DustGrid::isDeadMap()
{
	auto swap = [](Dust** a, Dust** b)
	{
		auto temp = *a;
		*a = *b;
		*b = temp;
	};

	bool isDeadMap = true;

	//遍历每一颗宝石
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			//跟左边的交换
			if (x > 0)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x - 1][y]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x - 1][y]);
			}

			//跟右边的交换
			if (x < m_col - 1)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x + 1][y]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x + 1][y]);
			}

			//跟上面的交换
			if (y < m_row - 1)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y + 1]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y + 1]);
			}

			//跟下面的交换
			if (y > 0)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y - 1]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y - 1]);
			}
		}
	}

	//canCrush会存储能消除的宝石进去，由于是模拟交换，所以还要清空
	m_crushDustBox.clear();

	return isDeadMap;

}


////判断是否可以有可以抵消的一组尘粒，并把尘粒收集起来
bool DustGrid::canCrush()
{
	int count = 0;

	Dust* DustBegin = nullptr; //开始遍历尘粒
	Dust* DustNext = nullptr;  //从开始尘粒往前遍历的尘粒

	//遍历每一列
	for (int x = 0; x < m_col;x++)
	for (int y = 0; y < m_row - 1;)
	{
		count = 1;
		DustBegin = m_DustsBox[x][y];
		DustNext = m_DustsBox[x][y+1];

		while (DustBegin->getType() == DustNext->getType())
		{
			count++;
			int nextIndex = y + count;
			if (nextIndex >m_row - 1)
				break;

			DustNext = m_DustsBox[x][nextIndex];
		}
		if (count >= 3)
		{
			for (int n = 0; n < count; n++)
			{
				auto dust = m_DustsBox[x][y+n];
				m_crushDustBox.pushBack(dust);
			}
		}
		y += count;
	}


	//遍历每一行
	for (int y = 0; y < m_row; y++)
	for (int x = 0; x < m_col - 1;)
	{
		count = 1;
		DustBegin = m_DustsBox[x][y];
		DustNext = m_DustsBox[x+1][y];

		while (DustBegin->getType() == DustNext->getType())
		{
			count++;
			int nextIndex = x + count;
			if (nextIndex >m_col - 1)
				break;

			DustNext = m_DustsBox[nextIndex][y];
		}
		if (count >= 3)
		{
			for (int n = 0; n < count; n++)
			{
				auto dust = m_DustsBox[x+n][y];
				m_crushDustBox.pushBack(dust);
			}
		}
		x += count;
	}


	//如果消除宝石盒子不为空，那么说明该阵列可消除，返回真
	if (!m_crushDustBox.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}


void DustGrid::goCrush()
{
	//遍历消除宝石盒子，对其中的宝石进行消除操作
	for (auto dust : m_crushDustBox)
	{
		//生成新的宝石，类型随机，初始位置在最上面一行的上边一行（布局外一格）
		auto newDust = Dust::createByType(dust->getX(), m_row, random(1, 5) );
		//setJewelPixPos(newJewel, newJewel->getX(), m_row);
		addChild(newDust);

		//将新宝石放到新宝石盒子内，等待加入布局
		m_newDustBox.pushBack(newDust);

		//宝石盒子内应当刷新的宝石暂时置为空
		m_DustsBox[dust->getX()][dust->getY()] = nullptr;

		//原有宝石对象消除
		dust->crush();
	}
}




////重新更新地图
void DustGrid::updateMap()
{
	for (int x = 0; x < m_col;x++)
	for (int y = 0; y < m_row; y++)
	{
		m_DustsBox[x][y]->removeFromParent();  //从父容器中移除 
		m_DustsBox[x][y] = createADust(x, y);  //重新建造
	}
	log("update a new map!");
}


Dust* DustGrid::createADust(int x,int y)
{
	Dust* dust = nullptr;
	///???
	while (1)
	{
		dust = Dust::createByType(x, y, random(1, 5));

	//	MessageBox(__String::createWithFormat("%d",dust->getType())->getCString(),"1");

		if (isDustLegal(dust, x, y))
		{
			break;
		}
		//dust-
	
	}
	addChild(dust);
	return dust;
}



bool DustGrid::onTouchBegan(Touch *t,Event *e)
{

	auto vec = this->convertToNodeSpace(t->getLocation());

	int x = vec.x/GridWidth;
	int y = vec.y/GridWidth;

	if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
	{
		m_selectedDust = m_DustsBox[x][y];
	}
	if (m_selectedDust&&!tool1&&!tool2)
	{
		return true;
	}
	 if (m_selectedDust&&(tool1||tool2))
	{
		    checkTool();
			m_selectedDust = nullptr;
			SimpleAudioEngine::getInstance()->playEffect("effectMusic.mp3");
			//SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
			goCrush();
			schedule(schedule_selector(DustGrid::onDustsCrushing));
			tool1 = false;
			tool2 = false;
		return false;
	}
	else
	{
		return false;
	}
}

void DustGrid::onTouchMoved(Touch *t, Event *e)
{
	if (!m_selectedDust)
	{
		return;
	}


	auto vec = this->convertToNodeSpace(t->getLocation());

	int x = vec.x / GridWidth;
	int y = vec.y / GridWidth;

	if (x<0 || x>7 || y<0 || y>7)
	{
		return;
	}
	if (abs(m_selectedDust->getX()-x)+abs(m_selectedDust->getY()-y) !=1)
	{
		return;
	}
	
	m_swapedDust = m_DustsBox[x][y];
	swapDusts(m_selectedDust, m_swapedDust);
	schedule(schedule_selector(DustGrid::onDustsSwaping));  //正在替换尘粒
	
}

void DustGrid::swapDusts(Dust *a,Dust *b)
{
	//MessageBox("swap","window");
	_eventDispatcher->pauseEventListenersForTarget(this); //交换开始，关闭触摸监听
	//把容器里面的东西换了
	Dust* temp = m_DustsBox[a->getX()][a->getY()];
	m_DustsBox[a->getX()][a->getY()] = m_DustsBox[b->getX()][b->getY()];
	m_DustsBox[b->getX()][b->getY()] = temp;

	//位置交换
	int x= a->getX();
	a->setX(b->getX());
	b->setX(x);

	int y = a->getY();
	a->setY(b->getY());
	b->setY(y);

	//a->setPos();
	//b->setPos();
	moveToNewPosition(a);
	moveToNewPosition(b);


	/*a->setStr();
	b->setStr();*/

}

bool DustGrid::isDustLegal(Dust* dust,int x,int y )
{
	bool isXLegal = true;
	bool isYLegal = true;

	if (x > 1)
	{
		if (dust->getType() == m_DustsBox[x - 1][y]->getType() &&
			dust->getType() == m_DustsBox[x - 2][y]->getType())
		{ isXLegal = false;}
		else
		{ isXLegal = true;}
	}

	if (y > 1)
	{
		if (dust->getType() == m_DustsBox[x][y - 1]->getType() &&
			dust->getType() == m_DustsBox[x][y - 2]->getType())
		{ isYLegal = false;}
		else
		{ isYLegal = true;}
	}


	return isXLegal&&isYLegal;

}

void DustGrid::moveToNewPosition(Dust* d)
{

	//auto move = MoveTo::create(MoveTime,Vec2(d->getX()*50,d->getY()*50));
	//d->runAction(move);

	//移动开始设置宝石交换状态为真，移动结束再设置为假
	d->setSwapingState(true);
	auto move = MoveTo::create(MoveTime, Vec2(d->getX() * GridWidth, d->getY() * GridWidth));
	auto call = CallFunc::create([d](){
		d->setSwapingState(false);
		//d->setStr();
	});
	d->runAction(Sequence::create(move, call, nullptr));
}


//捕捉函数
void DustGrid::onDustsSwaping(float dt)
{
	//捕捉两个正在交换的宝石的交换动作是否已经停止，如果没停止，返回继续捕捉
	if (m_selectedDust->isSwaping() || m_swapedDust->isSwaping())
	{
		return;
	}
	//如果宝石交换动作执行完毕
	else
	{
		unschedule(schedule_selector(DustGrid::onDustsSwaping));  //停止捕捉

		log("swap over!");

		log("is it can crush?");

		//判断是否当前状态可以消除
		if (canCrush())
		{
			log("yes,crush!");

			m_selectedDust = nullptr;

			////开始消除，开启消除状态捕捉函数(捕捉到消除完毕后，刷新布局)，这一轮消除正式开始
			//SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
			SimpleAudioEngine::getInstance()->playEffect("effectMusic.mp3");
			goCrush();
			schedule(schedule_selector(DustGrid::onDustsCrushing));
		}
		else
		{
			log("no, cant crush!");

			//不能消除，交换回去，开启交换返回时的捕捉函数(捕捉到消除完毕后，开启触摸接听)
			//SimpleAudioEngine::getInstance()->playEffect("swapback.ogg");
			swapDusts(m_selectedDust, m_swapedDust);
			schedule(schedule_selector(DustGrid::onDustsSwapingBack));
		}
	}
}

void DustGrid::onDustsSwapingBack(float dt)
{
	//捕捉两个正在交换的宝石的交换动作是否已经停止，如果没停止，返回继续捕捉
	if (m_selectedDust->isSwaping() || m_swapedDust->isSwaping())
	{
		return;
	}
	else
	{
		unschedule(schedule_selector(DustGrid::onDustsSwapingBack)); //停止捕捉

		log("swap back!");

		m_selectedDust = nullptr;

		_eventDispatcher->resumeEventListenersForTarget(this); //重新开始触摸接听
	}
}

void DustGrid::onDustsCrushing(float dt)
{
	//捕捉宝石消除状态，如果有宝石还在消除，那么继续捕捉
	for (auto dust : m_crushDustBox)
	{
		if (dust->isCrushing())
		{
			//log("crushing");
			return;
		}
	}

	//如果全部宝石已经消除完毕，停止捕捉函数
	unschedule(schedule_selector(DustGrid::onDustsCrushing));

	m_crushDustBox.clear(); //清空消除宝石盒子

	log("crush over!");
	log("begin to refresh!");

	//刷新宝石阵列，并开启刷新状态捕捉函数（刷新一遍结束，重新判断新阵列是否可消除）
	refreshDustsGrid();
	schedule(schedule_selector(DustGrid::onDustsRefreshing));
}

void DustGrid::onDustsRefreshing(float dt)
{
	//捕捉宝石刷新状态，如果新宝石盒子还有宝石（即新宝石还在刷新当中），那么继续捕捉
	if (m_newDustBox.size() != 0)
	{
		//log("refreshing!");
		return;
	}
	else
	{
		unschedule(schedule_selector(DustGrid::onDustsRefreshing));

		log("refresh over!");
		log("and now, is it can crush?");

		if (canCrush())
		{
			log("yes, crush again!");

			//如果能消除，那么继续消除
			//SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
			SimpleAudioEngine::getInstance()->playEffect("effectMusic.mp3");
			goCrush();
			schedule(schedule_selector(DustGrid::onDustsCrushing));
		}
		else
		{
			log("no, cant crush! over!");

			//判断是否为死图，如果是，则执行一段文字动画，提示即将更新地图
			if (isDeadMap())
			{
				log("cant crush any more, updating a new map!");

				auto winSize = Director::getInstance()->getWinSize();
				auto label = Label::createWithTTF("Cant Crush Any More, Change!", "fonts/Marker Felt.ttf", 24);
				label->setTextColor(Color4B::BLACK);
				label->setPosition(winSize.width / 2, winSize.height / 2);
				label->setOpacity(0);
				this->getParent()->addChild(label);

				//提示文字淡入淡出后，更新地图，再开启触摸监听
				auto fadein = FadeIn::create(0.5);
				auto fadeout = FadeOut::create(0.5);

				auto call = CallFunc::create([this, label](){
					do
					{
						updateMap();
					} while (isDeadMap());

					label->removeFromParent();

					_eventDispatcher->resumeEventListenersForTarget(this);
				});

				label->runAction(Sequence::create(fadein, DelayTime::create(2), fadeout, call, nullptr));
			}
			else
			{
				//如果不是死图，那么就直接开启触摸监听，等待下一轮的交互操作
				_eventDispatcher->resumeEventListenersForTarget(this);
			}
		}
	}
}


void DustGrid::refreshDustsGrid()
{
	//遍历列，如果该列有空位，那么应当刷新
	for (int x = 0; x < m_col; x++)
	{
		int empty_count = 0; //一列总的空格子数

		for (int y = 0; y < m_row; y++)
		{
			//根据坐标索引宝石盒子内的宝石指针，如果为空，那么说明该坐标位置为空
			auto dust = m_DustsBox[x][y];
			if (!dust)
				empty_count++;
		}
		if (empty_count)
		{
			//log("the %d col has %d empty", x, empty_count);
			//找到有空位的列，刷新该列的宝石
			refreshDustsToNewPos(x);
		}
	}
}

void DustGrid::refreshDustsToNewPos(int col)
{
	//刷新该列上面的宝石
	int n = 0; //当前遍历到的空位数
	auto pDustsbox = &m_DustsBox; //保存一个宝石盒子的指针，这是为了让其能传入lamda

	//先让现有的宝石下落
	for (int y = 0; y < m_row; y++)
	{
		auto dust = m_DustsBox[col][y];

		if (!dust)
		{
			n++;
			continue;
		}
		else if (n != 0)
		{
			dust->setY(dust->getY() - n);
			auto move = MoveBy::create(0.4, Vec2(0, -n*GridWidth));
			auto call = CallFunc::create([pDustsbox, dust](){
				//更新宝石盒子内的数据
				(*pDustsbox)[dust->getX()][dust->getY()] = dust;
			});

			dust->runAction(Sequence::create(move, call, nullptr));
			//dust->setStr();
		}
	}

	//再让新宝石下落
	int i = n;
	int delta = 1;

	for (auto dust : m_newDustBox)
	{
		if (dust->getX() == col)
		{
			dust->setY(m_row - i);

			auto delay = DelayTime::create(0.2);
			//后下落的速度设置慢一些
			auto move = MoveBy::create(0.4*delta++, Vec2(0, -i--*GridWidth));
			auto call = CallFunc::create([dust, pDustsbox, this](){
				(*pDustsbox)[dust->getX()][dust->getY()] = dust;
				//从新宝石盒子中移除该宝石
				m_newDustBox.eraseObject(dust);
			});

			dust->runAction(Sequence::create(delay, move, call, nullptr));
			//dust->setStr();
		}
	}
	//if (!m_newDustBox.empty())
	//{
	//	m_newDustBox.clear();
	//}
}

//void DustGrid::onCountNew(float dt)
//{
//	nl->setString(__String::createWithFormat("left new:%d,%d", m_newDustBox.size(), m_crushDustBox.size())->getCString());
//}

void DustGrid::setTool(int type)
{
	switch (type)
	{
	case 1:
		tool1 =true;
		tool2 = false;
		break;
	case 2:
		tool2 = true;
		tool1 = false;
		break;
	}
}

void DustGrid::checkTool()
{
	_eventDispatcher->pauseEventListenersForTarget(this);
	if (tool1)
	{
		for (int x = 0; x < m_col; x++)
		for (int y = 0; y < m_row; y++)
		{
			if (m_DustsBox[x][y]->getType() == m_selectedDust->getType())
			{
				auto dust = m_DustsBox[x][y];
				m_crushDustBox.pushBack(dust);
			}
		}
	}
	if (tool2)
	{
		for (int x = 0; x < m_col; x++)
		for (int y = 0; y < m_row; y++)
		{
			if ((abs(m_DustsBox[x][y]->getX() - m_selectedDust->getX()) + abs(m_DustsBox[x][y]->getY() - m_selectedDust->getY()))<=2)
			{
				auto dust = m_DustsBox[x][y];
				m_crushDustBox.pushBack(dust);
			}
		}
	}
}