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
	//Ԥ������Ч
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

	//����ÿһ�ű�ʯ
	for (int x = 0; x < m_col; x++)
	{
		for (int y = 0; y < m_row; y++)
		{
			//����ߵĽ���
			if (x > 0)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x - 1][y]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x - 1][y]);
			}

			//���ұߵĽ���
			if (x < m_col - 1)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x + 1][y]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x + 1][y]);
			}

			//������Ľ���
			if (y < m_row - 1)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y + 1]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y + 1]);
			}

			//������Ľ���
			if (y > 0)
			{
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y - 1]);
				if (canCrush())
					isDeadMap = false;
				swap(&m_DustsBox[x][y], &m_DustsBox[x][y - 1]);
			}
		}
	}

	//canCrush��洢�������ı�ʯ��ȥ��������ģ�⽻�������Ի�Ҫ���
	m_crushDustBox.clear();

	return isDeadMap;

}


////�ж��Ƿ�����п��Ե�����һ�鳾�������ѳ����ռ�����
bool DustGrid::canCrush()
{
	int count = 0;

	Dust* DustBegin = nullptr; //��ʼ��������
	Dust* DustNext = nullptr;  //�ӿ�ʼ������ǰ�����ĳ���

	//����ÿһ��
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


	//����ÿһ��
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


	//���������ʯ���Ӳ�Ϊ�գ���ô˵�������п�������������
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
	//����������ʯ���ӣ������еı�ʯ������������
	for (auto dust : m_crushDustBox)
	{
		//�����µı�ʯ�������������ʼλ����������һ�е��ϱ�һ�У�������һ��
		auto newDust = Dust::createByType(dust->getX(), m_row, random(1, 5) );
		//setJewelPixPos(newJewel, newJewel->getX(), m_row);
		addChild(newDust);

		//���±�ʯ�ŵ��±�ʯ�����ڣ��ȴ����벼��
		m_newDustBox.pushBack(newDust);

		//��ʯ������Ӧ��ˢ�µı�ʯ��ʱ��Ϊ��
		m_DustsBox[dust->getX()][dust->getY()] = nullptr;

		//ԭ�б�ʯ��������
		dust->crush();
	}
}




