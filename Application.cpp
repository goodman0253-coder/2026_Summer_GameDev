#include <DxLib.h>
#include "Application.h"
#include "TitleScene.h"
#include "GameScene.h"

Application::Application()
{

}

Application::~Application()
{

	delete titleScene;
	delete gameScene;

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


	titleScene = new TitleScene();
	titleScene->Initialize();

	gameScene = new GameScene();
	gameScene->GameInit();

	currentScene = titleScene;

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
}

void Application::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK); // 描画する画面を裏の画面に設定する
	ClearDrawScreen(); // 描画する画面の内容を消去(クリア)する

	if (currentScene != nullptr)
	{
		currentScene->Draw();
	}

	ScreenFlip(); // 裏画面と表画面を入れ替える
}
