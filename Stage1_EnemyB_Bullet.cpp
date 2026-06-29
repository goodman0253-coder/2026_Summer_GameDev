#include "Stage1_EnemyB_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST1B::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage1_EnemyB_Bulled.png");
	size = { 16, 16 };
	return (imgHandle != -1);
}

void BulletST1B::Update(void)
{
	pos.x += velocity.x;
	pos.y += velocity.y;


	EnemyBulletBase::Update();
}

void BulletST1B::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST1B::Release(void)
{
	return EnemyBulletBase::Release();
}

