#include <DxLib.h>
#include "GameScene.h"
#include "Player.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	if (player != nullptr) 
	{
		delete player;
		player = nullptr;
	}
}

bool GameScene::SystemInit(void)
{
	return true;
}

bool GameScene::GameInit(void)
{
	player = new Player();
	return true;
}

void GameScene::Update(void)
{
	if (player != nullptr)
	{
		player->Update();
	}
}

void GameScene::Draw(void)
{
	if (player != nullptr)
	{
		player->Draw();
	}
}

bool GameScene::Release(void)
{
	return true;
}
