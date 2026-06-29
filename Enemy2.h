#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Enemy2 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	int shotTimer = 0;
};
