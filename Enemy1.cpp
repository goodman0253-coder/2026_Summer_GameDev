#include "Enemy1.h"
#include <DxLib.h>
void Enemy1::SetEnemyParam(void)
{
	// 敵の画像ファイル名
	imgFName = "Girl_stage1_A.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 2.0f;
	// 敵のヒットポイント最大値
	hpMax = 1;
}