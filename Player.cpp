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
<<<<<<< HEAD

	Run();
	Jump();
=======
    // 前に書いた移動や重力の処理をここに書く
    if (CheckHitKey(KEY_INPUT_RIGHT)) playerPosx += 5.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPosx -= 5.0f;

>>>>>>> 47ac59c752867f8ce9ca122c0543236f31fd0070


	vy += 0.5f; // 重力
	if (vy > 5.0f)
	{
		vy = 5.0f;
	}
	playerPosy += vy; // 座標を更新

	// 地面に衝突したら止まる
	if (playerPosy > 300.0f)
	{
		playerPosy = 300.0f;
		vy = 0.0f;
<<<<<<< HEAD
		
=======
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			Jump();
		}
>>>>>>> 47ac59c752867f8ce9ca122c0543236f31fd0070
	}
}

void Player::Draw(float camX,float camY)
{

	// もし image が -1 (失敗状態) なら、今この瞬間に読み込みを試みる
#if 0 
	if (image == -1) 
	{
		image = LoadGraph("player.png");

		if (image != -1)
		{
		
			printfDx("Draw内読み込み成功_ハンドル: %d\n", image);
		}
		else
		{
			
			printfDx("Draw内読み込み失敗\n");
		}
	}
	printfDx("Handle: %d  Pos: %f, %f\n", image, 30, 30);
#endif
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
	if (playerPosy >= 300)
	{

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			vy = -12.0f;
		}
	}
}