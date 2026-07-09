#pragma once
#include "EnemyBulletBase.h"
class GameScene;
class BulletST3C : public EnemyBulletBase
{
public:
	bool SystemInit(GameScene* gs) override;
	void Update(void) override;
	void Draw(void) override;
	bool Release(void) override;
private:
};