#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	DxLib_Init();
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
		DrawString(10, 10, "Hello, DxLib!", GetColor(255, 255, 255));
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}