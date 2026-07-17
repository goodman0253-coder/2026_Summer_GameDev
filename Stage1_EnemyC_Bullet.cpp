#include "Stage1_EnemyC_Bullet.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool BulletST1C::SystemInit(GameScene* gs)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage1_EnemyC_Bulled.png");
	size = { 16, 16 };
    isRotation = false;
	return (imgHandle != -1);
}

void BulletST1C::SetSpreadVelocity(int index, int totalCount)
{
    float speed = 3.0f;

    // 扇状の中心角度（左向きをPIとする）
    float centerAngle = 0.0f;

    // 扇の広がり（90度＝PI/2）
    float angleRange = 3.14159f;

    // 等間隔に角度を割り振ります
    float angle = (2.0f * 3.14159f * index) / totalCount;

    // 速度ベクトル（X, Y）を決定
    this->velocity.x = std::cos(angle) * speed;
    this->velocity.y = std::sin(angle) * speed;
}

void BulletST1C::Update(void)
{
	EnemyBulletBase::Update();
}

void BulletST1C::Draw(void)
{
	EnemyBulletBase::Draw();
}

bool BulletST1C::Release(void)
{
	return EnemyBulletBase::Release();
}

