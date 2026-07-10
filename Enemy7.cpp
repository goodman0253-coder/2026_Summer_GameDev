#include "Enemy7.h"
#include "GameScene.h"
#include <DxLib.h>

void Enemy7::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(3400.0f, 1225.0f));
}

void Enemy7::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage3_A.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 2.0f;
	// 敵のヒットポイント最大値
	hpMax = 3;
	// ボスではない
	eob = 0;
}

void Enemy7::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得


	pos.x -= speed; // 敵の移動速度を設定
	
}