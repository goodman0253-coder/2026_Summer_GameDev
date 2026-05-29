#include <DxLib.h>
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "Enemy1.h"


GameScene::GameScene()
{
	enemys.push_back(new Enemy1());
	for (int i = 0; i < enemys.size();i++)
	{
		if (!enemys[i]->SystemInit(this))
		{
			printfDx("敵の初期化に失敗");
		}
		enemys[i]->GameInit();
	}
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

	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Release();
			delete enemys[i];
		}
	}
	enemyBullets.clear();
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

void GameScene::AddEnemyBullet(EnemyBulletBase* newBullet, Vector2F spawnPos, Vector2F vel)
{
	if (newBullet != nullptr)
	{
		if (newBullet != nullptr)
		{
			newBullet->SystemInit(this); // 敵弾の画像を読み込む
			newBullet->GameInit(spawnPos, vel); // 敵弾の初期位置と速度を設定
			enemyBullets.push_back(newBullet); // GamwSceneのリストに追加
		}
	}
}

void GameScene::Update(void)
{
	if (player != nullptr)
	{
		player->Update();
	}

	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Update();
		}
	}

	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Update();
		}
	}

	// 生存していない敵弾をリストから削除する
	auto bitr = enemyBullets.begin();
	while (bitr != enemyBullets.end())
	{
		if (!(*bitr)->GetAlive())
		{
			(*bitr)->Release();
			delete (*bitr);
			bitr = enemyBullets.erase(bitr);
		}
		else
		{
			++bitr;
		}
	}

	// プレイヤーの座標(playerX, playerY)が画面中央に来るようにカメラを配置
	cameraX = player->GetX() - (SCREEN_WIDTH / 2);
	if (cameraX <= 0)
	{
		cameraX = 0;
	}
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

	if (stage != nullptr)
	{
		// 背景を描く
		stage->Draw(cameraX, cameraY, LAYER_BACKGROUND);

		// 中景を描く
		stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUND);
	}

	// プレイヤーを描画
	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);
	}

	size_t size = enemys.size(); // 敵のテーブルの要素数を取得
	std::vector<EnemyBase*>::iterator eitr = enemys.begin(); // イテレータを取得
	for (int ii = 0; ii < size; ii++) {
		(*eitr)->Draw();
		eitr++;
	}

	// 敵の弾を描画
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Draw();
		}
	}
     
	if (stage != nullptr)
	{
		// 前景を描く
		stage->Draw(cameraX, cameraY, LAYER_OBJECT);

		// 前景を描く
		stage->Draw(cameraX, cameraY, LAYER_FOREGROUND);
	}
}

bool GameScene::Release(void)
{
	if (player != nullptr) { delete player; player = nullptr; }
	if (stage != nullptr) { delete stage;  stage = nullptr; }

	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Release();
			delete enemyBullets[i];
		}
	}
	enemyBullets.clear();

	return true;
}
