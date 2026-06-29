#pragma once
#include "RecipeBase.h"

class MelonRecipe : public RecipeBase
{
public:
    MelonRecipe(float startX, float startY)
        : RecipeBase(startX, startY, Player::BREAD_TYPE::MELONPAN)
    {
        // メロンパン解放アイテム専用の画像を読み込む
        imageHandle = LoadGraph("image/bread.png");
    }
};

