#include <DxLib.h>
#include "BreadManager.h"
#include "Bread.h"
#include "Player.h"

BreadManager::BreadManager(void)
{
	image = -1;

	plInst = nullptr;
	bread = nullptr;
}

void BreadManager::Update(void)
{
	bread->Update();
	plInst->Update();

	if (bread->GetShotFlg() == false)
	{
		prevShotKey = nowShotkey;
		nowShotkey = CheckHitKey(KEY_INPUT_SPACE);

		if (prevShotKey == 0 && nowShotkey == 1)
		{
		}
	}
}
