#include <DxLib.h>
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"


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
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
}

bool GameScene::SystemInit(void)
{

	return true;
}

bool GameScene::GameInit(void)
{

	player = new Player();
	player->GameInit();
	stage = new Stage();
	stage->Initialize();

	return true;
}

void GameScene::Initialize()
{
}

void GameScene::Update(void)
{
	if (player != nullptr)
	{
		player->Update();
	}

	// プレイヤーの座標(playerX, playerY)が画面中央に来るようにカメラを配置
	cameraX = player->GetX() - (SCREEN_WIDTH / 2);
	cameraY = player->GetY() - (SCREEN_HEIGHT / 2);
}

void GameScene::Draw(void)
{
	// --- ここからテスト用：地面を描く ---
	// 画面の下の方に、50ピクセルおきに縦線を引く
	for (int i = 0; i < 20000; i += 50) {
		int x = (int)(i - cameraX);
		DrawLine(x, 0, x, 3000, GetColor(100, 100, 100));
	}
	// 1. まず背景・ステージを描画
	if (stage != nullptr)
	{
		stage->Draw(cameraX, cameraY);
	}
	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);
	}
}

bool GameScene::Release(void)
{
	if (player != nullptr) { delete player; player = nullptr; }
	if (stage != nullptr) { delete stage;  stage = nullptr; }
	return true;
}
