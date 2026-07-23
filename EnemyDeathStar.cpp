#include "EnemyDeathStar.h"
#include "GameScene.h"
#include "Player.h"
#include <DxLib.h>

bool Star::SystemInit(GameScene* gs)
{
	gInst = gs;
	imgHandle = LoadGraph("image/Death_Star.png");
	size = { 32, 32 };
	aliveFlg = true;
	aliveTimer = 180.0f;
	deleteTimer = 0;
	randSP = rand() % 3 + 2;
	randSP2 = rand() % 3 + 2;
	randRad = rand() % 360 - 180; // -180から180までのランダムな整数を生成

	SP = randSP / randSP2;
	rad = (randRad * 3.14159f) / 180.0f; // ラジアンに変換

	velocity.x = cos(rad) * SP;
	velocity.y = sin(rad) * SP;

	return (imgHandle != -1);
}

void Star::Update(void)
{
	if (!aliveFlg)
	{
		return;
	}

	pos.x += velocity.x;
	pos.y += velocity.y;

	deleteTimer++;
	if (deleteTimer >= aliveTimer)
	{
		aliveFlg = false;
	}



	// 弾の位置を移動する(基本移動)
	pos.x += velocity.x;
	pos.y += velocity.y;

	// カメラ座標の取得
	float camX = gInst->GetCameraX();
	float camY = gInst->GetCameraY();

	// カメラの外に出たら消える
	if (pos.x < camX - 20 || pos.x > camX + 1280 + 20 ||
		pos.y < camY - 20 || pos.y > camY + 720 + 20)
	{
		aliveFlg = false;
	}

	aliveTimer -= 1.0f;
	if (aliveTimer <= 0.0f)
	{
		aliveFlg = false;
	}
}

void Star::Draw(void)
{
	if (!aliveFlg)
	{
		return;
	}
	float camX = gInst->GetCameraX();	//カメラ座標X
	float camY = gInst->GetCameraY();	//カメラ座標Y


	DrawRotaGraph(static_cast<int>(pos.x - camX),
		static_cast<int>(pos.y - camY),
		1.0,0.0,
		imgHandle,
		true);
}

bool Star::Release(void)
{

	if (imgHandle != -1) {
		DeleteGraph(imgHandle) == -1;
		imgHandle = -1;
	}
	return true;
}
