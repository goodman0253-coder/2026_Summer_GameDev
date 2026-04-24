#include <DxLib.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


	DxLib_Init();
	
	Application application;

	// ‰Šú‰»ˆ—
	application.SystemInit();

	// ƒQ[ƒ€‹N“®
	application.Run();

	// ‰ğ•úˆ—
	application.Release();

	
	DxLib_End();
	return 0;
}