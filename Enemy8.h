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
	float lowspeed = -15.0f;
	float maxspeed = 15.0f;
	float nowspeed = 0.0f;
	int shotTimer = 0;
	Player* player = nullptr;
};