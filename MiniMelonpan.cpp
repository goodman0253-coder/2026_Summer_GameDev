#include "MiniMelonpan.h"
#include "DxLib.h"

MiniMelonpan::MiniMelonpan(float startX, float startY, float vx, float vy)
    : BreadBase(startX, startY, AsoUtility::DIR::MAX) // ベースクラスの初期化（向きはMAX等でダミーに）
{
    // 速度を上書き
    speedX = vx;
    speedY = vy;

    // 小さいのでサイズを小さく設定
    width = 32;
    height = 32;

    // 小さいパンの寿命（1秒＝60フレームで消滅）
    lifeTimer = 60;

    imageHandle = LoadGraph("image/melonpan.png");
}

void MiniMelonpan::Update()
{
    if (!isAlive) return;

    // 独自に拡張したXとYの速度で斜めや上下に移動
    x += speedX;
    y += speedY;

    // 寿命タイマーの更新
    if (lifeTimer > 0) lifeTimer--;
    if (lifeTimer <= 0) isAlive = false;
}

void MiniMelonpan::Draw(float cameraX, float cameraY)
{
    if (!isAlive) return;

    int drawX = (int)x - (int)cameraX;
    int drawY = (int)y - (int)cameraY;

    if (imageHandle != -1)
    {
        // 中心を基準に0.6倍の大きさで描画
        DrawRotaGraph(drawX + width / 2, drawY + height / 2, 1.0f, 0.0f, imageHandle, TRUE);
    }

    // デバッグ用当たり判定の可視化
    //DrawBox(drawX, drawY, drawX + width, drawY + heigh     t, GetColor(255, 0, 0), FALSE);
}