////���¸��µ�ͼ
void DustGrid::updateMap()
{
	for (int x = 0; x < m_col;x++)
	for (int y = 0; y < m_row; y++)
	{
		m_DustsBox[x][y]->removeFromParent();  //�Ӹ��������Ƴ� 
		m_DustsBox[x][y] = createADust(x, y);  //���½���
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
	schedule(schedule_selector(DustGrid::onDustsSwaping));  //�����滻����
	
}

void DustGrid::swapDusts(Dust *a,Dust *b)
{
	//MessageBox("swap","window");
	_eventDispatcher->pauseEventListenersForTarget(this); //������ʼ���رմ�������
	//����������Ķ�������
	Dust* temp = m_DustsBox[a->getX()][a->getY()];
	m_DustsBox[a->getX()][a->getY()] = m_DustsBox[b->getX()][b->getY()];
	m_DustsBox[b->getX()][b->getY()] = temp;

	//λ�ý���
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

	//�ƶ���ʼ���ñ�ʯ����״̬Ϊ�棬�ƶ�����������Ϊ��
	d->setSwapingState(true);
	auto move = MoveTo::create(MoveTime, Vec2(d->getX() * GridWidth, d->getY() * GridWidth));
	auto call = CallFunc::create([d](){
		d->setSwapingState(false);
		//d->setStr();
	});
	d->runAction(Sequence::create(move, call, nullptr));
}


//��׽����
void DustGrid::onDustsSwaping(float dt)
{
	//��׽�������ڽ����ı�ʯ�Ľ��������Ƿ��Ѿ�ֹͣ�����ûֹͣ�����ؼ�����׽
	if (m_selectedDust->isSwaping() || m_swapedDust->isSwaping())
	{
		return;
	}
	//�����ʯ��������ִ�����
	else
	{
		unschedule(schedule_selector(DustGrid::onDustsSwaping));  //ֹͣ��׽

		log("swap over!");

		log("is it can crush?");

		//�ж��Ƿ�ǰ״̬��������
		if (canCrush())
		{
			log("yes,crush!");

			m_selectedDust = nullptr;

			////��ʼ��������������״̬��׽����(��׽��������Ϻ�ˢ�²���)����һ��������ʽ��ʼ
			//SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
			SimpleAudioEngine::getInstance()->playEffect("effectMusic.mp3");
			goCrush();
			schedule(schedule_selector(DustGrid::onDustsCrushing));
		}
		else
		{
			log("no, cant crush!");

			//����������������ȥ��������������ʱ�Ĳ�׽����(��׽��������Ϻ󣬿�����������)
			//SimpleAudioEngine::getInstance()->playEffect("swapback.ogg");
			swapDusts(m_selectedDust, m_swapedDust);
			schedule(schedule_selector(DustGrid::onDustsSwapingBack));
		}
	}
}

void DustGrid::onDustsSwapingBack(float dt)
{
	//��׽�������ڽ����ı�ʯ�Ľ��������Ƿ��Ѿ�ֹͣ�����ûֹͣ�����ؼ�����׽
	if (m_selectedDust->isSwaping() || m_swapedDust->isSwaping())
	{
		return;
	}
	else
	{
		unschedule(schedule_selector(DustGrid::onDustsSwapingBack)); //ֹͣ��׽

		log("swap back!");

		m_selectedDust = nullptr;

		_eventDispatcher->resumeEventListenersForTarget(this); //���¿�ʼ��������
	}
}

void DustGrid::onDustsCrushing(float dt)
{
	//��׽��ʯ����״̬������б�ʯ������������ô������׽
	for (auto dust : m_crushDustBox)
	{
		if (dust->isCrushing())
		{
			//log("crushing");
			return;
		}
	}

	//���ȫ����ʯ�Ѿ�������ϣ�ֹͣ��׽����
	unschedule(schedule_selector(DustGrid::onDustsCrushing));

	m_crushDustBox.clear(); //���������ʯ����

	log("crush over!");
	log("begin to refresh!");

	//ˢ�±�ʯ���У�������ˢ��״̬��׽������ˢ��һ������������ж��������Ƿ��������
	refreshDustsGrid();
	schedule(schedule_selector(DustGrid::onDustsRefreshing));
}

void DustGrid::onDustsRefreshing(float dt)
{
	//��׽��ʯˢ��״̬������±�ʯ���ӻ��б�ʯ�����±�ʯ����ˢ�µ��У�����ô������׽
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

			//�������������ô��������
			//SimpleAudioEngine::getInstance()->playEffect("crush.ogg");
			SimpleAudioEngine::getInstance()->playEffect("effectMusic.mp3");
			goCrush();
			schedule(schedule_selector(DustGrid::onDustsCrushing));
		}
		else
		{
			log("no, cant crush! over!");

			//�ж��Ƿ�Ϊ��ͼ������ǣ���ִ��һ�����ֶ�������ʾ�������µ�ͼ
			if (isDeadMap())
			{
				log("cant crush any more, updating a new map!");

				auto winSize = Director::getInstance()->getWinSize();
				auto label = Label::createWithTTF("Cant Crush Any More, Change!", "fonts/Marker Felt.ttf", 24);
				label->setTextColor(Color4B::BLACK);
				label->setPosition(winSize.width / 2, winSize.height / 2);
				label->setOpacity(0);
				this->getParent()->addChild(label);

				//��ʾ���ֵ��뵭���󣬸��µ�ͼ���ٿ�����������
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
				//���������ͼ����ô��ֱ�ӿ��������������ȴ���һ�ֵĽ�������
				_eventDispatcher->resumeEventListenersForTarget(this);
			}
		}
	}
}


void DustGrid::refreshDustsGrid()
{
	//�����У���������п�λ����ôӦ��ˢ��
	for (int x = 0; x < m_col; x++)
	{
		int empty_count = 0; //һ���ܵĿո�����

		for (int y = 0; y < m_row; y++)
		{
			//��������������ʯ�����ڵı�ʯָ�룬���Ϊ�գ���ô˵��������λ��Ϊ��
			auto dust = m_DustsBox[x][y];
			if (!dust)
				empty_count++;
		}
		if (empty_count)
		{
			//log("the %d col has %d empty", x, empty_count);
			//�ҵ��п�λ���У�ˢ�¸��еı�ʯ
			refreshDustsToNewPos(x);
		}
	}
}

void DustGrid::refreshDustsToNewPos(int col)
{
	//ˢ�¸�������ı�ʯ
	int n = 0; //��ǰ�������Ŀ�λ��
	auto pDustsbox = &m_DustsBox; //����һ����ʯ���ӵ�ָ�룬����Ϊ�������ܴ���lamda

	//�������еı�ʯ����
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
				//���±�ʯ�����ڵ�����
				(*pDustsbox)[dust->getX()][dust->getY()] = dust;
			});

			dust->runAction(Sequence::create(move, call, nullptr));
			//dust->setStr();
		}
	}

	//�����±�ʯ����
	int i = n;
	int delta = 1;

	for (auto dust : m_newDustBox)
	{
		if (dust->getX() == col)
		{
			dust->setY(m_row - i);

			auto delay = DelayTime::create(0.2);
			//��������ٶ�������һЩ
			auto move = MoveBy::create(0.4*delta++, Vec2(0, -i--*GridWidth));
			auto call = CallFunc::create([dust, pDustsbox, this](){
				(*pDustsbox)[dust->getX()][dust->getY()] = dust;
				//���±�ʯ�������Ƴ��ñ�ʯ
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