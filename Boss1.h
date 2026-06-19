#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Player;

class Boss1 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
	void SetPlayer(Player* p) { player = p; }
private:
	int PX;
	int PY;
	int JumpTimer;
	bool isJumping = false;     // 現在ジャンプ中（空中）かどうかのフラグ
	float jumpVy = 0.0f;        // 毎フレームの縦方向の移動量
	float jumpVx = 0.0f;        // 毎フレームの横方向の移動量
	const float GRAVITY = 0.5f; // 物理演算用の重力の強さ
	int JumpPow = 20;
	int nowJumpPow = 0;
	int widJumpPow = 0;
	Player* player = nullptr;
};

