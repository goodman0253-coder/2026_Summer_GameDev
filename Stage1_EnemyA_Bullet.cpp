#include "Stage1_EnemyA_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST1A::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage1_EnemyA_Bulled.png");
	size = { 16, 16 };
	return (imgHandle != -1);
}

void BulletST1A::Update(void)
{
	waveTimer++;

	pos.x += velocity.x;
	pos.y += velocity.y;

	if (velocity.x != 0.0f)
	{
		float waveAmplitude = 5.0f; // óhÇÍÇÃêUïù

		float waveSpeed = 0.2f; // óhÇÍÇÃë¨ìx

		pos.y += sinf(static_cast<float>(waveTimer) * waveSpeed) * waveAmplitude;
	}
EnemyBulletBase::Update();
}

void BulletST1A::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST1A::Release(void)
{
	return EnemyBulletBase::Release();
}

