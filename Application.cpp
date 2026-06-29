#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"

Application::Application()
{

}

Application::~Application()
{

}

bool Application::SystemInit(void)
{
	// システム処理
	SetWindowText("でりばりぃべぇかりぃ");
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG,32);
	SetWaitVSyncFlag(TRUE);
	if (DxLib_Init() == -1) return false;

	SetDrawScreen(DX_SCREEN_BACK);

	ChangeWindowMode(false);
	return true;
}

bool Application::GameInit(void)
{
	InputManager::CreateInstance();
	sceneManager = new SceneManager();
	sceneManager->ChangeScene(SCENE_TITLE);

	return true;
}

void Application::Run()
{
	LONGLONG startTime = GetNowHiPerformanceCount();
	const LONGLONG targetFrameTime = 1000000 / 60; // 1フレームあたりの目標時間（マイクロ秒：約16666）

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面クリアと更新・描画の実行
		ClearDrawScreen();

		Update();
		Draw();

		// 裏画面の内容を表画面に反映
		ScreenFlip();

		// 💡 144Hzや240Hzなどのゲーミングモニター環境でも強制的に60FPSに抑えるウエイト処理
		LONGLONG endTime = GetNowHiPerformanceCount();
		LONGLONG processTime = endTime - startTime;

		// 目標時間より早く1フレームの処理が終わった場合、足りない時間分だけ待つ
		if (processTime < targetFrameTime)
		{
			while (GetNowHiPerformanceCount() - startTime < targetFrameTime)
			{
				// CPUの占有率を下げてPCへの負荷を減らすためのスリープ
				Sleep(0);
			}
		}

		// 次のフレームの開始時間を記録
		startTime = GetNowHiPerformanceCount();
	}
}

bool Application::Release(void)
{
	if (DxLib_End() == -1)return false;
	return true;
}

void Application::Update(void)
{
	InputManager::GetInstance().Update();

	if (sceneManager != nullptr)
	{
		clsDx();
		printfDx("%d", InputManager::GetInstance().IsPadAKeyLX(InputManager::JOYPAD_NO::PAD1));
		sceneManager->Update();
	}
#if 0;
	if (currentScene != nullptr)
	{
		currentScene->Update();
	}

	
	if (currentScene == titleScene)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			currentScene = gameScene; 
		}
	}
#endif;

}

void Application::Draw(void)
{
	if (sceneManager != nullptr)
	{
		sceneManager->Draw();
	}
}
