#pragma once
#include "Player.h"
#include <DxLib.h>

class RecipeBase
{
protected:
    float x, y;                 // 座標
    int width, height;          // 当たり判定のサイズ
    int imageHandle;            // 画像ハンドル
    bool isAlive;               // 生存フラグ（拾われたら false になる）
    Player::BREAD_TYPE unlockType; // 拾ったときに解放するパンの種類
    int bordImg = -1;

public:
    RecipeBase(float startX, float startY, Player::BREAD_TYPE type)
    {
        x = startX;
        y = startY;
        width = 32;          // デフォルトサイズ（適宜変更してください）
        height = 32;
        imageHandle = -1;
        isAlive = true;
        unlockType = type;

		bordImg = LoadGraph("image/Recipe_bord.png");
    }

    virtual ~RecipeBase() {}

    virtual void Update()
    {
        // 必要であれば、アイテムをフワフワ上下に浮かせたりするアニメーションをここに書けます
    }

    virtual void Draw(float cameraX, float cameraY)
    {
        if (!isAlive || imageHandle == -1) return;

        // 指定サイズに合わせて引き伸ばし描画（Box全体に合わせる）
        int drawX1 = (int)(x - cameraX);
        int drawY1 = (int)(y - cameraY);
        int drawX2 = drawX1 + width;
        int drawY2 = drawY1 + height;

        DrawExtendGraph(drawX1 , drawY1 - 4, drawX2 , drawY2 + 4, bordImg, TRUE);
        DrawExtendGraph(drawX1, drawY1, drawX2, drawY2, imageHandle, TRUE);

    }

    // ゲッター関数群
    float GetX() const { return x; }
    float GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsAlive() const { return isAlive; }
    Player::BREAD_TYPE GetUnlockType() const { return unlockType; }

    // 拾われた時の処理
    void Collect() { isAlive = false; }
};