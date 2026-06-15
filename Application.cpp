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
	if (DxLib_Init() == -1) return false;


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

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Update();
		Draw();
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
	SetDrawScreen(DX_SCREEN_BACK); // 描画する画面を裏の画面に設定する
	ClearDrawScreen(); // 描画する画面の内容を消去(クリア)する

	if (sceneManager != nullptr)
	{
		sceneManager->Draw();
	}

	ScreenFlip(); // 裏画面と表画面を入れ替える
}
