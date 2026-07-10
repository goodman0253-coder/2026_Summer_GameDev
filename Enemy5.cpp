#include <cmath>
#include "math.h"
#include "Enemy5.h"
#include "GameScene.h"
#include "EnemyBulletBase.h"
#include "Stage2_EnemyB_Bullet.h"
#include <DxLib.h>

void Enemy5::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(2600.0f, 1225.0f));
}

void Enemy5::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage2_B.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 0.0f;
	// 敵のヒットポイント最大値
	hpMax = 3;
	// ボスではない
	eob = 0;
}

void Enemy5::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	shotTimer++;
	randSP = rand() % 2 + 1;
	randSP2 = rand() % 3 + 15;
	randRad = rand() % 180 - 90; // -90から90までのランダムな整数を生成

	SP = randSP / randSP2;
	rad = (randRad * 3.14159f) / 180.0f; // ラジアンに変換

	if (shotTimer == 5)
	{
		Vector2F bulletVel;

		bulletVel.x = -cos(rad) * SP;
		bulletVel.y = sin(rad) * SP;

		EnemyBulletBase* newBullet = new BulletST2B();

		if (gInst != nullptr)
		{
			Vector2F spownPos = this->pos; // 敵の現在位置を取得

			spownPos.x -= 20.0f; // 弾のスポーン位置を手の位置に調整
			spownPos.y -= 10.0f; // 弾のスポーン位置を手の位置に調整

			gInst->AddEnemyBullet(newBullet, spownPos, bulletVel);
			shotTimer = 0; // タイマーをリセット
		}
	}
}
