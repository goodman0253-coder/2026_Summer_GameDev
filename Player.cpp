#include "DxLib.h"
#include "Player.h"

Player::Player() 
{
    x = 100.0f; y = 300.0f; vy = 0.0f;
    image = LoadGraph("mario.png");
}

void Player::Update() 
{
    // 前に書いた移動や重力の処理をここに書く
    if (CheckHitKey(KEY_INPUT_RIGHT)) x += 5.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) x -= 5.0f;
	vy += 0.5f; // 重力
	y += vy; // 座標を更新
	// 地面に衝突したら止まる
	if (y > 300.0f) {
		y = 300.0f;
		vy = 0.0f;
	}
}

void Player::Draw()
{
    DrawGraph((int)x, (int)y, image, TRUE);
}

void Player::Jump() 
{
    vy = -12.0f;
}