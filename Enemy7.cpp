#include "Enemy7.h"
#include "GameScene.h"
#include "Stage.h"
#include <DxLib.h>

void Enemy7::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(3400.0f, 1225.0f));
	dir = 0;
}

void Enemy7::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage3_A.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 2.0f;
	// 敵のヒットポイント最大値
	hpMax = 3;
	// ボスではない
	eob = 0;
}

bool Enemy7::CheckGrounded(float checkX, float checkY)
{

	if (this->gInst == nullptr) return false;
	Stage* stage = this->gInst->GetLpStage();
	if (stage == nullptr) return false;

	// Enemy7の中心位置から左右の足元2点（左下・右下）を割り出す
	float halfW = size.x / 2.0f;
	float halfH = size.y / 2.0f;

	// 少し内側（遊びを持たせる）をチェック
	float footLeftX = checkX - halfW + 4.0f;
	float footRightX = checkX + halfW - 4.0f;
	float footY = checkY + halfH; // Enemy8の最下部

	// 左下、または右下が壁チップに触れていれば地面のココアール（接触）と判定
	if (stage->CheckCollision(footLeftX, footY) || stage->CheckCollision(footRightX, footY))
	{
		return true;
	}
	return false;
}

void Enemy7::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}
	// --- 足元のコリジョン判定 ---
	if (CheckGrounded(pos.x, pos.y))
	{
		// 地面にめり込まないように位置を調整（タイルサイズ 32 ピクセル単位にスナップ）
		float halfH = size.y / 2.0f;
		float footY = pos.y + halfH;
		int tileY = (int)floorf(footY / 32.0f);

	}
	else
	{
		// 足元に床がない場合は空中状態にする
		isFalling = true;
	}

	if (isFalling == true)
	{
		fallVy += 0.5f; // 重力加速度を調整
		pos.y += fallVy; // 落下速度を適用
		if (CheckGrounded(pos.x, pos.y))
		{
			// 着地した場合
			isFalling = false;
			fallVy = 0.0f; // 落下速度をリセット
		}
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得


	pos.x -= speed; // 敵の移動速度を設定
	
}