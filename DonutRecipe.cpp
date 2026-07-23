#include "DonutRecipe.h"
#include <DxLib.h>

DonutRecipe::DonutRecipe(float startX, float startY)
    : RecipeBase(startX, startY, Player::BREAD_TYPE::DONUT)
{
    // ドーナツ解放アイテム専用の画像を読み込む（※ image/donut.png を用意してください）
    imageHandle = LoadGraph("image/donut.png");
}