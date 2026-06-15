#include <DxLib.h>
#include "SceneManager.h"
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
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

			newBullet->SystemInit(this); // EnemyBulletBaseのSystemInit()にGameSceneのインスタンスを渡す
			newBullet->GameInit(spawnPos, vel); // EnemyBulletBaseのGameInit()に初期位置と速度を設定
			enemyBullets.push_back(newBullet); // GameSceneの敵弾リストに追加
		}
	}
}

void GameScene::CollisionCheckPB()
{
	PX = player->GetX();
	PY = player->GetY();

	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			Vector2F pos = enemyBullets[i]->GetPos(); // EnemyBulletBase から弾の座標を得る
			BX = (int)pos.x;
			BY = (int)pos.y;

			if (PX + 23 < BX + (enemyBullets[i]->GetSize().x / 2) && // �v���C���[�̉E�[���G�̒e�̍��[��荶�ɂ���ꍇ
				PX + Player::PLAYER_WID - 23 > BX - (enemyBullets[i]->GetSize().x / 2) && // �v���C���[�̍��[���G�̒e�̉E�[���E�ɂ���ꍇ
				PY < BY + (enemyBullets[i]->GetSize().y / 2) && // �v���C���[�̉��[���G�̒e�̏�[��艺�ɂ���ꍇ
				PY + Player::PLAYER_HIG > BY - (enemyBullets[i]->GetSize().y / 2)) // �v���C���[�̏�[���G�̒e�̉��[����ɂ���ꍇ
			{
				player->ApplyDamage(); // プレイヤーにダメージを与える
				enemyBullets[i]->SetAlive(false); // 敵の弾を消す
			}
		}
	}
}

void GameScene::CollisionCheckPE()
{
	PX = player->GetX();
	PY = player->GetY();

	for(int i =0;i< enemys.size();i++)
	{
		if (enemys[i] != nullptr)
		{
			Vector2F pos = enemys[i]->GetEnemyPos(); // EnemyBase のインスタンスから取得
			EX = (int)pos.x;
			EY = (int)pos.y;
			
			if (PX + 23 < EX + 16 && // プレイヤーの右端が敵の左端より左にある場合
				PX + Player::PLAYER_WID - 23 > EX - 16 && // プレイヤーの左端が敵の右端より右にある場合
				PY < EY + (enemys[i]->GetEnemySize().y / 2) && // プレイヤーの下端が敵の上端より下にある場合
				PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2)) // プレイヤーの上端が敵の下端より上にある場合
			{
				player->ApplyDamage(); // プレイヤーにダメージを与える
				enemys[i]->SetDamage(1); // エネミーにダメージを与える
			}
		}
	}
}

//�@�v���C���[�̃p���ƓG�̓����蔻��
void GameScene::CollisionCheckEB()
{
	for (int i= 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			Vector2F enemyPos = enemys[i]->GetEnemyPos();
			Vector2 enemySize = enemys[i]->GetEnemySize();
			for (auto* bread : breadList)
			{
				if (bread->IsAlive())
				{
					Vector2F breadPos = { bread->x, bread->y };
					Vector2 breadSize = { bread->width, bread->height };
					if (breadPos.x < enemyPos.x + (enemySize.x / 2) &&
						breadPos.x + breadSize.x > enemyPos.x - (enemySize.x / 2) &&
						breadPos.y < enemyPos.y + (enemySize.y / 2) &&
						breadPos.y + breadSize.y > enemyPos.y - (enemySize.y / 2))
					{
						enemys[i]->SetDamage(1); // �G�Ƀ_���[�W��^����֐����Ăяo��
						bread->Kill(); // ���������p���͏�����悤�ɂ���
					}
				}
			}
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

	// すべての敵弾に対して更新処理を行う
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Update();
		}
	}
	// 画面外に出た敵弾を削除する処理
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
	// すべての敵弾に対して更新処理を行う
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

	CollisionCheckPE(); // �v���C���[�ƓG�̓����蔻����s���֐�
	CollisionCheckPB(); // �v���C���[�ƓG�̒e�̓����蔻����s���֐�
	CollisionCheckEB(); // �G�̒e�ƃp���̓����蔻����s���֐�
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

	// 2. ? すべてのパンの描画処理
	for (auto* bread : breadList)
	{
		bread->Draw(cameraX, cameraY);
	}

	//すべての敵弾の描画処理
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
