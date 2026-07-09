#include "Enemy8.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

void Enemy8::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(3800.0f, 1225.0f));
}

void Enemy8::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage3_B.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 0.5f;
	// 敵のヒットポイント最大値
	hpMax = 2;
}

void Enemy8::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得

	// プレイヤーの方向を向くように設定
	int PX = (player != nullptr) ? player->GetPosX() : 0;
	Vector2F playerDir = Vector2F(PX - pos.x, 0.0f);
	this->setMoveDirection(playerDir);

	if (player == nullptr) { player = gInst->GetLpPlayer(); }

	// 移動処理のロジック修正
	if (PX < pos.x) {
		animNo = 0; // 左向き（例）
		nowspeed -= 0.5f; // 加速度を少し抑える
	}
	else {
		animNo = 1; // 右向き
		nowspeed += 0.5f;
	}

	// 速度制限と適用
	if (nowspeed < lowspeed) nowspeed = lowspeed;
	if (nowspeed > maxspeed) nowspeed = maxspeed;
	pos.x += nowspeed;
}
