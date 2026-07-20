#include <DxLib.h>
#include <fstream>
#include <sstream>
#include "SceneManager.h"
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "BreadBase.h"
#include "Bread.h"
#include "Melonpan.h"
#include "MelonpanRecipe.h"
#include "MiniMelonpan.h"
#include "Croissant.h"
#include "CroissantRecipe.h"
#include "SoundManager.h"

GameScene::GameScene()
{
#if 0
	enemys.push_back(new Enemy1, new Enemy2, new Enemy3, new Enemy4, new Enemy5, new Enemy6, new Enemy7, new Enemy8, new Enemy9, new Boss1, new Boss2 ,new Boss3());
	for (int i = 0; i < enemys.size();i++)
	{
		enemys[i]->GameInit();
	}
#endif
}

GameScene::~GameScene()
{
	if (player != nullptr) { delete player; player = nullptr; }
	if (stage != nullptr) { delete stage;  stage = nullptr; }

	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Release();
			delete enemys[i];
		}
	}
	enemyBullets.clear();

	for (size_t i = 0; i < recipeList.size(); i++)
	{
		if (recipeList[i] != nullptr) { delete recipeList[i]; }
	}
	recipeList.clear();
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
	stage->Initialize(currentStageNum);
	 
	enemySpawnList.clear();

	// ステージ数に応じて読み込むCSVファイルを切り替える
	std::string csvPath = "";

	if (currentStageNum == 1)      csvPath = "Data//AGS_Map_School_Enemy.csv";
	else if (currentStageNum == 2) csvPath = "Data//AGS_Map_Office_Enemy.csv";
	else if (currentStageNum == 3) csvPath = "Data//AGS_Map_Street_Enemy.csv";

	// CSVファイルからデータを読み込む
	if (!csvPath.empty())
	{
		LoadEnemyCSV(csvPath);
	}
	else
	{
		// CSVファイルが指定されていない場合のエラーハンドリング
		AppLogAdd("Error: No CSV file specified for enemy spawn data.\n");
	}

	isClearTriggered = false;
	clearTimer = 0;

	SoundManager::GetInstance().PlayBGM("gameScene");

	AddRecipe(new MelonRecipe(1500.0f, 1150.0f));
	AddRecipe(new CroissantRecipe(500.0f, 1150.0f));

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
			newBullet->SystemInit(this);
			newBullet->GameInit(spawnPos, vel);
			enemyBullets.push_back(newBullet);
		}
	}
}

void GameScene::CollisionCheckPB()
{
	if (player != nullptr)
	{
		PX = player->GetPosX();
		PY = player->GetPosY();


		for (size_t i = 0; i < enemyBullets.size(); i++)
		{

			if (enemyBullets[i] != nullptr)
			{
				Vector2F pos = enemyBullets[i]->GetPos();
				BX = (int)pos.x;
				BY = (int)pos.y;

				if (PX + 23 < BX + (enemyBullets[i]->GetSize().x / 2) && 
					PX + Player::PLAYER_WID - 23 > BX - (enemyBullets[i]->GetSize().x / 2) && 
					PY < BY + (enemyBullets[i]->GetSize().y / 2) && 
					PY + Player::PLAYER_HIG > BY - (enemyBullets[i]->GetSize().y / 2))
				{
					SoundManager::GetInstance().PlaySE("damage");
					player->ApplyDamage(); 
					enemyBullets[i]->SetAlive(false);
				}
			}
		}
	}
}

void GameScene::CollisionCheckPE()
{
	clsDx(); //　プリントクリア

	if (player != nullptr)
	{
		PX = player->GetPosX();
		PY = player->GetPosY();
		for (int i = 0;i < enemys.size();i++)
		{
			if (enemys[i]->GetAlive() == true)
			{
				if (enemys[i] != nullptr)
				{
					Vector2F pos = enemys[i]->GetEnemyPos(); 
					EX = (int)pos.x;
					EY = (int)pos.y;
					if (enemys[i]->EoB != 10)
					{
						if (PX + 23 < EX + 16 &&
							PX + Player::PLAYER_WID - 23 > EX - 16 && 
							PY < EY + (enemys[i]->GetEnemySize().y / 2) &&
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2))
						{
							player->ApplyDamage();
							SoundManager::GetInstance().PlaySE("damage");
							enemys[i]->SetDamage(1);
						}
					}
					else
					{
						if (PX + 23 < EX + (enemys[i]->GetEnemySize().x / 2) && 
							PX + Player::PLAYER_WID - 23 > EX - (enemys[i]->GetEnemySize().x / 2) && 
							PY < EY + (enemys[i]->GetEnemySize().y / 2) &&
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2))
						{
							SoundManager::GetInstance().PlaySE("damage");
							player->ApplyDamage();
						}
					}
				}
			}
			
		}
	}
}

