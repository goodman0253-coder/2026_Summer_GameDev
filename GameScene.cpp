#include <DxLib.h>
#include "SceneManager.h"
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
#include "Enemy1.h"
#include "Boss1.h"
#include "BreadBase.h"
#include "Bread.h"
#include "Melonpan.h"
#include "MelonpanRecipe.h"


GameScene::GameScene()
{
#if 0
	enemys.push_back(new Enemy1, new Boss1()); // �G�̃C���X�^���X���쐬���ă��X�g�ɒǉ�
	for (int i = 0; i < enemys.size();i++)
	{
		//if (!enemys[i]->SystemInit(this))
		//{
			//printfDx("�G�̏������Ɏ��s");
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
		// this (GameScene) ��G�Ɋm���ɓn���I
		newEnemy->SystemInit(this);

		// GameInit���Ăԁi�����ʒu��ݒ�j
		newEnemy->GameInit();

		// �������������G�����X�g�ɓo�^
		enemys.push_back(newEnemy);
	}

	EnemyBase* newEnemy2 = new Boss1();
	if (newEnemy2 != nullptr)
	{
		// this (GameScene) ��G�Ɋm���ɓn���I
		newEnemy2->SystemInit(this);
		// GameInit���Ăԁi�����ʒu��ݒ�j
		newEnemy2->GameInit();
		static_cast<Boss1*>(newEnemy2)->SetPlayer(player);
		// �������������G�����X�g�ɓo�^
		enemys.push_back(newEnemy2);
	}

	//���̃N���A
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

			newBullet->SystemInit(this); // EnemyBulletBase��SystemInit()��GameScene�̃C���X�^���X��n��
			newBullet->GameInit(spawnPos, vel); // EnemyBulletBase��GameInit()�ɏ����ʒu�Ƒ��x��ݒ�
			enemyBullets.push_back(newBullet); // GameScene�̓G�e���X�g�ɒǉ�
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
				Vector2F pos = enemyBullets[i]->GetPos(); // EnemyBulletBase ����e�̍��W�𓾂�
				BX = (int)pos.x;
				BY = (int)pos.y;

				if (PX + 23 < BX + (enemyBullets[i]->GetSize().x / 2) && // �v���C���[�̉E�[���G�̒e�̍��[��荶�ɂ���ꍇ
					PX + Player::PLAYER_WID - 23 > BX - (enemyBullets[i]->GetSize().x / 2) && // �v���C���[�̍��[���G�̒e�̉E�[���E�ɂ���ꍇ
					PY < BY + (enemyBullets[i]->GetSize().y / 2) && // �v���C���[�̉��[���G�̒e�̏�[��艺�ɂ���ꍇ
					PY + Player::PLAYER_HIG > BY - (enemyBullets[i]->GetSize().y / 2)) // �v���C���[�̏�[���G�̒e�̉��[����ɂ���ꍇ
				{
					player->ApplyDamage(); // �v���C���[�Ƀ_���[�W��^����
					enemyBullets[i]->SetAlive(false); // �G�̒e������
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
					Vector2F pos = enemys[i]->GetEnemyPos(); // EnemyBase EnemyBase �̃C���X�^���X����擾
					EX = (int)pos.x;
					EY = (int)pos.y;
					if (enemys[i]->EoB != 10)
					{
						if (PX + 23 < EX + 16 && // �v���C���[�̉E�[���G�̍��[��荶�ɂ���ꍇ
							PX + Player::PLAYER_WID - 23 > EX - 16 && // �v���C���[�̍��[���G�̉E�[���E�ɂ���ꍇ
							PY < EY + (enemys[i]->GetEnemySize().y / 2) && // �v���C���[�̉��[���G�̏�[��艺�ɂ���ꍇ
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2)) //�v���C���[�̏�[���G�̉��[����ɂ���ꍇ
						{
							player->ApplyDamage(); // �v���C���[�Ƀ_���[�W��^����
							enemys[i]->SetDamage(1); // �G�l�~�[�Ƀ_���[�W��^����
						}
					}
					else
					{
						if (PX + 23 < EX + (enemys[i]->GetEnemySize().x / 2) && // �v���C���[�̉E�[���G�̍��[��荶�ɂ���ꍇ
							PX + Player::PLAYER_WID - 23 > EX - (enemys[i]->GetEnemySize().x / 2) && // �v���C���[�̍��[���G�̉E�[���E�ɂ���ꍇ
							PY < EY + (enemys[i]->GetEnemySize().y / 2) && // �v���C���[�̉��[���G�̏�[��艺�ɂ���ꍇ
							PY + Player::PLAYER_HIG > EY - (enemys[i]->GetEnemySize().y / 2)) //�v���C���[�̏�[���G�̉��[����ɂ���ꍇ
						{
							player->ApplyDamage(); // �v���C���[�Ƀ_���[�W��^����
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
							enemys[i]->SetDamage(2); // エネミーにダメージを与える
						  	// メロンパンだった場合は破裂させる（内部で小さなパンが生成され、自身は死亡する）
						  	melon->Explode();
						  }
						  else
						  {
							enemys[i]->SetDamage(1); // エネミーにダメージを与える
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

	// プレイヤーの矩形情報
	float pX = player->GetPosX();
	float pY = player->GetPosY();
	int pW = Player::PLAYER_WID;
	int pH = Player::PLAYER_HIG;

	for (auto* recipe : recipeList)
	{
		if (!recipe->IsAlive()) continue;

		// アイテムの矩形情報
		float rX = recipe->GetX();
		float rY = recipe->GetY();
		int rW = recipe->GetWidth();
		int rH = recipe->GetHeight();

		// 💡 矩形同士の当たり判定（AABB）
		if (pX < rX + rW && pX + pW > rX &&
			pY < rY + rH && pY + pH > rY)
		{
			// 1. アイテムを消滅状態にする
			recipe->Collect();

			// 2. プレイヤーの該当するパンを解放する！
			player->UnlockBread(recipe->GetUnlockType());

			// 画面確認用デバッグテキスト
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
		if (!(*it)->IsAlive()) // lifeTimer��0�ɂȂ���IsAlive��false�ɂȂ�����
		{
			delete (*it);              // ���������
			it = breadList.erase(it);  // ���X�g���珜�O
		}
		else
		{
			++it; // �����Ă���Ύ���
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

	// ���ׂĂ̓G�e�ɑ΂��čX�V�������s��
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Update();
		}
	}

	// ��ʊO�ɏo���G�e���폜���鏈��
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
	// ���ׂĂ̓G�e�ɑ΂��čX�V�������s��
	// �v���C���[�̍��W(playerX, playerY)����ʒ����ɗ���悤�ɃJ������z�u

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
		// ���ׂẴG�l�~�[�ɑ΂��ē����蔻����`�F�b�N
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
	// ���̃N���A
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
			sceneManager->ChangeScene(SCENE_GAMECLEAR);// ���݂̃V�[����ێ�
			return;
		}
	
	}
	if (player != nullptr)
	{
		CollisionCheckPE(); // 
		CollisionCheckPB(); // ?�v?�?�?�C?�?�?�[?�ƓG?�̒e?�̓�?�?�?�蔻?�?�?�?�s?�?�?�֐�
		CollisionCheckEB(); // ?�G?�̒e?�ƃp?�?�?�̓�?�?�?�蔻?�?�?�?�s?�?�?�֐�
		CollisionCheckPR();
	}
}

void GameScene::Draw(void)
{

	if (stage != nullptr && player != nullptr)
	{
		// �w�i��`��
		stage->Draw(cameraX, cameraY, LAYER_BACKGROUND);

		// ���i��`��
		stage->Draw(cameraX, cameraY, LAYER_MIDDLEGROUND);
	}

	// �v���C���[��`��
	if (player != nullptr)
	{
		player->Draw(cameraX, cameraY);

		//---------------------------------------------
		//  左下にHPゲージを表示する処理
		int currentHp = player->GetHp();
		int maxHp = 5;

		// ゲージを表示する基準位置（左下）
		int gaugeX = 60;
		int gaugeY = SCREEN_HEIGHT - 100; // 1080 - 100 = 980 

		int gaugeWidth = 300;  // ゲージの全体の長さ(最大HP時)
		int gaugeHeight = 24;  // ゲージの縦幅

		// 現在のHPの割合に応じて緑色バーの長さを計算
		int currentBarWidth = (int)((float)currentHp / (float)maxHp * gaugeWidth);

		// 1. ゲージの背景（黒い座布団）
		DrawBox(gaugeX - 10, gaugeY - 45, gaugeX + gaugeWidth + 10, gaugeY + gaugeHeight + 10, GetColor(0, 0, 0), TRUE);

		// 2. テキスト表示 (HP: 5 / 5)
		SetFontSize(24);
		DrawFormatString(gaugeX, gaugeY - 35, GetColor(255, 255, 255), "PLAYER HP: %d / %d", currentHp, maxHp);

		// 3. ゲージの枠（白い線）
		DrawBox(gaugeX, gaugeY, gaugeX + gaugeWidth, gaugeY + gaugeHeight, GetColor(255, 255, 255), FALSE);

		// 4. 中身のバー（HPが残っている時だけ緑色で塗る）
		if (currentHp > 0)
		{
			// 残りHPが1の時はピンチっぽく赤、それ以外は緑にする演出
			unsigned int barColor = (currentHp <= 1) ? GetColor(255, 0, 0) : GetColor(0, 255, 0);
			DrawBox(gaugeX + 2, gaugeY + 2, gaugeX + currentBarWidth - 2, gaugeY + gaugeHeight - 2, barColor, TRUE);
		}

		// 無敵状態のテキストはゲージの少し上にズラして表示
		if (player->IsInvincible())
		{
			SetFontSize(20);
			DrawString(gaugeX, gaugeY - 70, "INVINCIBLE!!", GetColor(255, 0, 0));
		}
		//---------------------------------------------


		//---------------------------------------------
		//パンのクールタイムUI
		int currentTypeIdx = static_cast<int>(player->GetCurrentBreadType());
		int currentTimer = player->GetShotBreadTimer(currentTypeIdx);
		int maxCoolTime = player->GetMaxCoolTime(currentTypeIdx);

		// 表示する右下の基準座標
		int uiX = SCREEN_WIDTH - 300; 
		int uiY = SCREEN_HEIGHT - 300; 
		int iconSize = 256;   // アイコンのサイズ

		// 現在選択されているパンの画像ハンドルを決定
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

		// パンのアイコン画像を描画
		if (breadImg != -1)
		{
			DrawExtendGraph(uiX, uiY, uiX + iconSize, uiY + iconSize, breadImg, TRUE);
		}


		// クールタイムの影演出（下から上に晴れる演出）
		if (currentTimer > 0 && maxCoolTime > 0)
		{
			// クールタイムの残り割合 (1.0 から 0.0 へと減っていく)
			float rate = (float)currentTimer / (float)maxCoolTime;

			// 残り時間（割合）に応じた、影の縦幅を計算
			int shadowHeight = (int)(iconSize * rate);

			int shadowTopY = uiY + (iconSize - shadowHeight);

			// --- 透過ブレンドモードを開始 ---
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180); // 180 = ほどよい暗さの半透明の黒

			// 計算した座標で、アイコンの下端（uiY + iconSize）までを黒い四角で塗りつぶす
			DrawRoundRect(uiX, shadowTopY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(0, 0, 0), TRUE);

			// --- 透過ブレンドモードを必ず解除 ---
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);;
		}

		DrawRoundRect(uiX, uiY, uiX + iconSize, uiY + iconSize, roundRadius, roundRadius, GetColor(255, 255, 255), FALSE);		//---------------------------------------
	}

	size_t size = enemys.size(); // �G�̃e�[�u���̗v�f�����擾
	std::vector<EnemyBase*>::iterator eitr = enemys.begin(); // �C�e���[�^���擾
	for (int ii = 0; ii < size; ii++)
	{
		(*eitr)->Draw();
		eitr++;
	};    

	for (auto* recipe : recipeList)
	{
		recipe->Draw(cameraX, cameraY);
	}

	// 2.���ׂẴp���̕`�揈��
	for (auto* bread : breadList)
	{
		bread->Draw(cameraX, cameraY);
	}

	//���ׂĂ̓G�e�̕`�揈��
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Draw();
		}
	}
	if (stage != nullptr)
	{
		// �O�i��`��
		stage->Draw(cameraX, cameraY, LAYER_OBJECT);

		// �O�i��`��
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

	// --- ��������e�X�g�p�F�n�ʂ�`�� ---
	// ��ʂ̉��̕��ɁA64�s�N�Z�������ɏc��������
	for (int i = 0; i < 20000; i += 64) {
		int x = (int)(i - cameraX);
		DrawLine(x, 0, x, 3000, GetColor(100, 100, 100));
	}
}

bool GameScene::Release(void)
{
	// �G�̉��
	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (enemys[i] != nullptr)
		{
			enemys[i]->Release();
			delete enemys[i];
		}
	}

	// �G�̒e�̉��
	for (size_t i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i] != nullptr)
		{
			enemyBullets[i]->Release();
			delete enemyBullets[i];
		}
	}
	// �p���̉��
	enemyBullets.clear();
	for (auto* bread : breadList)
	{
		delete bread;
	}
	breadList.clear(); // ���X�g���̂̒��g������ۂɂ���
	return true;
}
