#include "Enemy1.h"
#include "GameScene.h"
#include "EnemyBulletBase.h"
#include "Stage1_EnemyA_Bullet.h"
#include <DxLib.h>

void Enemy1::GameInit(void)
{

}

void Enemy1::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage1_A.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 0.0f;
	// 敵のヒットポイント最大値
	hpMax = 3;
	// ボスではない
	eob = 0;
}

void Enemy1::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}


	shotTimer++;

	if (shotTimer % 120 == 0)
	{
		Vector2F bulletVel = { -3.0f, 0.0f }; // 弾の速度ベクト
		EnemyBulletBase* newBullet = new BulletST1A();
		
		if (gInst != nullptr)
		{
			Vector2F spownPos = this->pos; // 敵の現在位置を取得

			spownPos.x -= 20.0f; // 弾のスポーン位置をトランペットの位置に調整
			spownPos.y -= 10.0f; // 弾のスポーン位置をトランペットの位置に調整

			gInst->AddEnemyBullet(newBullet, spownPos, bulletVel);
		}
	}
}

