#include "DxLib.h"
#include "Application.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "InputManager.h"
#include "Player.h"
#include "BreadBase.h"
#include "Bread.h"
#include "GameScene.h"


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
	playerPosy = 100;
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
	if (playerPosy > 1000.0f)
	{
		playerPosy = 1000.0f;
		vy = 0.0f;
		Jump();
	}

	if (playerPosx < 100.0f)
	{
		playerPosx = 100.0f;

	}	
	
	if (playerPosx > 6400.0f)
	{
		playerPosx = 6400.0f;

	}

	if (shotCoolTime > 0)
	{
		shotCoolTime--;
	}

	if (CheckHitKey(KEY_INPUT_V) && shotCoolTime == 0)
	{
		// パンを生成する（プレイヤーの中心付近から発射）
		float spawnX = playerPosx;
		float spawnY = playerPosy;

		// ⭕ 基本のパン（Bread）のインスタンスを作成
		Bread* newBread = new Bread(spawnX, spawnY, playerDir);

		if (gameScene != nullptr)
		{
			gameScene->AddBread(newBread);
		}

		// クールタイムを3秒（1秒=60フレーム × 3 = 180フレーム）に設定
		shotCoolTime = 180;
	}

}

void Player::Draw(float camX,float camY)
{

	clsDx();
	printfDx("PlayerPosX: %.1f, PlayerPosY: %.1f, CameraX: %.1f, CameraY: %.1f\n", playerPosx, playerPosy, camX, camY);
	

	// 描画する画面上の座標を計算
	int drawX = (int)(playerPosx - camX);
	int drawY = (int)(playerPosy - camY);

	// ⭕ プレイヤーの向きが「左（LEFT）」のときだけ画像を左右反転して描画する
	if (playerDir == AsoUtility::DIR::LEFT)
	{
		// DrawTurnGraph( x座標, y座標, グラフィックハンドル, 透過フラグ )
		DrawTurnGraph(drawX, drawY, playerImageArray[0], TRUE);
	}
	else
	{
		// 右向き、あるいは上下を向いているときは通常通り描画
		DrawGraph(drawX, drawY, playerImageArray[0], TRUE);
	}

}

void Player::Run()
{
	bool isMoving = false;
	AsoUtility::DIR moveDir = AsoUtility::DIR::MAX; // 初期値として無効な値を設定

	if (CheckHitKey(KEY_INPUT_UP))
	{
		moveDir = AsoUtility::DIR::UP;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		moveDir = AsoUtility::DIR::DOWN;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		moveDir = AsoUtility::DIR::LEFT;
		isMoving = true;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
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


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
			vy = -12.0f;
	}
}