void GameScene::CollisionCheckEB()
{
	for (int i= 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			if (enemys[i]->GetAlive() == true)
			{
				Vector2F enemyPos = enemys[i]->GetEnemyPos();
				Vector2 enemySize = enemys[i]->GetEnemySize();
				for (auto* bread : breadList)
				{
					if (enemys[i]->GetAlive() && bread->IsAlive())
					{

						Vector2F breadPos = { bread->x, bread->y };
						Vector2 breadSize = { bread->width, bread->height };
						if (breadPos.x < enemyPos.x + (enemySize.x / 2) &&
							breadPos.x + breadSize.x > enemyPos.x - (enemySize.x / 2) &&
							breadPos.y < enemyPos.y + (enemySize.y / 2) &&
							breadPos.y + breadSize.y > enemyPos.y - (enemySize.y / 2))
						{
						  Melonpan* melon = dynamic_cast<Melonpan*>(bread);
						  MiniMelonpan* miniMelon = dynamic_cast<MiniMelonpan*>(bread);
						  Croissant* croissant = dynamic_cast<Croissant*>(bread);
						  if (melon != nullptr)
						  {
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(3);  
								if (enemys[i]->GetAlive() == false && enemys[i]->EoB > 5)
								{
								  	isClearTriggered = true;
						  		}
						  	// メロンパンだった場合は破裂させる（内部で小さなパンが生成され、自身は死亡する）
						  	melon->Explode();
						  }
						  else if (miniMelon != nullptr)
						  {
							  if (enemys[i]->IsInvincible() == true)
							  {
								  continue;
							  }
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(1);
							  miniMelon->Kill();
						  }
						  else if (croissant != nullptr)
						  {
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(2);
							  croissant->Kill();
						  }
						  else
						  {
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(1); 
							  if (enemys[i]->GetAlive() == false && enemys[i]->EoB > 5)
							  {
								  isClearTriggered = true;
							  }
						  	// 通常のパンだった場合はそのまま消す
						  	bread->Kill();
						  }
						}
					}
				}
			}
		}
	}
}


void GameScene::CollisionCheckPR()
{
	if (player == nullptr) return;
	float pX = player->GetPosX();
	float pY = player->GetPosY();
	int pW = Player::PLAYER_WID;
	int pH = Player::PLAYER_HIG;

	for (auto* recipe : recipeList)
	{
		if (!recipe->IsAlive()) continue;
		float rX = recipe->GetX();
		float rY = recipe->GetY();
		int rW = recipe->GetWidth();
		int rH = recipe->GetHeight();
		
		if (pX < rX + rW && pX + pW > rX &&
			pY < rY + rH && pY + pH > rY)
		{
			recipe->Collect();
			player->UnlockBread(recipe->GetUnlockType());
		}
	}
}

