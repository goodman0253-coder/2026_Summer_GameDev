#include "BreadBase.h"
#include "DxLib.h"
#include "Application.h" // 画面サイズ等の定数があれば

BreadBase::BreadBase(float startX, float startY, AsoUtility::DIR direction)
{
    x = startX;
    y = startY;

    dir = direction;

    isAlive = true;
    imageHandle = -1;
    width = 16;   // デフォルトサイズ
    height = 16;

    lifeTimer = 300;                  

    // 基本スピード
    float baseSpeed = 8.0f;

    if (dir == AsoUtility::DIR::RIGHT)
    {
        speedX = baseSpeed;       // 右に進む（プラス）
    }
    else if (dir == AsoUtility::DIR::LEFT)
    {
        speedX = -baseSpeed;      // 左に進む（マイナス）
    }
    else
    {
        speedX = baseSpeed;            // 上下を向いている時はとりあえず横には動かさない
    }


}

BreadBase::~BreadBase()
{
    // 画像ハンドルは共通で管理することが多いため、ここではDeleteGraphしない（またはGameInit等で一括管理）
}

void BreadBase::Update()
{
    if (!isAlive) return;

    // 横に直進移動
    x += speedX;

    // ? 2. 寿命タイマーを毎フレーム 1 減らす
    if (lifeTimer > 0)
    {
        lifeTimer--;
    }
    if (lifeTimer <= 0)
    {
        isAlive = false;
    }
}

void BreadBase::Draw(float cameraX, float cameraY)
{
    if (!isAlive) return;

    int drawX = (int)x - (int)cameraX;
    int drawY = (int)y - (int)cameraY;

    if (imageHandle != -1)
    {
        DrawGraph(drawX, drawY, imageHandle, TRUE);
    }
    else
    {
        // 画像がない場合の仮描画（黄色い丸）
        DrawCircle(drawX + width / 2, drawY + height / 2, width / 2, GetColor(255, 255, 0), TRUE);
    }
}