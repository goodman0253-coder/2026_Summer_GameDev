#include "Enemy8.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include <DxLib.h>

void Enemy8::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(3800.0f, 1225.0f));
}

void Enemy8::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "enemy_stage3_B.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 0.5f;
	// 敵のヒットポイント最大値
	hpMax = 2;
	// ボスではない
	eob = 0;
}

bool Enemy8::CheckGrounded(float checkX, float checkY)
{

	if (this->gInst == nullptr) return false;
	Stage* stage = this->gInst->GetLpStage();
	if (stage == nullptr) return false;

	// Enemy8の中心位置から左右の足元2点（左下・右下）を割り出す
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

void Enemy8::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得

	// プレイヤーの座標を取得
	int PX = (player != nullptr) ? player->GetPosX() : 0;

	if (player == nullptr) { player = gInst->GetLpPlayer(); }

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

	// 移動処理のロジック修正
	if (PX < pos.x) {
		dir = 0; // 左向き
		nowspeed -= 0.5f; // 加速度を少し抑える
	}
	else {
		dir = 2; // 右向き
		nowspeed += 0.5f;
	}

	// 速度制限と適用
	if (nowspeed < lowspeed) nowspeed = lowspeed;
	if (nowspeed > maxspeed) nowspeed = maxspeed;

	Stage* stage = this->gInst->GetLpStage();
	if (stage != nullptr && isFalling == true)
	{
		float halfW = size.x / 2.0f;
		float nextX = pos.x + nowspeed; // 次のフレームで移動予定のX座標

		// 進行方向側の端のX座標を取得
		float checkX = (nowspeed > 0) ? (nextX + halfW) : (nextX - halfW);

		// キャラクターの上半身と足元より少し上の2点で壁をチェック
		float checkTopY = pos.y - size.y / 4.0f;
		float checkBottomY = pos.y + size.y / 2.0f - 4.0f;

		// 進行方向に壁があるか？
		if (stage->CheckCollision(checkX, checkTopY) || stage->CheckCollision(checkX, checkBottomY))
		{
			// 落下中に壁にぶつかった場合は横移動をストップ
			nowspeed = 0.0f;
		}
		else
		{
			// 落下中で壁がなければX座標を更新
			pos.x = nextX;
		}
	}
	else
	{
		// 地上にいるとき（isFalling == false）は障害物を無視して爆走する
		pos.x += nowspeed;
	}
}
