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
#include "Boss1.h"
#include "BreadBase.h"
#include "Bread.h"
#include "Melonpan.h"
#include "MelonpanRecipe.h"


GameScene::GameScene()
{
#if 0
	enemys.push_back(new Enemy1, new Enemy2, new Enemy3, new Boss1()); // ?G??C???X?^???X??????????X?g????
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
	stage->Initialize();
	 
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
		// this (GameScene) ??G??m????n???I
		newEnemy4->SystemInit(this);
		// GameInit?????i??????u????j
		newEnemy4->GameInit();
		static_cast<Boss1*>(newEnemy4)->SetPlayer(player);
		// ?????????????G?????X?g??o?^
		enemys.push_back(newEnemy4);
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
							  enemys[i]->SetDamage(2); // 繧ｨ繝阪Α繝ｼ縺ｫ繝繝｡繝ｼ繧ｸ繧剃ｸ弱∴繧
						  	// 繝｡繝ｭ繝ｳ繝代Φ縺縺｣縺溷ｴ蜷医�遐ｴ陬ゅ＆縺帙ｋ�亥�驛ｨ縺ｧ蟆上＆縺ｪ繝代Φ縺檎函謌舌＆繧後∬�霄ｫ縺ｯ豁ｻ莠｡縺吶ｋ�
						  	// メロンパンだった場合は破裂させる（内部で小さなパンが生成され、自身は死亡する）
						  	melon->Explode();
						  }
						  else
						  {
							  enemys[i]->SetDamage(1); // 繧ｨ繝阪Α繝ｼ縺ｫ繝繝｡繝ｼ繧ｸ繧剃ｸ弱∴繧
						  	// 騾壼ｸｸ縺ｮ繝代Φ縺縺｣縺溷ｴ蜷医�縺昴�縺ｾ縺ｾ豸医☆
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

	// 繝励Ξ繧､繝､繝ｼ縺ｮ遏ｩ蠖｢諠�ｱ
	float pX = player->GetPosX();
	float pY = player->GetPosY();
	int pW = Player::PLAYER_WID;
	int pH = Player::PLAYER_HIG;

	for (auto* recipe : recipeList)
	{
		if (!recipe->IsAlive()) continue;

		// 繧｢繧､繝�Β縺ｮ遏ｩ蠖｢諠�ｱ
		float rX = recipe->GetX();
		float rY = recipe->GetY();
		int rW = recipe->GetWidth();
		int rH = recipe->GetHeight();

		// 庁 遏ｩ蠖｢蜷悟｣ｫ縺ｮ蠖薙◆繧雁愛螳夲ｼ�ABB�
		if (pX < rX + rW && pX + pW > rX &&
			pY < rY + rH && pY + pH > rY)
		{
			// 1. 繧｢繧､繝�Β繧呈ｶ域ｻ�憾諷九↓縺吶ｋ
			recipe->Collect();

			// 2. 繝励Ξ繧､繝､繝ｼ縺ｮ隧ｲ蠖薙☆繧九ヱ繝ｳ繧定ｧ｣謾ｾ縺吶ｋ�
			player->UnlockBread(recipe->GetUnlockType());

			// 逕ｻ髱｢遒ｺ隱咲畑繝�ヰ繝�げ繝�く繧ｹ繝
			// printfDx("BREAD UNLOCKED!\n");
		}
	}
}

void GameScene::Update(void)
{

	if (player != nullptr)
	{
		player->Update();
		cameraY = player->GetPosY() - (SCREEN_HEIGHT / 2);
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
		if (!(*it)->IsAlive()) // lifeTimer??0??????IsAlive??false????????
		{
			delete (*it);              // ?????????
			it = breadList.erase(it);  // ???X?g?????O
		}
		else
		{
			++it; // ?????????????
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

	// ??????G?e??????X?V???????s??
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Update();
		}
	}

	// ???O??o???G?e???????鏈??
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
	// ??????G?e??????X?V???????s??
	// ?v???C???[????W(playerX, playerY)????????????????J??????z?u

	if (player != nullptr)
	{
		if (cameraX != Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH)
		{
			cameraX = player->GetPosX() - (SCREEN_WIDTH / 2);
		}

		if (cameraX <= 0)
		{
			cameraX = 0;
		}
		if (cameraX >= Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH)
		{
			cameraX = Stage::TILE_SIZE * Stage::MAP_WIDTH - Player::PLAYER_WID - SCREEN_WIDTH;
		}
	}



	if (player != nullptr && !player->IsInvincible())
	{
		// ??????G?l?~?[???????????????`?F?b?N
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
	// ????N???A
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
		CollisionCheckPB(); // ?�ｽv?�ｽ?�ｽ?�ｽC?�ｽ?�ｽ?�ｽ[?�ｽﾆ敵?�ｽﾌ弾?�ｽﾌ難ｿｽ?�ｽ?�ｽ?�ｽ阡ｻ?�ｽ?�ｽ?�ｽ?�ｽs?�ｽ?�ｽ?�ｽﾖ撰ｿｽ
		CollisionCheckEB(); // ?�ｽG?�ｽﾌ弾?�ｽﾆパ?�ｽ?�ｽ?�ｽﾌ難ｿｽ?�ｽ?�ｽ?�ｽ阡ｻ?�ｽ?�ｽ?�ｽ?�ｽs?�ｽ?�ｽ?�ｽﾖ撰ｿｽ
		CollisionCheckPR(); //
	}
}

