#include "Boss1.h"
#include "GameScene.h"
#include "Player.h"
#include "Stage.h"
#include <DxLib.h>
#include <math.h>


void Boss1::GameInit(void)
{
}

void Boss1::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "stage1_boss.png";
	// 敵の画像サイズ
 	size = { 128, 128 };
	// 敵の移動速度
	speed = 0.0f;
	// 敵のヒットポイント最大値
	hpMax = 15;
	// ボスとして設定
	eob = 10;
	// 固有音声を設定
	BossSEName = "Sound/Boss1.wav";
}

bool Boss1::CheckGrounded(float checkX, float checkY)
{
	// EnemyBaseに保存されているGameSceneのポインタ（gameScene等）からStageを取得
	// ※もしEnemyBase内の変数名が異なる場合は、環境に合わせて調整してください。
	if (this->gInst == nullptr) return false;
	Stage* stage = this->gInst->GetLpStage();
	if (stage == nullptr) return false;

	// ボスの中心位置から左右の足元2点（左下・右下）を割り出す
	float halfW = size.x / 2.0f;
	float halfH = size.y / 2.0f;

	// 少し内側（遊びを持たせる）をチェック
	float footLeftX = checkX - halfW + 4.0f;
	float footRightX = checkX + halfW - 4.0f;
	float footY = checkY + halfH; // ボスの最下部

	// 左下、または右下が壁チップに触れていれば地面のココアール（接触）と判定
	if (stage->CheckCollision(footLeftX, footY) || stage->CheckCollision(footRightX, footY))
	{
		return true;
	}
	return false;
}

void Boss1::Update(void)
{
	EnemyBase::Update();

	if (!GetAlive())
	{
		return;
	}

	Vector2F nowPos = this->pos; // 敵の現在位置を取得

	// プレイヤーの方向を向くように設定
	int PX = (player != nullptr) ? player->GetPosX() : 0;
	if (PX < pos.x) {
		dir = 0; // 左向き
	}
	else {
		dir = 2; // 右向き
	}



	if (isJumping)
	{
		// 空中での重力処理
		if (jumpVy < 0.0f)
		{
			jumpVy += GRAVITY;
		}
		else
		{
			jumpVy += GRAVITY * 2.5f; // 落下時は少し重力を強く
		}
	}
	else
	{
		// 地上にいる時でも、床がなくなったら落下させるための処理
		jumpVy += GRAVITY;
	}

	// 移動量を座標に仮適用
	pos.x += jumpVx;
	pos.y += jumpVy;

	// --- 足元のコリジョン判定 ---
	if (CheckGrounded(pos.x, pos.y))
	{
		// 地面にめり込まないように位置を調整（タイルサイズ 32 ピクセル単位にスナップ）
		float halfH = size.y / 2.0f;
		float footY = pos.y + halfH;
		int tileY = (int)floorf(footY / 32.0f);

		// 地面の表面のY座標にボスを合わせる
		pos.y = (tileY * 32.0f) - halfH;

		// 着地完了処理
		if (SECN == 1)
		{
			SECN = 0;
			PlaySoundMem(BossActionSE, DX_PLAYTYPE_BACK);
		}
		jumpVy = 0.0f;
		jumpVx = 0.0f;
		isJumping = false;
	}
	else
	{
		// 足元に床がない場合は空中状態にする
		isJumping = true;
	}

	if (!isJumping)
	{
		JumpTimer++;

		if (JumpTimer >= 180)
		{
			isJumping = true;
			SECN = 1;
			JumpTimer = 0;

			jumpVy = -15.0f;

			float distanceX = PX - pos.x;
			jumpVx = (distanceX / 60.0f)*1.7f;
		}
	}
#if 0
	else
	{
		if (jumpVy < 0.0f)
		{
			
			jumpVy += GRAVITY;

			pos.x += jumpVx;
			pos.y += jumpVy;

			if (jumpVy >= 0.0f)
			{
				jumpVy = 0.0f;
				jumpVx = 0.0f; 
			}
		}

		else
		{
			
			jumpVy += GRAVITY * 2.5f;
			pos.y += jumpVy;

			if (pos.y >= 1225.0f)
			{
				pos.y = 1225.0f;   
				jumpVy = 0.0f;
				jumpVx = 0.0f;
				isJumping = false;
			}
		}

	}
#endif
}




    

