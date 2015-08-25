
#include "GameScene.h"
#include "ChessBoard.h"
#include "Chess.h"

Scene* GameScene::createScene()
{
	Scene *game = Scene::create();
	GameScene* gameScene = GameScene::create();
	game->addChild(gameScene);

	return game;
}

bool GameScene::init()
{
	//Layer::init();
	
	//auto chess = Chess::createChess("pao", 'r',5, 9, 'c');
	auto chessBoard = ChessBoard::create();
	addChild(chessBoard);

	return true;
}

