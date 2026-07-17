#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Player;

class Enemy8 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	bool CheckGrounded(float checkX, float checkY);
	bool isFalling = false;     // 現在落下中かどうかのフラグ
	float fallVy = 0.0f;        // 毎フレームの縦方向の移動量
	float lowspeed = -15.0f;
	float maxspeed = 15.0f;
	float nowspeed = 0.0f;
	int shotTimer = 0;
	Player* player = nullptr;
};