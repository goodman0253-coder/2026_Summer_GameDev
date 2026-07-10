#include <DxLib.h>
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
#include "BreadBase.h"
#include "Bread.h"
#include "Melonpan.h"
#include "MelonpanRecipe.h"


GameScene::GameScene()
{
#if 0
	enemys.push_back(new Enemy1, new Enemy2, new Enemy3, new Enemy4, new Enemy5, new Enemy6, new Enemy7, new Enemy8, new Enemy9, new Boss1()); // ?G??C???X?^???X??????????X?g????
	for (int i = 0; i < enemys.size();i++)
	{
		//if (!enemys[i]->SystemInit(this))
		//{
			//printfDx("?G???????????s");
		//}
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
	 
	if (currentStageNum == 1)
	{
		EnemyBase* newEnemy = new Enemy1();
		if (newEnemy != nullptr)
		{
			// this (GameScene) ??G??m????n???I
			newEnemy->SystemInit(this);

			// GameInit?????i??????u????j
			newEnemy->GameInit();

			// ?????????????G?????X?g??o?^
			enemys.push_back(newEnemy);
		}

		EnemyBase* newEnemy2 = new Enemy2();
		if (newEnemy2 != nullptr)
		{
			// this (GameScene) ??G??m????n???I
			newEnemy2->SystemInit(this);

			// GameInit?????i??????u????j
			newEnemy2->GameInit();

			// ?????????????G?????X?g??o?^
			enemys.push_back(newEnemy2);
		}

		EnemyBase* newEnemy3 = new Enemy3();
		if (newEnemy3 != nullptr)
		{
			// this (GameScene) ??G??m????n???I
			newEnemy3->SystemInit(this);

			// GameInit?????i??????u????j
			newEnemy3->GameInit();

			// ?????????????G?????X?g??o?^
			enemys.push_back(newEnemy3);
		}

		EnemyBase* newEnemy4 = new Boss1();
		if (newEnemy4 != nullptr)
		{
			// this (GameScene) ????m????n???I
			newEnemy4->SystemInit(this);
			// GameInit?????i??????u????j
			newEnemy4->GameInit();
			static_cast<Boss1*>(newEnemy4)->SetPlayer(player);
			// ?????????????G?????X?g??o?^
			enemys.push_back(newEnemy4);
		}
	}
	else if (currentStageNum == 2)
	{
		// 2繧ｹ繝�畑縺ｮ謨ｵ縺ｮ驟咲ｽｮ蜃ｦ逅...
	}
	else if (currentStageNum == 3)
	{
		// 3繧ｹ繝�畑縺ｮ謨ｵ縺ｮ驟咲ｽｮ蜃ｦ逅...
	}

	EnemyBase* newEnemy5 = new Enemy5();
	if (newEnemy5 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy5->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy5->GameInit();
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy5);
	}

	EnemyBase* newEnemy6 = new Enemy6();
	if (newEnemy6 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy6->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy6->GameInit();
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy6);
	}

	EnemyBase* newEnemy7 = new Enemy7();
	if (newEnemy7 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy7->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy7->GameInit();
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy7);
	}

	EnemyBase* newEnemy8 = new Enemy8();
	if (newEnemy8 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy8->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy8->GameInit();
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy8);
	}

	EnemyBase* newEnemy9 = new Enemy9();
	if (newEnemy9 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy9->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy9->GameInit();
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy9);
	}

	EnemyBase* newEnemy10 = new Boss1();
	if (newEnemy10 != nullptr)
	{
		// this (GameScene) ??G??m????n???I
		newEnemy10->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy10->GameInit();
		static_cast<Boss1*>(newEnemy10)->SetPlayer(player);
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy10);
	}

	//????N???A
	isClearTriggered = false;
	clearTimer = 0;

	AddRecipe(new MelonRecipe(800.0f, 1150.0f));

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

			newBullet->SystemInit(this); // EnemyBulletBase??SystemInit()??GameScene??C???X?^???X??n??
			newBullet->GameInit(spawnPos, vel); // EnemyBulletBase??GameInit()???????u????x????
			enemyBullets.push_back(newBullet); // GameScene??G?e???X?g????
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
				Vector2F pos = enemyBullets[i]->GetPos(); // EnemyBulletBase ????e????W????
				BX = (int)pos.x;
				BY = (int)pos.y;

				if (PX + 23 < BX + (enemyBullets[i]->GetSize().x / 2) && // ?v???C???[??E?[???G??e????[?????????
					PX + Player::PLAYER_WID - 23 > BX - (enemyBullets[i]->GetSize().x / 2) && // ?v???C???[????[???G??e??E?[???E??????
					PY < BY + (enemyBullets[i]->GetSize().y / 2) && // ?v???C???[????[???G??e???[?????????
					PY + Player::PLAYER_HIG > BY - (enemyBullets[i]->GetSize().y / 2)) // ?v???C???[???[???G??e????[?????????
				{
					player->ApplyDamage(); // ?v???C???[??_???[?W??^????
					enemyBullets[i]->SetAlive(false); // ?G??e??????
				}
			}
		}
	}
}

