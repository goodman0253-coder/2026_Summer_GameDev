#pragma once
#include "EnemyBase.h"
#include "EnemyBulletBase.h"
class Player;

class Boss3 : public EnemyBase
{
public:
	void GameInit(void) override;
	void SetEnemyParam(void) override;
	void Update(void) override;
	void SetPlayer(Player* p) { player = p; }
private:

	Player* player = nullptr;
	// 空中から接近、接触するとまたワープ、ダメージを受けるたびに加速
	int BakHP = 10; // 前回のHPを保存する変数
	int worp = 0; // ワープの方向を決定する変数
};