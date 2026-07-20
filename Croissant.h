#pragma once
#include "BreadBase.h"

class Player;

class Croissant : public BreadBase
{
private:
	enum class State
	{
		FORWARD, // 往路
		FORWARD_UP, // 往路上昇
		UP, // 往路
		BACK_UP, // 復路上昇
		RETURN   // 復路
	};



	State state = State::FORWARD;
	int timer = 0;
	float speed = 6.0f;
	Player* playerLp = nullptr;

	float startX = 0.0f;
	float startY = 0.0f;
	float theta = 0.0f;       // 軌道計算用の角度（ラジアン）
	float maxRangeX = 300.0f; // 横にどれくらい飛ぶか（カーブの横幅）
	float maxRangeY = 300.0f; // 縦にどれくらい膨らむか（カーブの縦幅）
	int directionSign = 1;    // 投げる方向（右: 1, 左: -1）

public:
	// ?? 引数のdirを AsoUtility::DIR に統一
	Croissant(float spawnX, float spawnY, AsoUtility::DIR direction, Player* player);
	virtual ~Croissant() = default;

	void Update() override;
	void Draw(float camX, float camY) override;
};

