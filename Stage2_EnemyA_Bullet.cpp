#include "Stage2_EnemyA_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST2A::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage2_EnemyA_Bulled.png");
	size = { 16, 16 };
	isRotation = false;
	return (imgHandle != -1);
}

void BulletST2A::Update(void)
{
	pos.x += velocity.x;
	pos.y += velocity.y;


	EnemyBulletBase::Update();
}

void BulletST2A::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST2A::Release(void)
{
	return EnemyBulletBase::Release();
}