void GameScene::Draw(void)
{

	if (stage != nullptr && player != nullptr)
	{
		// ?w?i??`??
		stage->Draw(cameraX, cameraY, LAYER_BACKGROUND);

		// ???i??`??
		stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUND);
	}

	// ?v???C???[??`??
	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);

		//---------------------------------------------
		//  蟾ｦ荳九↓HP繧ｲ繝ｼ繧ｸ繧定｡ｨ遉ｺ縺吶ｋ蜃ｦ逅
		int currentHp = player->GetHp();
		int maxHp = 5;

		// 繧ｲ繝ｼ繧ｸ繧定｡ｨ遉ｺ縺吶ｋ蝓ｺ貅紋ｽ咲ｽｮ�亥ｷｦ荳具ｼ
		int gaugeX = 60;
		int gaugeY = SCREEN_HEIGHT - 100; // 1080 - 100 = 980 

		int gaugeWidth = 300;  // 繧ｲ繝ｼ繧ｸ縺ｮ蜈ｨ菴薙�髟ｷ縺(譛螟ｧHP譎)
		int gaugeHeight = 24;  // 繧ｲ繝ｼ繧ｸ縺ｮ邵ｦ蟷

		// 迴ｾ蝨ｨ縺ｮHP縺ｮ蜑ｲ蜷医↓蠢懊§縺ｦ邱題牡繝舌�縺ｮ髟ｷ縺輔ｒ險育ｮ
		int currentBarWidth = (int)((float)currentHp / (float)maxHp * gaugeWidth);

		// 1. 繧ｲ繝ｼ繧ｸ縺ｮ閭梧勹�磯ｻ偵＞蠎ｧ蟶�屮�
		DrawBox(gaugeX - 10, gaugeY - 45, gaugeX + gaugeWidth + 10, gaugeY + gaugeHeight + 10, GetColor(0, 0, 0), TRUE);

		// 2. 繝�く繧ｹ繝郁｡ｨ遉ｺ (HP: 5 / 5)
		SetFontSize(24);
		DrawFormatString(gaugeX, gaugeY - 35, GetColor(255, 255, 255), "PLAYER HP: %d / %d", currentHp, maxHp);

		// 3. 繧ｲ繝ｼ繧ｸ縺ｮ譫�育區縺�ｷ夲ｼ
		DrawBox(gaugeX, gaugeY, gaugeX + gaugeWidth, gaugeY + gaugeHeight, GetColor(255, 255, 255), FALSE);

		// 4. 荳ｭ霄ｫ縺ｮ繝舌���P縺梧ｮ九▲縺ｦ縺�ｋ譎ゅ□縺醍ｷ題牡縺ｧ蝪励ｋ�
		if (currentHp > 0)
		{
			// 谿九ｊHP縺1縺ｮ譎ゅ�繝斐Φ繝√▲縺ｽ縺剰ｵ､縲√◎繧御ｻ･螟悶�邱代↓縺吶ｋ貍泌�
			unsigned int barColor = (currentHp <= 1) ? GetColor(255, 0, 0) : GetColor(0, 255, 0);
			DrawBox(gaugeX + 2, gaugeY + 2, gaugeX + currentBarWidth - 2, gaugeY + gaugeHeight - 2, barColor, TRUE);
		}

		// 辟｡謨ｵ迥ｶ諷九�繝�く繧ｹ繝医�繧ｲ繝ｼ繧ｸ縺ｮ蟆代＠荳翫↓繧ｺ繝ｩ縺励※陦ｨ遉ｺ
		if (player->IsInvincible())
		{
			SetFontSize(20);
			DrawString(gaugeX, gaugeY - 70, "INVINCIBLE!!", GetColor(255, 0, 0));
		}
		//---------------------------------------------


		//---------------------------------------------
		//繝代Φ縺ｮ繧ｯ繝ｼ繝ｫ繧ｿ繧､繝UI
		int currentTypeIdx = static_cast<int>(player->GetCurrentBreadType());
		int currentTimer = player->GetShotBreadTimer(currentTypeIdx);
		int maxCoolTime = player->GetMaxCoolTime(currentTypeIdx);

		// 陦ｨ遉ｺ縺吶ｋ蜿ｳ荳九�蝓ｺ貅門ｺｧ讓
		int uiX = SCREEN_WIDTH - 300; 
		int uiY = SCREEN_HEIGHT - 300; 
		int iconSize = 256;   // 繧｢繧､繧ｳ繝ｳ縺ｮ繧ｵ繧､繧ｺ

		// 迴ｾ蝨ｨ驕ｸ謚槭＆繧後※縺�ｋ繝代Φ縺ｮ逕ｻ蜒上ワ繝ｳ繝峨Ν繧呈ｱｺ螳
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

		// 繝代Φ縺ｮ繧｢繧､繧ｳ繝ｳ逕ｻ蜒上ｒ謠冗判
		if (breadImg != -1)
		{
			DrawExtendGraph(uiX, uiY, uiX + iconSize, uiY + iconSize, breadImg, TRUE);
		}


		// 繧ｯ繝ｼ繝ｫ繧ｿ繧､繝縺ｮ蠖ｱ貍泌��井ｸ九°繧我ｸ翫↓譎ｴ繧後ｋ貍泌��
		if (currentTimer > 0 && maxCoolTime > 0)
		{
			// 繧ｯ繝ｼ繝ｫ繧ｿ繧､繝縺ｮ谿九ｊ蜑ｲ蜷 (1.0 縺九ｉ 0.0 縺ｸ縺ｨ貂帙▲縺ｦ縺�￥)
			float rate = (float)currentTimer / (float)maxCoolTime;

			// 谿九ｊ譎る俣�亥牡蜷茨ｼ峨↓蠢懊§縺溘∝ｽｱ縺ｮ邵ｦ蟷�ｒ險育ｮ
			int shadowHeight = (int)(iconSize * rate);

			int shadowTopY = uiY + (iconSize - shadowHeight);

			// --- 騾城℃繝悶Ξ繝ｳ繝峨Δ繝ｼ繝峨ｒ髢句ｧ ---
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180); // 180 = 縺ｻ縺ｩ繧医＞證励＆縺ｮ蜊企乗�縺ｮ鮟

			// 險育ｮ励＠縺溷ｺｧ讓吶〒縲√い繧､繧ｳ繝ｳ縺ｮ荳狗ｫｯ��iY + iconSize�峨∪縺ｧ繧帝ｻ偵＞蝗幄ｧ偵〒蝪励ｊ縺､縺ｶ縺
			DrawRoundRect(uiX, shadowTopY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(0, 0, 0), TRUE);

			// --- 騾城℃繝悶Ξ繝ｳ繝峨Δ繝ｼ繝峨ｒ蠢�★隗｣髯､ ---
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);;
		}

		DrawRoundRect(uiX, uiY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(255, 255, 255), FALSE);		//---------------------------------------
	}
	size_t size = enemys.size(); // �ｽG�ｽﾌテ�ｽ[�ｽu�ｽ�ｽ�ｽﾌ要�ｽf�ｽ�ｽ�ｽ�ｽ�ｽ謫ｾ
	std::vector<EnemyBase*>::iterator eitr = enemys.begin(); // �ｽC�ｽe�ｽ�ｽ�ｽ[�ｽ^�ｽ�ｽ�ｽ謫ｾ
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

	if (player != nullptr)
	{
		SetFontSize(40);
		DrawFormatString(50, 50, GetColor(255, 255, 255), "PLAYER HP: %d / 5", player->GetHp());

		if (player->IsInvincible())
		{
			DrawString(50, 100, "INVINCIBLE!!", GetColor(255, 0, 0));
		}
	}

	// --- ????????e?X?g?p?F?n???`?? ---
	// ??????????A64?s?N?Z????????c????????
	for (int i = 0; i < 20000; i += 64) {
		int x = (int)(i - cameraX);
		DrawLine(x, 0, x, 3000, GetColor(100, 100, 100));
	}
}

bool GameScene::Release(void)
{
	// ?G????
	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Release();
			delete enemys[i];
		}
	}

	// ?G??e????
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Release();
			delete enemyBullets[i];
		}
	}
	// ?p??????
	enemyBullets.clear();
	for (auto* bread : breadList)
	{
		delete bread;
	}
	breadList.clear(); // ???X?g???????g???????????
	return true;
}
