#include "Enemy9.h"

#include "Player.h"
#include "GameScene.h"
#include "EnemyBulletBase.h"
#include "Stage3_EnemyC_Bullet.h"
#include <DxLib.h>

void Enemy9::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(4200.0f, 1000.0f));
}

void Enemy9::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage3_C.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 3.0f;
	// 敵のヒットポイント最大値
	hpMax = 2;
	// ボスではない
	eob = 0;
}

void Enemy9::Update(void)
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
	shotTimer++;

	if (shotTimer >= 30)
	{
		Vector2F bulletVel = { 0.0f, 5.0f }; // 弾の速度ベクト
		EnemyBulletBase* newBullet = new BulletST3C();

		if (gInst != nullptr)
		{
			Vector2F spownPos = this->pos; // 敵の現在位置を取得

			gInst->AddEnemyBullet(newBullet, spownPos, bulletVel);
		}
		shotTimer = 0; // タイマーをリセット
	}
}
