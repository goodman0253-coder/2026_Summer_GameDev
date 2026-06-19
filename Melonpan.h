#pragma once
#include "BreadBase.h"

class GameScene; // 前方宣言

class Melonpan : public BreadBase
{
private:
    GameScene* gameSceneRef; // 分裂したパンを登録するためにGameSceneのポインタを持つ

public:
    Melonpan(float startX, float startY, AsoUtility::DIR direction, GameScene* scene);

    void Update() override;

    // ⭕ 敵や壁に衝突した時に外部（GameSceneなど）から呼ばれる破裂関数
    void Explode();
};