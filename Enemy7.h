#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Enemy7 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	bool CheckGrounded(float checkX, float checkY);
	bool isFalling = false;     // 現在落下中かどうかのフラグ
	float fallVy = 0.0f;        // 毎フレームの縦方向の移動量
	int shotTimer = 0;
};