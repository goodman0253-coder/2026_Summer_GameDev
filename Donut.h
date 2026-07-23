#pragma once
#include "BreadBase.h"

class Donut : public BreadBase
{
private:
    float currentSize;   // 現在のサイズ（floatで滑らかに大きくする）
    float maxSize;       // 最大サイズ
    float growthRate;    // 1フレームごとに大きくなる量
    float angle;         // 回転角度（ラジアン）
	float rotateSpeed;  // 回転速度（ラジアン/フレーム）
    int baseDamage;      // 基本ダメージ

public:
    Donut(float startX, float startY, AsoUtility::DIR direction);

    void Update() override;

    void Draw(float cameraX, float cameraY) override;

    // 現在のサイズに応じたダメージを返す関数
    int GetCurrentDamage() const;
};