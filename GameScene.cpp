#include <DxLib.h>
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "Enemy1.h"
#include "BreadBase.h"
#include "Bread.h"


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
}

bool GameScene::SystemInit(void)
{

	return true;
}

bool GameScene::GameInit(void)
{

	player = new Player();
	player->SetGameScene(this);
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

	for (auto* bread : breadList)
	{
		if (bread->IsAlive())
		{
			bread->Update();
		}
	}

	for (auto it = breadList.begin(); it != breadList.end(); )
	{
		if (!(*it)->IsAlive()) // lifeTimerが0になってIsAliveがfalseになったら
		{
			delete (*it);              // メモリ解放
			it = breadList.erase(it);  // リストから除外
		}
		else
		{
			++it; // 生きていれば次へ
		}
	}

	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Update();
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
	};        

	// 2. ⭕ すべてのパンの描画処理
	for (auto* bread : breadList)
	{
		bread->Draw(cameraX, cameraY);
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
	for (auto* bread : breadList)
	{
		delete bread;
	}
	breadList.clear(); // リスト自体の中身も空っぽにする
	return true;
}