void GameScene::Update(void)
{
	float scale = 1.5f;
	float viewWidth = SCREEN_WIDTH / scale;
	float viewHeight = SCREEN_HEIGHT / scale;

	if (player != nullptr)
	{
		player->Update();
		//cameraY = player->GetPosY() - (SCREEN_HEIGHT / 2);
		//if (cameraY >= 800)
		//{
		//	cameraY = 800;
		//}
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
		if (!(*it)->IsAlive()) 
		{
			delete (*it);              
			it = breadList.erase(it); 
		}
		else
		{
			++it; 
		}
	}

	for (auto* recipe : recipeList)
	{
		recipe->Update();
	}

	for (auto it = recipeList.begin(); it != recipeList.end(); )
	{
		if (!(*it)->IsAlive())
		{
			delete* it;
			it = recipeList.erase(it);
		}
		else
		{
			++it;
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
	if (player != nullptr)
	{
		int currentWidth = stage->Stage::MAP_WIDTH;

		cameraX = player->GetPosX() - (viewWidth / 2.0f);

		if (cameraX <= 0)
		{
			cameraX = 0;
		}

		float maxCameraX = (Stage::TILE_SIZE * currentWidth) - viewWidth;
		if (cameraX >= maxCameraX)
		{
			cameraX = maxCameraX;
		}
	}

	for (auto& spawn : enemySpawnList)
	{
		// まだ生成されておらず、カメラの右端（画面外の少し先）に近づいたら生成
		if (!spawn.isSpawned && spawn.spawnX < cameraX + SCREEN_WIDTH + 100)
		{
			// spawn.enemyTypeに応じて適切なEnemyBase派生クラスのインスタンスを生成
			EnemyBase* newEnemy = CreateEnemyFromType(spawn.enemyType);

			if (newEnemy != nullptr)
			{
				newEnemy->SystemInit(this);
				newEnemy->GameInit(Vector2F(spawn.spawnX, spawn.spawnY));
				enemys.push_back(newEnemy);
			}

			spawn.isSpawned = true; // 生成済みフラグを立てる
		}
	}

	if (player != nullptr && !player->IsInvincible())
	{

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

	if (player != nullptr) 
	{
		for (int i = 0;i < enemys.size();i++)
		{
			if (enemys[i]->GetAlive() == false && enemys[i]->hp < 1)
			{

				if (enemys[i]->EoB >0)
				{
					isClearTriggered = true;
				}
			}
		}
	}
		
	if (isClearTriggered)
	{
	
		if(sceneManager != nullptr)
		{
			sceneManager->ChangeScene(SCENE_GAMECLEAR);
			return;
		}
	
	}
	if (player != nullptr)
	{
		CollisionCheckPE();
		CollisionCheckPB();
		CollisionCheckEB();
		CollisionCheckPR();
		player->Die();
	}
}

void GameScene::Draw(void)
{

	float scale = 1.5;
	MATRIX mat = MGetScale(VGet(scale, scale, 1.0f));
	float scaleUI = 1;
	MATRIX matUI = MGetScale(VGet(scaleUI, scaleUI, 1.0f));
	SetTransformTo2D(&mat);

	if (currentStageNum == 1)
	{
		if (stage != nullptr && player != nullptr)
		{
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDSG);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTSE);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDSG);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTSG);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTSI);

		}
	}
	if (currentStageNum == 2)
	{
		if (stage != nullptr && player != nullptr)
		{
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDO);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDO);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTO);

		}
	}
	if (currentStageNum == 3)
	{
		if (stage != nullptr && player != nullptr)
		{
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDTE);
			stage->Draw(cameraX, cameraY, LAYER_BACKGROUNDC);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDTE);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTO);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTC);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTTE);
		}
	}

	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);
	}

	size_t size = enemys.size();
	std::vector<EnemyBase*>::iterator eitr = enemys.begin();
	for (int ii = 0; ii < size; ii++)
	{
		(*eitr)->Draw();
		eitr++;
	};

	for (auto* recipe : recipeList)
	{
		recipe->Draw(cameraX, cameraY);
	}

	for (auto* bread : breadList)
	{
		bread->Draw(cameraX, cameraY);
	}

	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Draw();
		}
	}

	if (currentStageNum == 1)
	{
		if (stage != nullptr && player != nullptr)
		{

			stage->Draw(cameraX, cameraY, LAYER_FOREGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_FOREGROUNDSG);
		}
	}
	if (currentStageNum == 2)
	{
		if (stage != nullptr && player != nullptr)
		{

			stage->Draw(cameraX, cameraY, LAYER_FOREGROUNDO);
		}
	}


	SetTransformTo2D(&matUI);

	if (player != nullptr)
	{
		SetFontSize(24);
		DrawFormatString(60, 200, GetColor(255, 255, 0), "Player X: %.1f, Y: %.1f", player->GetPosX(), player->GetPosY());
		DrawFormatString(60, 230, GetColor(255, 255, 0), "Camera X: %.1f, Y: %.1f", cameraX, cameraY);


		int currentHp = player->GetHp();
		int maxHp = 5;

		int gaugeX = 60;
		int gaugeY = SCREEN_HEIGHT - 100;

		int gaugeWidth = 300;
		int gaugeHeight = 24;

		int currentBarWidth = (int)((float)currentHp / (float)maxHp * gaugeWidth);
		DrawBox(gaugeX - 10, gaugeY - 45, gaugeX + gaugeWidth + 10, gaugeY + gaugeHeight + 10, GetColor(0, 0, 0), TRUE);

		SetFontSize(24);
		DrawFormatString(gaugeX, gaugeY - 35, GetColor(255, 255, 255), "PLAYER HP: %d / %d", currentHp, maxHp);

		DrawBox(gaugeX, gaugeY, gaugeX + gaugeWidth, gaugeY + gaugeHeight, GetColor(255, 255, 255), FALSE);

		if (currentHp > 0)
		{
			unsigned int barColor = (currentHp <= 1) ? GetColor(255, 0, 0) : GetColor(0, 255, 0);
			DrawBox(gaugeX + 2, gaugeY + 2, gaugeX + currentBarWidth - 2, gaugeY + gaugeHeight - 2, barColor, TRUE);
		}

		if (player->IsInvincible())
		{
			SetFontSize(20);
			DrawString(gaugeX, gaugeY - 70, "INVINCIBLE!!", GetColor(255, 0, 0));
		}
		int currentTypeIdx = static_cast<int>(player->GetCurrentBreadType());
		int currentTimer = player->GetShotBreadTimer(currentTypeIdx);
		int maxCoolTime = player->GetMaxCoolTime(currentTypeIdx);

		int uiX = SCREEN_WIDTH - 300;
		int uiY = SCREEN_HEIGHT - 300;
		int iconSize = 256;

		int breadImg = -1;
		if (currentTypeIdx == 0) // NORMAL
		{
			breadImg = LoadGraph("image/bread.png");
		}
		else if (currentTypeIdx == 1) // MELONPAN
		{
			breadImg = LoadGraph("image/melonpan.png");
		}
		else if (currentTypeIdx == 2) // CROISSANT 
		{
			breadImg = LoadGraph("image/croissant.png");
		}

		int roundRadius = 12;

		DrawRoundRect(uiX, uiY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(0, 0, 0), TRUE);

		if (breadImg != -1)
		{
			DrawExtendGraph(uiX, uiY, uiX + iconSize, uiY + iconSize, breadImg, TRUE);
		}

		if (currentTimer > 0 && maxCoolTime > 0)
		{

			float rate = (float)currentTimer / (float)maxCoolTime;

			int shadowHeight = (int)(iconSize * rate);

			int shadowTopY = uiY + (iconSize - shadowHeight);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawRoundRect(uiX, shadowTopY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(0, 0, 0), TRUE);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		DrawRoundRect(uiX, uiY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(255, 255, 255), FALSE);
	}

}

