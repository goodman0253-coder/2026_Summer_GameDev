#pragma once
#include "EnemyBulletBase.h"
class GameScene;
class BulletST1B : public EnemyBulletBase
{
public:
	bool SystemInit(GameScene* gs) override;
	void Update(void) override;
	void Draw(void) override;
	bool Release(void) override;
private:
};