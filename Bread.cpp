#include "DxLib.h"
#include "BreadBase.h"
#include "Bread.h"


Bread::Bread(float startX, float startY, AsoUtility::DIR direction)
    : BreadBase(startX, startY, direction)
{
    // 基本のパン固有の画像を読み込む（事前に一括読み込みして使い回すのが理想ですが、簡易的に）
    imageHandle = LoadGraph("image/bread.png");
    width = 16;
    height = 16;
}

Bread::~Bread()
{
    if (imageHandle != -1)
    {
        DeleteGraph(imageHandle); // 毎回読み込む簡易処理の場合はここで消す
    }
}

void Bread::Update()
{
    // 親クラスの基本移動（直進）を呼び出す
    BreadBase::Update();

    // もし少しずつ下に落ちる（放物線)などの固有処理を入れたい場合はここに書けます
}