bool GameScene::Release(void)
{
#if 0
	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Release();
			delete enemys[i];
		}
	}

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
	breadList.clear();
#endif
	return true;

}

void GameScene::LoadEnemyCSV(const std::string& filePath) // CSVファイルから敵のスポーンデータを読み込む関数
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		// 【デバッグ】ファイルが開けなかったエラーをVisual Studioの出力に出す
		AppLogAdd("--- [ERROR] CSVファイルが開けませんでした: %s ---\n", filePath.c_str());
		return;
	}

	// 【デバッグ】ファイルが開けたことを知らせる
	AppLogAdd("--- [SUCCESS] CSVファイルの読み込みを開始します: %s ---\n", filePath.c_str());
	
	std::string line;
	int row = 0; // 行（Y方向のマス目）
	int totalEnemies = 0; // 【デバッグ用】見つかった敵の総カウント

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string token;
		int col = 0; // 列（X方向のマス目）

		while (std::getline(ss, token, ','))
		{
			int enemyType = std::stoi(token);

			// -1 以外（＝敵が配置されているマス）の場合
			if (enemyType != -1)
			{
				EnemySpawnDate spawnData;
				spawnData.enemyType = enemyType;

				// マス目の位置からピクセル座標に変換（マスの中心に配置されるよう+CHIP_SIZE/2）
				spawnData.spawnX = static_cast<float>(col * CHIP_SIZE + CHIP_SIZE / 2);
				spawnData.spawnY = static_cast<float>(row * CHIP_SIZE + CHIP_SIZE / 2);
				spawnData.isSpawned = false; // まだ画面に出ていない

				// 出現予定リストに追加
				enemySpawnList.push_back(spawnData);
				totalEnemies++; // カウントを増やす

				// 【デバッグ】敵を1体読み込むたびに、IDと計算された座標を出力する
				AppLogAdd("  [Enemy Found] Type:%d | Row:%d, Col:%d | SpawnPos(X:%.1f, Y:%.1f)\n",
					enemyType, row, col, spawnData.spawnX, spawnData.spawnY);

			}
			col++;
		}
		row++;
	}
	file.close();

	// 【デバッグ】最終的な読み込み結果を出力する
	AppLogAdd("--- [FINISH] CSV読み込み完了。総行数:%d | 登録された敵の総数:%d ---\n", row, totalEnemies);
}

EnemyBase* GameScene::CreateEnemyFromType(int enemyType) 
{
	EnemyBase* newEnemy = nullptr;

	switch (enemyType)
	{
		// ==========================================
		// ■ ステージ1 の敵定義
		// ==========================================
	case 1:  newEnemy = new Enemy1(); break; // ザコ1
	case 2:  newEnemy = new Enemy2(); break; // ザコ2
	case 3:  newEnemy = new Enemy3(); break; // ザコ3
	case 10:                                  // ボス1
	{
		Boss1* boss = new Boss1();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	// ==========================================
	// ■ ステージ2 の敵定義
	// ==========================================
	case 4:  newEnemy = new Enemy4(); break; // ザコ4
	case 5:  newEnemy = new Enemy5(); break; // ザコ5
	case 6:  newEnemy = new Enemy6(); break; // ザコ6
	case 11:                                  // ボス2
	{
		Boss2* boss = new Boss2();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	// ==========================================
	// ■ ステージ3 の敵定義
	// ==========================================
	case 7:  newEnemy = new Enemy7(); break; // ザコ7
	case 8:  newEnemy = new Enemy8(); break; // ザコ8
	case 9:  newEnemy = new Enemy9(); break; // ザコ9
	case 12:                                  // ボス3
	{
		Boss3* boss = new Boss3();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	default:
		break; // 想定外のID（-1など）は何もしない
	}

	return newEnemy;
}
