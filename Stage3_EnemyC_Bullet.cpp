#include "Stage3_EnemyC_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST3C::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage3_EnemyC_Bulled.png");
	size = { 16, 16 };
	return (imgHandle != -1);
}

void BulletST3C::Update(void)
{
	pos.y += velocity.y;


	EnemyBulletBase::Update();
}

void BulletST3C::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST3C::Release(void)
{
	return EnemyBulletBase::Release();
}

