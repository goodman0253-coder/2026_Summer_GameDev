#include <DxLib.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application application;

<<<<<<< HEAD
    //‰Šú‰»
    if (application.SystemInit() == false)
    {
        return -1;
    }

    if (application.GameInit() == false)
    {
        return -1;
    }
=======
	DxLib_Init();
	
	Application application;
>>>>>>> salmon

    // ƒQ[ƒ€‹N“®
    application.Run();

    // ‰ğ•úˆ—
    application.Release();

	
	DxLib_End();
	return 0;
}