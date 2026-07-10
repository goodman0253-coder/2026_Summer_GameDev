#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Player;

class Boss2 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
	void SetPlayer(Player* p) { player = p; }
private:
	int BakHP = 20; // ‘O‰ñ‚ÌHP‚ğ•Û‘¶‚·‚é•Ï”
	Player* player = nullptr;


	// UŒ‚‚ğó‚¯‚é‚Æ’e‚ğ•úË‚·‚é
};