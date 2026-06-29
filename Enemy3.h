#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Enemy3 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
private:
	int shotTimer = 0;
	// “G‚Ìó‘Ô‚ğ’è‹`
	enum class ActionState {
		IDLE,       // –³”½‰
		ALERT,      // —\”õ“®ì
		ATTACKING   // UŒ‚’†
	};

	// Œ»İ‚Ìó‘Ô
	ActionState currentState = ActionState::IDLE;

	// ’T’mEUŒ‚‚Ì”ÍˆÍ
	float outerRange = 600.0f; // —\”õ“®ì‚ğn‚ß‚éL‚¢”ÍˆÍ
	float innerRange = 300.0f; // UŒ‚”ÍˆÍ
};