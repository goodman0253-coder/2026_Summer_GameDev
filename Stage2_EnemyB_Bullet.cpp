#include "Stage2_EnemyB_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST2B::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage2_EnemyB_Bulled.png");
	size = { 16, 16 };
	return (imgHandle != -1);
}

void BulletST2B::Update(void)
{
	pos.x += velocity.x;
	pos.y += velocity.y;

	deleteTimer++;
	if (deleteTimer >= deleteLimit)
	{
		aliveFlg = false;
	}
	EnemyBulletBase::Update();
}

void BulletST2B::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST2B::Release(void)
{
	return EnemyBulletBase::Release();
}

