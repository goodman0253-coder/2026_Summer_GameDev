#include "DxLib.h"
#include "Application.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "InputManager.h"
#include "Player.h"
#include "BreadBase.h"
#include "Bread.h"
#include "Melonpan.h"
#include "GameScene.h"
#include "Stage.h"

Player::Player() 
{

	LoadDivGraph("image/playerV2.png", PLAYER_ANIM_MAX, PLAYER_ANIM_XNUM, PLAYER_ANIM_YNUM, PLAYER_WID, PLAYER_HIG, playerImageArray);

}

Player::~Player()
{

}


bool Player::SystemInit()
{

	return true;

}

bool Player::GameInit()
{
	vy = 0.0f;
	playerPosx = 100;
	playerPosy = 1200;

	for (int i = 0; i < static_cast<int>(BREAD_TYPE::MAX); ++i)
	{
		shotBreadTimers[i] = 0;
	}

	return true;
}

void Player::Update() 
{

	Run();
	
	vy += 0.5f; // 重力
	if (vy > 5.0f)
	{
		vy = 5.0f;
	}
	playerPosy += vy; // 座標を更新

	// 地面に衝突したら止まる
	if (playerPosy >= 1225.0f)
	{
		playerPosy = 1225.0f;
		vy = 0.0f;
		jumpableFlg = true;

	}

	if (jumpableFlg == true)
	{
		Jump();
	}

	if (playerPosx < 0)
	{
		playerPosx = 0;
	}	
	if (gameScene->GetCameraX() == Stage::TILE_SIZE * Stage::MAP_WIDTH - PLAYER_WID - gameScene->GetScreenW())
	{
		if (playerPosx < Stage::TILE_SIZE * Stage::MAP_WIDTH - PLAYER_WID - gameScene->GetScreenW())
		{
			playerPosx = Stage::TILE_SIZE * Stage::MAP_WIDTH - PLAYER_WID - gameScene->GetScreenW();
		}
	}
	if (playerPosx > Stage::TILE_SIZE * Stage::MAP_WIDTH - PLAYER_WID)
	{
		playerPosx = Stage::TILE_SIZE * Stage::MAP_WIDTH - PLAYER_WID;

	}

	for (int i = 0; i < static_cast<int>(BREAD_TYPE::MAX); ++i)
	{
		if (shotBreadTimers[i] > 0)
		{
			shotBreadTimers[i]--; // 各パン個別に1フレームずつ減らす
		}
	}


	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_C) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::L_TRIGGER))
	{
		// 次の種類に進める
		int nextType = static_cast<int>(currentBreadType) + 1;

		// もし最大数（MAX）に達したら、最初の種類（NORMAL）に戻す
		if (nextType >= static_cast<int>(BREAD_TYPE::MAX))
		{
			nextType = 0;
		}

		currentBreadType = static_cast<BREAD_TYPE>(nextType);
	}

	breadIdx = static_cast<int>(currentBreadType);

	if ((InputManager::GetInstance().IsTrgDown(KEY_INPUT_V) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)) && shotBreadTimers[breadIdx] <= 0)
	{
		float spawnX = playerPosx;
		float spawnY = playerPosy;

		BreadBase* newBread = nullptr;


		breadThrowPoseFlg = true;

		switch (currentBreadType)
		{
		case BREAD_TYPE::NORMAL:
		{
			newBread = new Bread(spawnX, spawnY, playerDir); // 通常のパン
			shotBreadTimers[breadIdx] = MAX_COOL_TIME[breadIdx];
		}
		break;
		case BREAD_TYPE::MELONPAN:
		{
			newBread = new Melonpan(spawnX, spawnY, playerDir, gameScene);
			shotBreadTimers[breadIdx] = MAX_COOL_TIME[breadIdx];
		}
		break;
		}

		// 安全にGameSceneの管理リストに追加する
		if (newBread != nullptr && gameScene != nullptr)
		{
			gameScene->AddBread(newBread);

		}
	}

	if (breadThrowPoseFlg == true)
	{
		breadThrowPoseTime--;
		if (breadThrowPoseTime <= 0)
		{
			breadThrowPoseFlg = false;
		}

	}
	else if (breadThrowPoseFlg == false)
	{
		breadThrowPoseTime = 60;
	}

	if (isMoving == true)
	{
		animTimer++;
		if (animTimer >= ANIM_SPEED)
		{
			
			animTimer = 0;
			animNoNow++;

		}
		if (animNoNow > ANIM_RUN_NO_MAX)
		{

			animNoNow = 1;

		}

	}

	if (invincibleTimer > 0)
	{
		invincibleTimer--; // 1フレームごとに1減らす（60フレーム = 1秒）
	}
}

