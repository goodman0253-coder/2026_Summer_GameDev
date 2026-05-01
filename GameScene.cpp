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
	// ログを出して確認
	printfDx("GameScene::GameInit Start!\n");

	player = new Player();

	if (player != nullptr) {
		printfDx("Player object created successfully!\n");
	}
	else {
		printfDx("Failed to create Player object...\n");
	}

	player ->GameInit();

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
