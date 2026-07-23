#include "Boss3.h"
#include "GameScene.h"
#include "Player.h"
#include<DXLib.h>



void Boss3::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(6200.0f, 1225.0f));
	BakHP = hpMax; // 初期HPを保存
}

void Boss3::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "stage3_boss.png";
	// 敵の画像サイズ
	size = { 128, 128 };
	// 敵の移動速度
	speed = 10.5f;
	// 敵のヒットポイント最大値
	hpMax = 10;
	// ボスとして設定
	eob = 10;
}

void Boss3::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得

	speed = 10.5 - BakHP; // HPが減るごとに加速
	int PH = (player != nullptr) ? player->GetHig() : 0;
	int PW = (player != nullptr) ? player->GetWid() : 0;
	// プレイヤーの位置を取得

	int PX = (player != nullptr) ? player->GetPosX() : 0;
	int PY = (player != nullptr) ? player->GetPosY() : 0;

	PX += PW / 2; // プレイヤーの中心座標を取得
	PY += PH / 2; // プレイヤーの中心座標を取得


	if (player == nullptr) { player = gInst->GetLpPlayer(); }

	// 移動処理のロジック
	if (PX - pos.x > -10 && PX - pos.x < 10)
	{
		// プレイヤー座標との差が-10から10の範囲内の場合、Y座標は変化させない
	}
	else if (PX < pos.x) {
		pos.x -= speed;
		dir = 0; // 左向き
	}
	else {
		pos.x += speed;
		dir = 2; // 右向き
	}

	if (PY - pos.y > -10 && PY - pos.y < 10)
	{
		// プレイヤー座標との差が-10から10の範囲内の場合、Y座標は変化させない
	}
	else if (PY < pos.y) {
		pos.y -= speed; // 上方向への加速
	}
	else if (PY > pos.y) {
		pos.y += speed; // 下方向への加速
	}

	if (BakHP != EnemyBase::hp ||(PX == pos.x && PY == pos.y))
	{

		worp = rand() % 2; // 0か1をランダムに生成
		if (worp == 0)
		{
			pos.x = PX + 300 + (50 * speed);
			pos.y = PY + 300 + (50 * speed);
		}
		else
		{
			pos.x = PX - 300 - (50 * speed);
			pos.y = PY - 300 - (50 * speed);
		}
		BakHP = EnemyBase::hp;
	}

}