void Player::Draw(float camX,float camY)
{

	//clsDx();
	//printfDx("PlayerPosX: %.1f, PlayerPosY: %.1f, CameraX: %.1f, CameraY: %.1f\n", playerPosx, playerPosy, camX, camY);
	if (IsInvincible())
	{
		if ((invincibleTimer / 4) % 2 == 0)
		{
			return; // このフレームは描画をスキップ（非表示にして点滅を表現）
		}
	}



	// 描画する画面上の座標を計算
	int drawX = (int)(playerPosx - camX);
	int drawY = (int)(playerPosy - camY);

	if (isMoving == true)
	{
		animState = ANIM_STATE::RUN;
	}
	else
	{
		animState = ANIM_STATE::IDLE;
	}
	if (breadThrowPoseFlg == true)
	{
		animState = ANIM_STATE::THROW;
	}
	if (jumpableFlg == false && breadThrowPoseFlg == false)
	{
		animState = ANIM_STATE::JUMP;
	}

	switch (animState)
	{
	case ANIM_STATE::IDLE:
	{
		if (playerDir == AsoUtility::DIR::LEFT)
		{
			DrawTurnGraph(drawX, drawY, playerImageArray[0], TRUE);
		}
		else
		{
			DrawGraph(drawX, drawY, playerImageArray[0], TRUE);
		}
	}
		break;
	case ANIM_STATE::JUMP:
	{
		if (playerDir == AsoUtility::DIR::LEFT)
		{
			DrawTurnGraph(drawX, drawY, playerImageArray[2], TRUE);
		}
		else
		{
			DrawGraph(drawX, drawY, playerImageArray[2], TRUE);
		}
	}
		break;
	case ANIM_STATE::RUN:
	{
		if (playerDir == AsoUtility::DIR::LEFT)
		{
			if (animNoNow == 1)
			{
				DrawTurnGraph(drawX, drawY, playerImageArray[0], TRUE);
			}
			if (animNoNow == 2)
			{
				DrawTurnGraph(drawX, drawY, playerImageArray[1], TRUE);
			}
		}
		else
		{
			if (animNoNow == 1)
			{
				DrawGraph(drawX, drawY, playerImageArray[0], TRUE);
			}
			if (animNoNow == 2)
			{
				DrawGraph(drawX, drawY, playerImageArray[1], TRUE);
			}
		}
	}
	break;
	case ANIM_STATE::THROW:
	{
		if (playerDir == AsoUtility::DIR::LEFT)
		{
			DrawTurnGraph(drawX, drawY, playerImageArray[3], TRUE);
		}
		else
		{
			DrawGraph(drawX, drawY, playerImageArray[3], TRUE);
		}
	}
		break;

	}

#if 0
	// プレイヤーの向きが「左（LEFT）」のときだけ画像を左右反転して描画する
	if (playerDir == AsoUtility::DIR::LEFT)
	{
		// DrawTurnGraph( x座標, y座標, グラフィックハンドル, 透過フラグ )
		DrawTurnGraph(drawX, drawY, playerImageArray[0], TRUE);
		if (breadThrowPoseFlg == true)
		{
			DrawTurnGraph(drawX, drawY, playerImageArray[3], TRUE);
		}
		if (jumpableFlg == false && breadThrowPoseFlg == false)
		{
			DrawTurnGraph(drawX, drawY, playerImageArray[2], TRUE);
		}
	}
	else
	{
		// 右向き、あるいは上下を向いているときは通常通り描画
		DrawGraph(drawX, drawY, playerImageArray[0], TRUE);
		if (breadThrowPoseFlg == true)
		{
			DrawGraph(drawX, drawY, playerImageArray[3], TRUE);
		}
		if (jumpableFlg == false && breadThrowPoseFlg == false)
		{
			DrawGraph(drawX, drawY, playerImageArray[2], TRUE);
		}

	}
#endif


	const char* breadName = "NORMAL";
	if (currentBreadType == BREAD_TYPE::MELONPAN)      breadName = "MELONOAN";
	//if (currentBreadType == BREAD_TYPE::CROISSANT) breadName = "CROISSANT";

	// プレイヤーの少し上に現在の選択を表示
	DrawFormatString(drawX, drawY - 20, GetColor(0, 255, 255), "[%s,%d]", breadName ,shotBreadTimers[breadIdx]);
	// 当たり判定の可視化（デバッグ用）


	DrawBox(drawX+23, drawY, drawX + PLAYER_WID-23, drawY + PLAYER_HIG, GetColor(255, 0, 0), FALSE);

}

