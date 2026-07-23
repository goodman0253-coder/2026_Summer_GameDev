#include "Donut.h"
#include <DxLib.h>

Donut::Donut(float startX, float startY, AsoUtility::DIR direction)
    : BreadBase(startX, startY, direction)
{
    // 画像ロード（※ donut.png を準備してください）
    imageHandle = LoadGraph("image/donut.png");

    // 初期サイズと成長パラメータ
    currentSize = 24.0f;
    maxSize = 160.0f;      // 最大80pxまで巨大化
    growthRate = 1.5f;    // 毎フレーム 1.5px ずつ大きくなる

    width = (int)currentSize;
    height = (int)currentSize;

    angle = 0.0f;         // 初期角度
    rotateSpeed = 0.1f;   // 回転速度（大きくすると高速回転）

    baseDamage = 1;       // 初期ダメージ
    baseSpeed = 6.0f;     // 移動速度

    lifeTimer = 120;      // 寿命

    // 向きに応じた速度設定
    if (dir == AsoUtility::DIR::RIGHT)      speedX = baseSpeed;
    else if (dir == AsoUtility::DIR::LEFT)  speedX = -baseSpeed;
    else                                    speedX = baseSpeed;
}

void Donut::Update()
{
    // 基本の移動処理や寿命のカウントダウン
    BreadBase::Update();

    if (!isAlive) return;

    angle += rotateSpeed;

    // 徐々にサイズを大きくする
    if (currentSize < maxSize)
    {
        currentSize += growthRate;
        if (currentSize > maxSize) currentSize = maxSize;

        // 幅・高さを更新（これで当たり判定と描画サイズが同時に大きくなる）
        width = (int)currentSize;
        height = (int)currentSize;
        x -= growthRate / 2.0f;
        y -= growthRate / 2.0f;
    }
}

void Donut::Draw(float cameraX, float cameraY)
{
    if (!isAlive) return;

    if (imageHandle != -1)
    {
        // 画面上の中心座標を計算（DrawRotaGraphは中心指定のため）
        float drawCenterX = (x + width / 2.0f) - cameraX;
        float drawCenterY = (y + height / 2.0f) - cameraY;

        // 元画像のサイズ（仮に32px）に対する倍率計算
        double ExtRate = (double)currentSize / 32.0;

        // 回転＆拡大して描画
        DrawRotaGraph((int)drawCenterX, (int)drawCenterY, ExtRate, (double)angle, imageHandle, TRUE);
    }
    else
    {
        // 画像がない場合は親クラスの仮描画を呼ぶ
        BreadBase::Draw(cameraX, cameraY);
    }
}

// サイズに応じてダメージがアップする
int Donut::GetCurrentDamage() const
{
    // 例: サイズが大きくなるにつれて最大 4 ダメージまで増加
    int bonusDamage = (int)((currentSize - 16.0f) / 40.0f);
    return baseDamage + bonusDamage;
}