void GameScene::CollisionCheckPE()
{
	clsDx();

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
					Vector2F pos = enemys[i]->GetEnemyPos(); // EnemyBase EnemyBase ??C???X?^???X????擾
					EX = (int)pos.x;
					EY = (int)pos.y;
					if (enemys[i]->EoB != 10)
					{
						if (PX + 23 < EX + 16 && // ?v???C???[??E?[???G????[?????????
							PX + Player::PLAYER_WID - 23 > EX - 16 && // ?v???C???[????[???G??E?[???E??????
							PY < EY + (enemys[i]->GetEnemySize().y / 2) && // ?v???C???[????[???G???[?????????
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2)) //?v???C???[???[???G????[?????????
						{
							player->ApplyDamage(); // ?v???C???[??_???[?W??^????
							enemys[i]->SetDamage(1); // ?G?l?~?[??_???[?W??^????
						}
					}
					else
					{
						if (PX + 23 < EX + (enemys[i]->GetEnemySize().x / 2) && // ?v???C???[??E?[???G????[?????????
							PX + Player::PLAYER_WID - 23 > EX - (enemys[i]->GetEnemySize().x / 2) && // ?v???C???[????[???G??E?[???E??????
							PY < EY + (enemys[i]->GetEnemySize().y / 2) && // ?v???C???[????[???G???[?????????
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2)) //?v???C???[???[???G????[?????????
						{
							player->ApplyDamage(); // ?v???C???[??_???[?W??^????
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
						  if (melon != nullptr)
						  {
							  enemys[i]->SetDamage(2); 
						  	
						  	// メロンパンだった場合は破裂させる（内部で小さなパンが生成され、自身は死亡する）
						  	melon->Explode();
						  }
						  else
						  {

							  enemys[i]->SetDamage(1); 
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
		cameraY = player->GetPosY() - (SCREEN_HEIGHT / 2);
		if (cameraY >= 800)
		{
			cameraY = 800;
		}
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

		// 繝励Ξ繧､繝､繝ｼ繧呈僑螟ｧ逕ｻ髱｢縺ｮ荳ｭ蠢�↓縺吶ｋ
		cameraX = player->GetPosX() - (viewWidth / 2.0f);

		if (cameraX <= 0)
		{
			cameraX = 0;
		}

		// 繝槭ャ繝怜承遶ｯ蛻ｶ髯舌ｒ迴ｾ蝨ｨ縺ｮ螳溯ｳｪ隕夜㍽蟷�ｼ�iewWidth�峨ｒ蜈�↓邂怜�縺吶ｋ
		float maxCameraX = (Stage::TILE_SIZE * currentWidth) - viewWidth;
		if (cameraX >= maxCameraX)
		{
			cameraX = maxCameraX;
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
			sceneManager->ChangeScene(SCENE_GAMECLEAR);// ?????V?[??????
			return;
		}
	
	}
	if (player != nullptr)
	{
		CollisionCheckPE(); // 
		CollisionCheckPB(); // ?�ｽ�ｽv?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽC?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ[?�ｽ�ｽ��雰?�ｽ�ｽ�悟ｼｾ?�ｽ�ｽ�碁屮�ｿ�ｽ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ髦｡�ｻ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽs?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ�匁腸�ｿ�ｽ
		CollisionCheckEB(); // ?�ｽ�ｽG?�ｽ�ｽ�悟ｼｾ?�ｽ�ｽ��ヱ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ�碁屮�ｿ�ｽ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ髦｡�ｻ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽs?�ｽ�ｽ?�ｽ�ｽ?�ｽ�ｽ�匁腸�ｿ�ｽ
		CollisionCheckPR(); //
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

	if (stage != nullptr && player != nullptr)
	{
		stage->Draw(cameraX, cameraY, LAYER_BACKGROUND);
		stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUND);
	}


	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);
	}

	size_t size = enemys.size(); // �ｽ�ｽG�ｽ�ｽ�後ユ�ｽ�ｽ[�ｽ�ｽu�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�瑚ｦ�ｿｽ�ｽf�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ隰ｫ�ｾ
	std::vector<EnemyBase*>::iterator eitr = enemys.begin(); // �ｽ�ｽC�ｽ�ｽe�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ[�ｽ�ｽ^�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ隰ｫ�ｾ
	for (int ii = 0; ii < size; ii++)
	{
		(*eitr)->Draw();
		eitr++;
	};

	for (auto* recipe : recipeList)
	{
		recipe->Draw(cameraX, cameraY);
	}

	// 2.??????p????`????
	for (auto* bread : breadList)
	{
		bread->Draw(cameraX, cameraY);
	}

	//??????G?e??`????
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Draw();
		}
	}
	if (stage != nullptr)
	{
		// ?O?i??`??
		stage->Draw(cameraX, cameraY, LAYER_OBJECT);

		// ?O?i??`??
		stage->Draw(cameraX, cameraY, LAYER_FOREGROUND);
	}

	SetTransformTo2D(&matUI);

	if (player != nullptr)
	{
		// 繝�ヰ繝�げ逕ｨ繝�く繧ｹ繝郁｡ｨ遉ｺ
		SetFontSize(24);
		DrawFormatString(60, 200, GetColor(255, 255, 0), "Player X: %.1f, Y: %.1f", player->GetPosX(), player->GetPosY());
		DrawFormatString(60, 230, GetColor(255, 255, 0), "Camera X: %.1f, Y: %.1f", cameraX, cameraY);


		//---------------------------------------------
		//  Player縺ｮHP
		int currentHp = player->GetHp();
		int maxHp = 5;

		// Player縺ｮHPUI縺ｮ菴咲ｽｮ
		int gaugeX = 60;
		int gaugeY = SCREEN_HEIGHT - 100; // 1080 - 100 = 980 

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
		//---------------------------------------
	}
}

bool GameScene::Release(void)
{
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
	return true;
}
