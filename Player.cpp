#include "DxLib.h"
#include "Player.h"

Player::Player() 
{
	image = -1;

	SystemInit();
}

Player::~Player()
{

}

bool Player::SystemInit()  
{  
	vy = 0.0f;  

	image = LoadGraph("Image/croissant.png");
	if (image == -1) 
	{
		printfDx("画像の読み込みに失敗しました\n");
		return false;
	}

	return true; 
}

bool Player::GameInit()
{
	playerPosx = PLAYER_WID;
	playerPosy = PLAYER_HIG;

	return true;
}

void Player::Update() 
{
    // 前に書いた移動や重力の処理をここに書く
    if (CheckHitKey(KEY_INPUT_RIGHT)) playerPosx += 5.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPosx -= 5.0f;

	vy += 0.5f; // 重力
	playerPosy += vy; // 座標を更新

	// 地面に衝突したら止まる
	if (playerPosy > 300.0f)
	{
		playerPosy = 300.0f;
		vy = 0.0f;
	}
}

void Player::Draw()
{
	//printfDx("Handle: %d  Pos: %f, %f\n", image, 30, 30);
    DrawGraph((int)playerPosx, (int)playerPosy, image, TRUE);
}


void Player::Jump() 
{
    vy = -12.0f;
}