#include "DxLib.h"
#include "Application.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "InputManager.h"
#include "Player.h"

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
	if (playerPosy > 500.0f)
	{
		playerPosy = 500.0f;
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

}

void Player::Draw(float camX,float camY)
{

	clsDx();
	printfDx("PlayerPosX: %.1f, PlayerPosY: %.1f, CameraX: %.1f, CameraY: %.1f\n", playerPosx, playerPosy, camX, camY);
	DrawGraph((int)(playerPosx - camX), (int)(playerPosy - camY), playerImageArray[0], TRUE);


}

void Player::Run()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))playerPosx += speed;
	if (CheckHitKey(KEY_INPUT_LEFT))playerPosx -= speed;
#if 0
	if (InputManager::GetInstance().IsNew(KEY_INPUT_LEFT))
	{
		playerPosx =- speed;
	}
	if (InputManager::GetInstance().IsNew(KEY_INPUT_RIGHT))
	{
		playerPosx =+ speed;
	}
#endif

}


void Player::Jump() 
{


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
			vy = -12.0f;
	}
}