#include "Enemy3.h"
#include "GameScene.h"
#include "EnemyBulletBase.h"
#include "Stage1_EnemyC_Bullet.h"
#include "Player.h"
#include <cmath> 

void Enemy3::GameInit(void)
{
    EnemyBase::GameInit(Vector2F(1800.0f, 1225.0f));
}

void Enemy3::SetEnemyParam(void)
{
	imgFName = "enemy_stage1_C.png";
	size = { 64, 64 };
	speed = 0.0f;
	hpMax = 3;
}

void Enemy3::Update(void)
{
    EnemyBase::Update();
    if (!GetAlive()) return;

    Player* player = gInst->GetLpPlayer();
    if (player == nullptr) return;

    // プレイヤーと敵の座標
    float px = player->GetPosX();
    float py = player->GetPosY();
    float ex = this->pos.x;
    float ey = this->pos.y;

    // 警戒範囲（四角）
    float alertRange = 300.0f;
    bool inAlert = (std::abs(px - ex) < alertRange && std::abs(py - ey) < alertRange);

    // 状態遷移と攻撃タイマー
    switch (currentState)
    {
    case ActionState::IDLE:
        animCounter = 0;
        animNo = 0;
        // 警戒範囲に入ったら警戒モードへ
        if (inAlert) {
            currentState = ActionState::ALERT;
            shotTimer = 0; // 警戒開始時にタイマーをリセット
        }
        break;

    case ActionState::ALERT:
        animCounter = 0;
        animNo = 0;
        shotTimer++; // 警戒に入ってからの時間をカウント

        // 警戒開始から一定フレーム（例：60フレーム）経ったら強制的に攻撃
        if (shotTimer >= 60) {
            currentState = ActionState::ATTACKING;
            animCounter = 0; // 攻撃アニメーション開始
        }
        break;

    case ActionState::ATTACKING:
        // 攻撃アニメーション再生中
        if (animCounter == EnemyBase::ANIM_INTERVAL)
        {
            int bulletCount = 8;
            for (int i = 0; i < bulletCount; i++)
            {
                BulletST1C* newBullet = new BulletST1C();

                // 弾に「自分は何番目か」と「合計何発か」を教えて計算させる
                newBullet->SetSpreadVelocity(i, bulletCount);

                // 弾をリストに追加（位置はエネミーの現在位置から）
                gInst->AddEnemyBullet(newBullet, this->pos, newBullet->GetVelocity());
            }
        }

        // アニメーション終了（60フレーム）で待機状態へ
        if (animCounter == 0)
        {
            currentState = ActionState::IDLE;
        }
        break;
    }
}