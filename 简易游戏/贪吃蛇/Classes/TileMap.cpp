#include "TileMap.h"

bool TileMap::init()
{


	if (!Layer::init())
	{
		return false;
	}

	auto tiles = DrawNode::create();

	for (int i = 0; i < 11; i++)
	{
	tiles->drawLine(Vec2(50,50+i*50),Vec2(350,50+i*50),Color4F::RED);
	}

	for (int i = 0; i < 7; i++)
	{
		tiles->drawLine(Vec2(50+i*50, 50), Vec2(50+i*50, 550), Color4F::RED);
	}
	//tiles->

	addChild(tiles);
	return true;


}