void Player::Run()
{
	isMoving = false;
	AsoUtility::DIR moveDir = AsoUtility::DIR::MAX; // 初期値として無効な値を設定

	if (InputManager::GetInstance().IsNew(KEY_INPUT_UP) || InputManager::GetInstance().IsNew(KEY_INPUT_W) || InputManager::GetInstance().IsPadAKeyLY(InputManager::JOYPAD_NO::PAD1) < -800)
	{
		moveDir = AsoUtility::DIR::UP;
	}
	else if (InputManager::GetInstance().IsNew(KEY_INPUT_DOWN) || InputManager::GetInstance().IsNew(KEY_INPUT_S) || InputManager::GetInstance().IsPadAKeyLY(InputManager::JOYPAD_NO::PAD1) > 800)
	{
		moveDir = AsoUtility::DIR::DOWN;
	}
	else if (InputManager::GetInstance().IsNew(KEY_INPUT_LEFT) || InputManager::GetInstance().IsNew(KEY_INPUT_A) || InputManager::GetInstance().IsPadAKeyLX(InputManager::JOYPAD_NO::PAD1) < -800)
	{
		moveDir = AsoUtility::DIR::LEFT;
		isMoving = true;
	}
	else if (InputManager::GetInstance().IsNew(KEY_INPUT_RIGHT) || InputManager::GetInstance().IsNew(KEY_INPUT_D) || InputManager::GetInstance().IsPadAKeyLX(InputManager::JOYPAD_NO::PAD1) > 800)
	{
		moveDir = AsoUtility::DIR::RIGHT;
		isMoving = true;
	}


	if (moveDir != AsoUtility::DIR::MAX)
	{
		playerDir = moveDir;
	}

	if (isMoving)
	{
		float moveSpeed = 4.0f;

		switch (playerDir)
		{
		case AsoUtility::DIR::LEFT:
			playerPosx -= moveSpeed;
			break;
		case AsoUtility::DIR::RIGHT:
			playerPosx += moveSpeed;
			break;
		default:
			break;
		}
	}
}


void Player::Jump() 
{


	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
			vy = -15.0f;
			jumpableFlg = false;
	}
}

void Player::ApplyDamage()
{
	// すでに無敵状態、または体力が0ならダメージを通さない
	if (IsInvincible() || hp <= 0)
	{
		return;
	}
	hp -= 1; // 体力を1減らす

	if (hp > 0)
	{
		// まだ生きていれば2秒間（60フレーム×2＝120フレーム）の無敵をつける
		invincibleTimer = 120;
	}
}

