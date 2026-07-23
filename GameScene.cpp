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
#include "Donut.h"
#include "DonutRecipe.h"
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

	// ƒXƒe[ƒW”‚É‰‚¶‚Ä“Ç‚İ‚ŞCSVƒtƒ@ƒCƒ‹‚ğØ‚è‘Ö‚¦‚é
	std::string csvPath = "";

	if (currentStageNum == 1)      csvPath = "Data//AGS_Map_School_Enemy.csv";
	else if (currentStageNum == 2) csvPath = "Data//AGS_Map_Office_Enemy.csv";
	else if (currentStageNum == 3) csvPath = "Data//AGS_Map_Street_Enemy.csv";

	// CSVƒtƒ@ƒCƒ‹‚©‚çƒf[ƒ^‚ğ“Ç‚İ‚Ş
	if (!csvPath.empty())
	{
		LoadEnemyCSV(csvPath);
	}
	else
	{
		// CSVƒtƒ@ƒCƒ‹‚ªw’è‚³‚ê‚Ä‚¢‚È‚¢ê‡‚ÌƒGƒ‰[ƒnƒ“ƒhƒŠƒ“ƒO
		AppLogAdd("Error: No CSV file specified for enemy spawn data.\n");
	}

	isClearTriggered = false;
	clearTimer = 0;

	SoundManager::GetInstance().PlayBGM("gameScene");


	buttunImageC = LoadGraph("Image/C.png");
	buttunImageV = LoadGraph("Image/V.png");
	RTImage = LoadGraph("Image/RT.png");
	LTImage = LoadGraph("Image/LT.png");
	attackUIImage = LoadGraph("Image/Bread_Attack.png");
	changeUIImage = LoadGraph("Image/Bread_Change.png");

	if (currentStageNum == 1)
	{
		AddRecipe(new MelonRecipe(2750.0f, 1150.0f));
		AddRecipe(new CroissantRecipe(500.0f, 1150.0f));
		AddRecipe(new DonutRecipe(1500.0f, 1050.0f));
	}
	if (currentStageNum == 2)
	{
		AddRecipe(new MelonRecipe(2500.0f, 1050.0f));
		AddRecipe(new CroissantRecipe(500.0f, 1150.0f));
		AddRecipe(new DonutRecipe(1500.0f, 1050.0f));
	}
	if (currentStageNum == 3)
	{
		AddRecipe(new MelonRecipe(2500.0f, 1050.0f));
		AddRecipe(new CroissantRecipe(500.0f, 1150.0f));
		AddRecipe(new DonutRecipe(1500.0f, 1050.0f));
	}
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
	clsDx(); //@ƒvƒŠƒ“ƒgƒNƒŠƒA

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
						  Donut* donut = dynamic_cast<Donut*>(bread);
						  if (melon != nullptr)
						  {
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(3);  
								if (enemys[i]->GetAlive() == false && enemys[i]->EoB > 5)
								{
									// ƒ{ƒXŒ‚”jŒã­‚µ‘Ò‚Â
									for (int CLEARTIMER = 0; CLEARTIMER < 120; CLEARTIMER++)
									{
										if (CLEARTIMER > 90) {
											isClearTriggered = true;
										}
									}
						  		}
						  	// ƒƒƒ“ƒpƒ“‚¾‚Á‚½ê‡‚Í”j—ô‚³‚¹‚éi“à•”‚Å¬‚³‚Èƒpƒ“‚ª¶¬‚³‚êA©g‚Í€–S‚·‚éj
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
						  else if (donut != nullptr)
						  {
							  SoundManager::GetInstance().PlaySE("damage");

							  // ãƒ‰ãƒ¼ãƒŠãƒ„ã®ç¾åœ¨ã®ã‚µã‚¤ã‚ºã«å¿œã˜ãŸãƒ€ãƒ¡ãƒ¼ã‚¸ã‚’ä¸ãˆã‚‹
							  enemys[i]->SetDamage(donut->GetCurrentDamage());

							  if (enemys[i]->GetAlive() == false && enemys[i]->EoB > 5)
							  {
								  isClearTriggered = true;
							  }

							  // ãƒ‰ãƒ¼ãƒŠãƒ„æ¶ˆæ»…ï¼ˆè²«é€šã•ã›ãŸã„å ´åˆã¯ Kill() ã‚’å‘¼ã°ãªã„é¸æŠã‚‚ã‚¢ãƒªï¼‰
							  donut->Kill();
						  }
						  else
						  {
							  SoundManager::GetInstance().PlaySE("damage");
							  enemys[i]->SetDamage(1); 
							  if (enemys[i]->GetAlive() == false && enemys[i]->EoB > 5)
							  {
								  // ƒ{ƒXŒ‚”jŒã­‚µ‘Ò‚Â
								  for (int CLEARTIMER = 0; CLEARTIMER < 120; CLEARTIMER++)
								  {
									  if (CLEARTIMER > 90) {
										  isClearTriggered = true;
									  }
								  }
							  }
						  	// ’Êí‚Ìƒpƒ“‚¾‚Á‚½ê‡‚Í‚»‚Ì‚Ü‚ÜÁ‚·
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
		// ‚Ü‚¾¶¬‚³‚ê‚Ä‚¨‚ç‚¸AƒJƒƒ‰‚Ì‰E’[i‰æ–ÊŠO‚Ì­‚µæj‚É‹ß‚Ã‚¢‚½‚ç¶¬
		if (!spawn.isSpawned && spawn.spawnX < cameraX + SCREEN_WIDTH + 100)
		{
			// spawn.enemyType‚É‰‚¶‚Ä“KØ‚ÈEnemyBase”h¶ƒNƒ‰ƒX‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ğ¶¬
			EnemyBase* newEnemy = CreateEnemyFromType(spawn.enemyType);

			if (newEnemy != nullptr)
			{
				newEnemy->SystemInit(this);
				newEnemy->GameInit(Vector2F(spawn.spawnX, spawn.spawnY));
				enemys.push_back(newEnemy);
			}

			spawn.isSpawned = true; // ¶¬Ï‚İƒtƒ‰ƒO‚ğ—§‚Ä‚é
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
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDSE);
			stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUNDSG);
			stage->Draw(cameraX, cameraY, LAYER_OBJECTSE);
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
		//DrawFormatString(60, 200, GetColor(255, 255, 0), "Player X: %.1f, Y: %.1f", player->GetPosX(), player->GetPosY());
		//DrawFormatString(60, 230, GetColor(255, 255, 0), "Camera X: %.1f, Y: %.1f", cameraX, cameraY);


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

		int currentTypeIdx = static_cast<int>(player->GetCurrentBreadType());
		int currentTimer = player->GetShotBreadTimer(currentTypeIdx); 
		int maxCoolTime = player->GetMaxCoolTime(currentTypeIdx); 

		// =========================================================
		// è¿½åŠ : ç”»é¢ä¸‹ã«è§£æ”¾æ¸ˆã¿ã®ãƒ‘ãƒ³ä¸€è¦§ã‚’è¡¨ç¤ºï¼ˆæ¨ªä¸¦ã³ï¼‰
		// =========================================================
		int listStartX = 420;                // HPã‚²ãƒ¼ã‚¸ã®å³å´ã«é…ç½®
		int listStartY = SCREEN_HEIGHT - 90; // ç”»é¢ä¸‹ã®é«˜ã•
		int listIconSize = 64;               // å„ãƒ‘ãƒ³ã®ã‚¢ã‚¤ã‚³ãƒ³ã‚µã‚¤ã‚º
		int spacing = 16;                    // ã‚¢ã‚¤ã‚³ãƒ³åŒå£«ã®é–“éš”

		int maxTypes = static_cast<int>(Player::BREAD_TYPE::MAX);

		for (int i = 0; i < maxTypes; i++)
		{
			// ãƒ‘ãƒ³ãŒè§£æ”¾ã•ã‚Œã¦ã„ã‚‹ã‹ãƒã‚§ãƒƒã‚¯
			bool isUnlocked = player->IsBreadUnlocked(i);

			// å„ãƒ‘ãƒ³ã®ç”»åƒãƒãƒ³ãƒ‰ãƒ«ã‚’é¸æŠ
			int iconHandle = -1;
			if (i == 0)      iconHandle = LoadGraph("image/bread.png");
			else if (i == 1) iconHandle = LoadGraph("image/melonpan.png");
			else if (i == 2) iconHandle = LoadGraph("image/croissant.png");
			else if (i == 3) iconHandle = LoadGraph("image/donut.png");

			int itemX = listStartX + i * (listIconSize + spacing);
			int itemY = listStartY;

			if (isUnlocked)
			{
				// ç¾åœ¨é¸æŠä¸­ã®ãƒ‘ãƒ³ãªã‚‰æ ã‚’é»„è‰²ï¼ˆãƒã‚¤ãƒ©ã‚¤ãƒˆï¼‰ã€ãã‚Œä»¥å¤–ã¯ç™½ã§è¡¨ç¤º[cite: 19]
				unsigned int borderColor = (i == currentTypeIdx) ? GetColor(255, 255, 0) : GetColor(255, 255, 255);

				// é»’èƒŒæ™¯æ 
				DrawRoundRect(itemX, itemY, itemX + listIconSize, itemY + listIconSize, 8, 8, GetColor(0, 0, 0), TRUE);

				// ãƒ‘ãƒ³ç”»åƒã‚’æç”»
				if (iconHandle != -1)
				{
					DrawExtendGraph(itemX, itemY, itemX + listIconSize, itemY + listIconSize, iconHandle, TRUE);
				}

				// å„ãƒ‘ãƒ³ã®å€‹åˆ¥ã‚¯ãƒ¼ãƒ«ã‚¿ã‚¤ãƒ å½±è¡¨ç¤º
				int cdTimer = player->GetShotBreadTimer(i);
				int maxCD = player->GetMaxCoolTime(i);
				if (cdTimer > 0 && maxCD > 0)
				{
					float rate = (float)cdTimer / (float)maxCD;
					int shadowH = (int)(listIconSize * rate);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
					DrawRoundRect(itemX, itemY + (listIconSize - shadowH), itemX + listIconSize, itemY + listIconSize, 8, 8, GetColor(0, 0, 0), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

				// å¤–æ æç”»
				DrawRoundRect(itemX, itemY, itemX + listIconSize, itemY + listIconSize, 8, 8, borderColor, FALSE);
			}
			else
			{
				// æœªè§£æ”¾ã®ãƒ‘ãƒ³ã¯éµãƒãƒ¼ã‚¯é¢¨ï¼ˆè–„ã„æš—è‰²ï¼‹ã€Œ?ã€ãƒãƒ¼ã‚¯ï¼‰ã§è¡¨ç¾
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
				DrawRoundRect(itemX, itemY, itemX + listIconSize, itemY + listIconSize, 8, 8, GetColor(30, 30, 30), TRUE);
				DrawRoundRect(itemX, itemY, itemX + listIconSize, itemY + listIconSize, 8, 8, GetColor(120, 120, 120), FALSE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				SetFontSize(24);
				DrawString(itemX + 24, itemY + 18, "?", GetColor(180, 180, 180));
			}
		}



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
		else if (currentTypeIdx == 3) // DONUT
		{
			breadImg = LoadGraph("image/donut.png");
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



		int btnSize = 64;

		// Cã‚­ãƒ¼ï¼ˆåˆ‡ã‚Šæ›¿ãˆï¼‰ã®æç”»
		DrawExtendGraph(uiX - 208, uiY + 112, uiX -208 + btnSize, uiY + 112 + btnSize, buttunImageV, TRUE);

		// Vã‚­ãƒ¼ï¼ˆæ”»æ’ƒ/æŠ•ã’ã‚‹ï¼‰ã®æç”»
		DrawExtendGraph(uiX - 208, uiY + 192, uiX - 208 + btnSize, uiY + 192 + btnSize, buttunImageC, TRUE);
	
		DrawExtendGraph(uiX - 272, uiY + 112, uiX - 272 + btnSize, uiY + 112 + btnSize, LTImage, TRUE);

		DrawExtendGraph(uiX - 272, uiY + 192, uiX - 272 + btnSize, uiY + 192 + btnSize, RTImage, TRUE);

		DrawExtendGraph(uiX - 112, uiY + 112, uiX - 112 + btnSize, uiY + 112 + btnSize, attackUIImage, TRUE);

		DrawExtendGraph(uiX - 112, uiY + 192, uiX - 112 + btnSize, uiY + 192 + btnSize, changeUIImage, TRUE);

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

void GameScene::LoadEnemyCSV(const std::string& filePath) // CSVƒtƒ@ƒCƒ‹‚©‚ç“G‚ÌƒXƒ|[ƒ“ƒf[ƒ^‚ğ“Ç‚İ‚ŞŠÖ”
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		// yƒfƒoƒbƒOzƒtƒ@ƒCƒ‹‚ªŠJ‚¯‚È‚©‚Á‚½ƒGƒ‰[‚ğVisual Studio‚Ìo—Í‚Éo‚·
		AppLogAdd("--- [ERROR] CSVƒtƒ@ƒCƒ‹‚ªŠJ‚¯‚Ü‚¹‚ñ‚Å‚µ‚½: %s ---\n", filePath.c_str());
		return;
	}

	// yƒfƒoƒbƒOzƒtƒ@ƒCƒ‹‚ªŠJ‚¯‚½‚±‚Æ‚ğ’m‚ç‚¹‚é
	AppLogAdd("--- [SUCCESS] CSVƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ‚ğŠJn‚µ‚Ü‚·: %s ---\n", filePath.c_str());
	
	std::string line;
	int row = 0; // siY•ûŒü‚Ìƒ}ƒX–Új
	int totalEnemies = 0; // yƒfƒoƒbƒO—pzŒ©‚Â‚©‚Á‚½“G‚Ì‘ƒJƒEƒ“ƒg

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string token;
		int col = 0; // —ñiX•ûŒü‚Ìƒ}ƒX–Új

		while (std::getline(ss, token, ','))
		{
			int enemyType = std::stoi(token);

			// -1 ˆÈŠOi“G‚ª”z’u‚³‚ê‚Ä‚¢‚éƒ}ƒXj‚Ìê‡
			if (enemyType != -1)
			{
				EnemySpawnDate spawnData;
				spawnData.enemyType = enemyType;

				// ƒ}ƒX–Ú‚ÌˆÊ’u‚©‚çƒsƒNƒZƒ‹À•W‚É•ÏŠ·iƒ}ƒX‚Ì’†S‚É”z’u‚³‚ê‚é‚æ‚¤+CHIP_SIZE/2j
				spawnData.spawnX = static_cast<float>(col * CHIP_SIZE + CHIP_SIZE / 2);
				spawnData.spawnY = static_cast<float>(row * CHIP_SIZE + CHIP_SIZE / 2);
				spawnData.isSpawned = false; // ‚Ü‚¾‰æ–Ê‚Éo‚Ä‚¢‚È‚¢

				// oŒ»—\’èƒŠƒXƒg‚É’Ç‰Á
				enemySpawnList.push_back(spawnData);
				totalEnemies++; // ƒJƒEƒ“ƒg‚ğ‘‚â‚·

				// yƒfƒoƒbƒOz“G‚ğ1‘Ì“Ç‚İ‚Ş‚½‚Ñ‚ÉAID‚ÆŒvZ‚³‚ê‚½À•W‚ğo—Í‚·‚é
				AppLogAdd("  [Enemy Found] Type:%d | Row:%d, Col:%d | SpawnPos(X:%.1f, Y:%.1f)\n",
					enemyType, row, col, spawnData.spawnX, spawnData.spawnY);

			}
			col++;
		}
		row++;
	}
	file.close();

	// yƒfƒoƒbƒOzÅI“I‚È“Ç‚İ‚İŒ‹‰Ê‚ğo—Í‚·‚é
	AppLogAdd("--- [FINISH] CSV“Ç‚İ‚İŠ®—¹B‘s”:%d | “o˜^‚³‚ê‚½“G‚Ì‘”:%d ---\n", row, totalEnemies);
}

EnemyBase* GameScene::CreateEnemyFromType(int enemyType) 
{
	EnemyBase* newEnemy = nullptr;

	switch (enemyType)
	{
		// ==========================================
		// ¡ ƒXƒe[ƒW1 ‚Ì“G’è‹`
		// ==========================================
	case 1:  newEnemy = new Enemy1(); break; // ƒUƒR1
	case 2:  newEnemy = new Enemy2(); break; // ƒUƒR2
	case 3:  newEnemy = new Enemy3(); break; // ƒUƒR3
	case 10:                                  // ƒ{ƒX1
	{
		Boss1* boss = new Boss1();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	// ==========================================
	// ¡ ƒXƒe[ƒW2 ‚Ì“G’è‹`
	// ==========================================
	case 4:  newEnemy = new Enemy4(); break; // ƒUƒR4
	case 5:  newEnemy = new Enemy5(); break; // ƒUƒR5
	case 6:  newEnemy = new Enemy6(); break; // ƒUƒR6
	case 11:                                  // ƒ{ƒX2
	{
		Boss2* boss = new Boss2();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	// ==========================================
	// ¡ ƒXƒe[ƒW3 ‚Ì“G’è‹`
	// ==========================================
	case 7:  newEnemy = new Enemy7(); break; // ƒUƒR7
	case 8:  newEnemy = new Enemy8(); break; // ƒUƒR8
	case 9:  newEnemy = new Enemy9(); break; // ƒUƒR9
	case 12:                                  // ƒ{ƒX3
	{
		Boss3* boss = new Boss3();
		boss->SetPlayer(player);
		newEnemy = boss;
	}
	break;

	default:
		break; // ‘z’èŠO‚ÌIDi-1‚È‚Çj‚Í‰½‚à‚µ‚È‚¢
	}

	return newEnemy;
}
