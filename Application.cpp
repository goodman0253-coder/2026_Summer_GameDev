#include <DxLib.h>
#include "Application.h"


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
	ChangeWindowMode(false);
	return true;
}

void Application::Run()
{
}

bool Application::Release(void)
{
	if (DxLib_End() == -1)return false;
	return true;
}

void Application::Update(void)
{
}

void Application::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK); // 描画する画面を裏の画面に設定する
	ClearDrawScreen(); // 描画する画面の内容を消去(クリア)する
	ScreenFlip(); // 裏画面と表画面を入れ替える
}
