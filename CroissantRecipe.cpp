#include "CroissantRecipe.h"
#include <DxLib.h>

CroissantRecipe::CroissantRecipe(float startX, float startY)
    : RecipeBase(startX, startY, Player::BREAD_TYPE::CROISSANT) // 💡 解放するパンの種類を指定
{
    // クロワッサン解放アイテム専用の画像を読み込む
    imageHandle = LoadGraph("image/croissant.png");
}

