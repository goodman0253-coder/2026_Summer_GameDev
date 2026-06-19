#include "MiniMelonpan.h"
#include "DxLib.h"

MiniMelonpan::MiniMelonpan(float startX, float startY, float vx, float vy)
    : BreadBase(startX, startY, AsoUtility::DIR::MAX) // ベースクラスの初期化（向きはMAX等でダミーに）
{
    // 速度を上書き
    speedX = vx;
    speedY = vy;

    // 小さいのでサイズを小さく設定
    width = 16;
    height = 16;

    // 小さいパンの寿命（1秒＝60フレームで消滅）
    lifeTimer = 60;

    // 💡 もし小さなメロンパン用の画像があればここで読み込む（無ければ黄色い円になります）
    imageHandle = LoadGraph("image/mini_melon.png");
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
        // 中心を基準に0.2倍の大きさで描画
        DrawRotaGraph(drawX + width / 2, drawY + height / 2, 0.2f, 0.0f, imageHandle, TRUE);
    }
    else
    {
        // 画像がない場合の仮描画（緑色の小さな丸）
        DrawCircle(drawX + width / 2, drawY + height / 2, width / 2, GetColor(0, 255, 0), TRUE);
    }

    // デバッグ用当たり判定の可視化
    DrawBox(drawX, drawY, drawX + width, drawY + height, GetColor(255, 0, 0), FALSE);
}
