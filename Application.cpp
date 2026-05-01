#include <DxLib.h>
#include "Application.h"
#include "GameScene.h"

Application::Application()
{

}

Application::~Application()
{
	delete gameScene;
}

bool Application::SystemInit(void)
{
	// システム処理
	SetWindowText("でりばりぃべぇかりぃ");
	SetGraphMode(800,600,32);
	ChangeWindowMode(true);
	return true;
}

bool Application::GameInit(void)
{
	gameScene = new GameScene();
	gameScene->GameInit();
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
	if (gameScene != nullptr)
	{
		gameScene->Update();
	}
}

void Application::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK); // 描画する画面を裏の画面に設定する
	ClearDrawScreen(); // 描画する画面の内容を消去(クリア)する

	if (gameScene != nullptr)
	{
		gameScene->Draw();
	}

	ScreenFlip(); // 裏画面と表画面を入れ替える
}
