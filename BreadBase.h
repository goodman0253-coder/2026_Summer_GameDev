#pragma once
#include "AsoUtility.h"


class BreadBase
{
protected:
    
    float speedX;     // 移動速度
    bool isAlive;     // 生存フラグ（falseになったら消滅）
    int imageHandle;  // 画像用ハンドル
    

    AsoUtility::DIR dir;

    int lifeTimer;

public:
    float x, y;       // 座標
    int width, height;// パンのサイズ
    BreadBase(float startX, float startY, AsoUtility::DIR direction);
    virtual ~BreadBase();

    virtual void Update(); // 毎フレームの移動処理
    virtual void Draw(float cameraX, float cameraY);   // 描画処理

    bool IsAlive() const { return isAlive; }
    void Kill() { isAlive = false; }

    virtual int GetCoolTime() const { return 180; }
};

