#include "Stage2_EnemyC_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST2C::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage2_EnemyC_Bulled.png");
	size = { 16, 16 };
	return (imgHandle != -1);
}

void BulletST2C::Update(void)
{
	pos.y += velocity.y;


	EnemyBulletBase::Update();
}

void BulletST2C::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST2C::Release(void)
{
	return EnemyBulletBase::Release();
}

