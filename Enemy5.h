#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Enemy5 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	int shotTimer = 0;
	float randSP = 0.0f;
	float randSP2 = 0.0f;
	float randRad = 0.0f;
	float SP = 0.0f;
	float rad = 0.0f;
};