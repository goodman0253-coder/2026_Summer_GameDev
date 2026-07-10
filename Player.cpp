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
#include "SoundManager.h"

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
	
	vy += 0.5f; // 重力加速
	if (vy > 12.0f) vy = 12.0f; // 落下速度の限界値を少し調整（すり抜け防止）

	playerPosy += vy; // Y座標を仮更新

	// Stageのポインタを安全に取得
	Stage* stage = (gameScene != nullptr) ? gameScene->GetLpStage() : nullptr;

	if (stage != nullptr)
	{
		if (vy < 0.0f)
		{
			float headX1 = playerPosx + 4.0f;               // 頭の左側
			float headX2 = playerPosx + PLAYER_WID - 4.0f;  // 頭の右側
			float headY = playerPosy;                       // 頭のてっぺん

			if (stage->CheckCollision(headX1, headY) || stage->CheckCollision(headX2, headY))
			{
				// 天井にぶつかったので、めり込みを戻して落下に転じさせる
				int tileY = (int)(headY / Stage::TILE_SIZE) + 1;
				playerPosy = (float)(tileY * Stage::TILE_SIZE);
				vy = 0.0f; // 上昇ストップ
			}
		}

		float footX1 = playerPosx + 4.0f;               // 足の左側
		float footX2 = playerPosx + PLAYER_WID - 4.0f;  // 足の右側
		float footY = playerPosy + PLAYER_HIG;          // 足元

		if (vy >= 0.0f && (stage->CheckCollision(footX1, footY) || stage->CheckCollision(footX2, footY)))
		{
			int tileY = (int)(footY / Stage::TILE_SIZE);
			playerPosy = (float)(tileY * Stage::TILE_SIZE) - PLAYER_HIG;

			vy = 0.0f;
			jumpableFlg = true;
		}
		else
		{
			jumpableFlg = false;
		}
	}
	else
	{
		if (playerPosy >= 1225.0f)
		{
			playerPosy = 1225.0f;
			vy = 0.0f;
			jumpableFlg = true;
		}
	}

	// ジャンプボタンの入力を受け付ける（着地判定の後に行う）

	if (jumpableFlg == true)
	{
		Jump();
	}


	if (playerPosx < 0)
	{
		playerPosx = 0;
	}	

	if (gameScene != nullptr && gameScene->GetLpStage() != nullptr)
	{
		int currentMapWidth = gameScene->GetLpStage()->Stage::MAP_WIDTH;

		if (gameScene->GetCameraX() == Stage::TILE_SIZE * currentMapWidth - PLAYER_WID - gameScene->GetScreenW())
		{
			if (playerPosx < Stage::TILE_SIZE * currentMapWidth - PLAYER_WID - gameScene->GetScreenW())
			{
				playerPosx = Stage::TILE_SIZE * currentMapWidth - PLAYER_WID - gameScene->GetScreenW();
			}
		}
		if (playerPosx > Stage::TILE_SIZE * currentMapWidth - PLAYER_WID)
		{
			playerPosx = Stage::TILE_SIZE * currentMapWidth - PLAYER_WID;
		}
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
		// ステージ内にパンが0個のときだけ切り替えられる（前のリクエストの処理と組み合わせる場合）
		if (gameScene != nullptr && gameScene->GetBreadCount() == 0)
		{
			BREAD_TYPE nextType = currentBreadType;

			// 解放されているパンが見つかるまで最大でMAX回ループして探す
			for (int i = 0; i < static_cast<int>(BREAD_TYPE::MAX); ++i)
			{
				int nextIdx = static_cast<int>(nextType) + 1;
				if (nextIdx >= static_cast<int>(BREAD_TYPE::MAX))
				{
					nextIdx = 0; // ループして最初に戻す
				}
				nextType = static_cast<BREAD_TYPE>(nextIdx);

				// もしそのパンが解放されていたら、それに決定してループを抜ける
				if (isBreadUnlocked[nextIdx] == true)
				{
					currentBreadType = nextType;
					break;
				}
			}
		}
	}

	breadIdx = static_cast<int>(currentBreadType);

	if ((InputManager::GetInstance().IsTrgDown(KEY_INPUT_V) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)) && shotBreadTimers[breadIdx] <= 0)
	{
		float spawnX = playerPosx;
		float spawnY = playerPosy;

		BreadBase* newBread = nullptr;

		SoundManager::GetInstance().PlaySE("throw");

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
	//DrawFormatString(drawX, drawY - 20, GetColor(0, 255, 255), "[%s,%d]", breadName ,shotBreadTimers[breadIdx]);


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
		float moveSpeed = 6.0f;

		//SoundManager::GetInstance().PlaySE("run");

		Stage* stage = (gameScene != nullptr) ? gameScene->GetLpStage() : nullptr;

		if (playerDir == AsoUtility::DIR::LEFT)
		{
			// 左に移動した仮の座標（少し余裕を持たせるため +4px 内側から判定）
			float nextLeftX = playerPosx - moveSpeed;
			float checkY1 = playerPosy + 1.0f;                  // プレイヤーの頭付近
			float checkY2 = playerPosy + PLAYER_HIG - 1.0f;     // プレイヤーの足元付近

			if (stage != nullptr && (stage->CheckCollision(nextLeftX, checkY1) || stage->CheckCollision(nextLeftX, checkY2)))
			{
				// 壁があるので進めない。壁の右端にぴったり補正
				int tileX = (int)(nextLeftX / Stage::TILE_SIZE) + 1;
				playerPosx = (float)(tileX * Stage::TILE_SIZE);
			}
			else
			{
				playerPosx -= moveSpeed;
			}
		}
		else if (playerDir == AsoUtility::DIR::RIGHT)
		{
			// 右に移動した仮の座標（右端の座標は playerPosx + PLAYER_WID）
			float nextRightX = playerPosx + PLAYER_WID + moveSpeed;
			float checkY1 = playerPosy + 1.0f;
			float checkY2 = playerPosy + PLAYER_HIG - 1.0f;

			if (stage != nullptr && (stage->CheckCollision(nextRightX, checkY1) || stage->CheckCollision(nextRightX, checkY2)))
			{
				// 壁があるので進めない。壁の左端にぴったり補正
				int tileX = (int)(nextRightX / Stage::TILE_SIZE);
				playerPosx = (float)(tileX * Stage::TILE_SIZE) - PLAYER_WID;
			}
			else
			{
				playerPosx += moveSpeed;
			}
		}
	}

	if (isMoving == true && jumpableFlg == true)
	{
		// 鳴らしたい足音（"run"）のハンドルを SoundManager から直接確認して再生
		int runHandle = SoundManager::GetInstance().GetSEHandle("run");
		if (runHandle != -1)
		{
			// まだ鳴っていなければ、ループモードで再生開始！
			if (CheckSoundMem(runHandle) == 0)
			{
				PlaySoundMem(runHandle, DX_PLAYTYPE_LOOP, TRUE);
			}
		}
	}
	else
	{
		// 移動をやめた、またはジャンプした（空中に浮いた）瞬間に足音を止める！
		int runHandle = SoundManager::GetInstance().GetSEHandle("run");
		if (runHandle != -1)
		{
			if (CheckSoundMem(runHandle) == 1)
			{
				StopSoundMem(runHandle);
			}
		}
	}
}


void Player::Jump() 
{


	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
			vy = -15.0f;
			jumpableFlg = false;
			SoundManager::GetInstance().PlaySE("jump");
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

void Player::Die()
{
	if (playerPosy > 1500.0f)
	{
		hp = 0; // 体力を0にする
	}
}
