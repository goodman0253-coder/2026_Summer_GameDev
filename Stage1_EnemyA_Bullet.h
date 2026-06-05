#pragma once
#include "EnemyBulletBase.h"
class GameScene;
class BulletST1A : public EnemyBulletBase
{
public:
	bool SystemInit(GameScene* gs) override;
	void Update(void) override;
	void Draw(void) override;
	bool Release(void) override;
private:
	int waveTimer = 0; // 弾の揺れを制御するタイマー
};