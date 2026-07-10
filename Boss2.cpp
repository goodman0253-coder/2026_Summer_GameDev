#include "Boss2.h"
#include "GameScene.h"
#include "EnemyBulletBase.h"
#include "Stage1_EnemyB_Bullet.h"
#include "Player.h"
#include<DXLib.h>



void Boss2::GameInit(void)
{
	EnemyBase::GameInit(Vector2F(6200.0f, 1225.0f));
	EoB = 10; // ボスとして設定
	BakHP = hpMax; // 初期HPを保存
}

void Boss2::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "stage2_boss.png";
	// 敵の画像サイズ
	size = { 128, 128 };
	// 敵の移動速度
	speed = 0.3f;
	// 敵のヒットポイント最大値
	hpMax = 20;
}

void Boss2::Update(void)
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

	if (PX < pos.x) {
		pos.x -= speed; // 加速度を少し抑える
	}
	else {
		pos.x += speed;
	}
	
	if (BakHP != EnemyBase::hp)
	{
		BakHP = EnemyBase::hp; // HPの更新
		
		// ここで弾を放射する処理を追加する
		if (gInst != nullptr)
		{
			for (int i = 0; i < 8; ++i) // 8方向に弾を放射
			{
				float angle = i * (3.14159f / 4.0f); // 45度ごとに角度を設定
				Vector2F bulletVel;
				bulletVel.x = cos(angle) * 2.0f; // 弾の速度を設定
				bulletVel.y = sin(angle) * 2.0f;
				EnemyBulletBase* newBullet = new BulletST1B(); // 弾のインスタンスを作成(書類を飛ばすためステージ1のエネミーBの弾を流用)
				Vector2F spownPos = this->pos; // 弾のスポーン位置を敵の位置に設定
				gInst->AddEnemyBullet(newBullet, spownPos, bulletVel); // 弾をゲームシーンに追加
			}
		}
	}
}




