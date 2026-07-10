#include "Boss3.h"
#include "GameScene.h"
#include "Player.h"
#include<DXLib.h>



void Boss3::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(6200.0f, 1225.0f));
	EoB = 10; // ボスとして設定
	BakHP = hpMax; // 初期HPを保存
}

void Boss3::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "stage3_boss.png";
	// 敵の画像サイズ
	size = { 128, 128 };
	// 敵の移動速度
	speed = 2.0f;
	// 敵のヒットポイント最大値
	hpMax = 10;
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

	// プレイヤーの方向を向くように設定
	int PX = (player != nullptr) ? player->GetPosX() : 0;
	int PY = (player != nullptr) ? player->GetPosY() : 0;
	Vector2F playerDir = Vector2F(PX - pos.x, 0.0f);
	this->setMoveDirection(playerDir);

	if (player == nullptr) { player = gInst->GetLpPlayer(); }

	// 移動処理のロジック修正
	if (PX < pos.x) {
		pos.x -= speed; // 加速度を少し抑える
	}
	else {
		pos.x += speed;
	}

	if (PY < pos.y) {
		pos.y -= speed; // 上方向への加速
	}
	else {
		pos.y += speed; // 下方向への加速
	}

	if (BakHP != EnemyBase::hp ||(PX == pos.x && PY == pos.y))
	{

		worp = rand() % 2; // 0か1をランダムに生成
		if (worp == 0)
		{
			pos.x = PX + 800;
			pos.y = PY + 800;
		}
		else
		{
			pos.x = PX - 800;
			pos.y = PY - 800;
		}
		BakHP = EnemyBase::hp;
	}

}




