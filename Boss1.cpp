#include "Boss1.h"
#include "GameScene.h"
#include "Player.h"
#include<DXLib.h>



void Boss1::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(6200.0f, 1225.0f));
	EoB = 10; // ボスとして設定
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
	Vector2F playerDir = Vector2F(PX - pos.x, 0.0f);
	this->setMoveDirection(playerDir);

	if (!isJumping)
	{
		JumpTimer++;

		if (JumpTimer >= 180)
		{
			isJumping = true;
			JumpTimer = 0;

			jumpVy = -15.0f;

			float distanceX = PX - pos.x;
			jumpVx = (distanceX / 60.0f)*1.7f;
		}
	}
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
}


    

