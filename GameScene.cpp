#include <DxLib.h>
#include "SceneManager.h"
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
	player->SetGameScene(this);
	player->GameInit();
	stage = new Stage();
	stage->Initialize();
	 
	//仮のクリア
	isClearTriggered = false;
	clearTimer = 0;

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
			newBullet->SystemInit(this); // 
			newBullet->GameInit(spawnPos, vel); // 
			enemyBullets.push_back(newBullet); // 
		}
	}
}

void GameScene::Update(void)
{

	if (player != nullptr)
	{
		player->Update();
		cameraY = player->GetY() - (SCREEN_HEIGHT / 2);
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


	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Update();
		}
	}
	// 
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
	// �v���C���[�̍��W(playerX, playerY)����ʒ����ɗ���悤�ɃJ������z�u
	// プレイヤーの座標(playerX, playerY)が画面中央に来るようにカメラを配置

	if (cameraX != Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH)
	{
		cameraX = player->GetX() - (SCREEN_WIDTH / 2);
	}

	if (cameraX <= 0)
	{
		cameraX = 0;
	}
	if (cameraX >= Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH)
	{

		cameraX = Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH;
		
	}

	if (player != nullptr && !player->IsInvincible())
	{
		// すべてのエネミーに対して当たり判定をチェック
		for (auto enemy : enemys)
		{
			if (enemy == nullptr) continue;

			
		}
	}
	if (player != nullptr && player->GetHp() <= 0)
	{
		if (sceneManager != nullptr)
		{
			
			sceneManager->ChangeScene(SCENE_GAMEOVER);
			return;
		}
	}

	//仮のクリア
	if (cameraX >= Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - (SCREEN_WIDTH * 1.5))
	{
		//ここ
		if (!isClearTriggered)
		{
			isClearTriggered = true;
			clearTimer = 0; // タイマーをリセット
		}
	}

	if (isClearTriggered)
	{
		clearTimer++; // 毎フレーム 1 ずつ増やす

		// 3秒（60フレーム × 10秒 = 600フレーム）経ったらシーン遷移
		if (clearTimer >= 600)
		{
			if(sceneManager != nullptr)
			{
				
				sceneManager->ChangeScene(SCENE_GAMECLEAR);// 現在のシーンを保持

			}

		}
	}


}

void GameScene::Draw(void)
{

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

	// �G�̒e��`��
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

	if (player != nullptr)
	{
		SetFontSize(40);
		DrawFormatString(50, 50, GetColor(255, 255, 255), "PLAYER HP: %d / 5", player->GetHp());

		if (player->IsInvincible())
		{
			DrawString(50, 100, "INVINCIBLE!!", GetColor(255, 0, 0));
		}
	}

	// --- ここからテスト用：地面を描く ---
	// 画面の下の方に、64ピクセルおきに縦線を引く
	for (int i = 0; i < 20000; i += 64) {
		int x = (int)(i - cameraX);
		DrawLine(x, 0, x, 3000, GetColor(100, 100, 100));
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
	for (auto* bread : breadList)
	{
		delete bread;
	}
	breadList.clear(); // リスト自体の中身も空っぽにする
	return true;
}
