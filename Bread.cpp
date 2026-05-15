#include <DxLib.h>
#include "Bread.h"

Bread::Bread(void)
{
	image = -1;
}

Bread::~Bread(void)
{
}

bool Bread::SystemInit(void)
{
	// クロワッサンの読み込み
	image = LoadGraph("image/croissant.png");
	if (image == -1)	return false;

	//

	return true;
}

void Bread::GameInit(void)
{
	// パンの発射
	pos.x = 0;
	pos.y = 0;

	shotFlg = false;

}

void Bread::Update(void)
{
	// 弾の処理
	if (shotFlg)
	{
		pos.x = pos.x - BREAD_MOVE_SPEED;

		if (pos.x < 0)
		{
			shotFlg = false;
		}
	}

}

void Bread::Draw(void)
{
	if (shotFlg == true)
	{
		DrawGraph(pos.x, pos.y, image, true);
	}
}

bool Bread::Release(void)
{
	if (DeleteGraph(image) == -1)	return false;

	return true;
}

