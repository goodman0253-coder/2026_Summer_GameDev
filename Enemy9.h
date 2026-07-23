#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Player;

class Enemy9 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	bool CheckGrounded(float checkX, float checkY);
	float fallVy = 0.0f; // —Ž‰º‘¬“x

	float lowspeed = -10.0f;
	float maxspeed = 10.0f;
	float nowspeed = 0.0f;
	int shotTimer = 0;
	Player* player = nullptr;
};