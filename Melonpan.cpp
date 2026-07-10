#include "Melonpan.h"
#include "MiniMelonpan.h"
#include "GameScene.h"
#include <DxLib.h>
#include <cmath> // cosf, sinf を使うため

Melonpan::Melonpan(float startX, float startY, AsoUtility::DIR direction, GameScene* scene)
    : BreadBase(startX, startY, direction) // ベースクラスのコンストラクタ呼び出し
{
    gameSceneRef = scene;

    // メロンパンなので少し大きめに設定
    width = 32;
    height = 32;

    // 💡 通常のメロンパン画像を読み込む
    imageHandle = LoadGraph("image/melonpan.png");

    lifeTimer = 90;
}

void Melonpan::Update()
{
    // 基本の移動処理（直進）や寿命管理はBreadBaseにすべて任せる
    BreadBase::Update();

    // もし寿命で死んだ場合も、不発で終わるのではなくその場で自動破裂させる
    if (!isAlive && lifeTimer <= 0)
    {
        // 一度だけ破裂するようにフラグが死ぬ前に実行
        isAlive = true;
        Explode();
    }
}

void Melonpan::Explode()
{
    if (!isAlive) return;

    isAlive = false; // 自分自身は消滅

    const int SPLIT_COUNT = 8;     // 8方向に分裂
    const float MINI_SPEED = 5.0f; // 分裂したパンの速度

    // メロンパンの中心座標を計算
    float centerX = x + (width / 2.0f);
    float centerY = y + (height / 2.0f);

    for (int i = 0; i < SPLIT_COUNT; ++i)
    {
        // 三角関数（360度を等分したラジアン）の計算
        float angle = ((float)i / (float)SPLIT_COUNT) * (3.141592f * 2.0f);

        float vx = cosf(angle) * MINI_SPEED;
        float vy = sinf(angle) * MINI_SPEED;

        // 小さなメロンパンを生成（親の中心から発射）
        MiniMelonpan* mini = new MiniMelonpan(centerX - 8, centerY - 8, vx, vy);

        // GameSceneに生成したパンを登録して管理してもらう
        if (gameSceneRef != nullptr)
        {
            gameSceneRef->AddBread(mini);
        }
    }
}