#pragma once
#include "EnemyBulletBase.h"
class GameScene;
class BulletST2B : public EnemyBulletBase
{
public:
	bool SystemInit(GameScene* gs) override;
	void Update(void) override;
	void Draw(void) override;
	bool Release(void) override;
private:
	int deleteTimer = 0; // 弾の寿命を管理するタイマー
	int deleteLimit = 300; // 弾の寿命の上限（フレーム数）
};