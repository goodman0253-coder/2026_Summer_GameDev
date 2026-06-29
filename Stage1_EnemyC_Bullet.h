#pragma once
#include "EnemyBulletBase.h"
#include <cmath>
class GameScene;
class BulletST1C : public EnemyBulletBase
{
public:
	bool SystemInit(GameScene* gs) override;
	void SetSpreadVelocity(int index, int totalCount);
	void Update(void) override;
	void Draw(void) override;
	bool Release(void) override;

	Vector2F GetVelocity() const { return velocity; }
private:
};