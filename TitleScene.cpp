#include <DxLib.h>
#include <string>
#include "TitleScene.h"
#include "Application.h"

void TitleScene::Initialize()
{
    titleImage = LoadGraph("image/title.png");

}

void TitleScene::Update()
{

    if (CheckHitKey(KEY_INPUT_SPACE))
    {
       
    }
}

void TitleScene::Draw(void)
{


    if (titleImage != -1)
    {
        DrawExtendGraph(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, titleImage, true);
    }
    //else
    //{
    //    DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
    //}
    //DrawBox(0, 0, 640, 480, 0xffffff, TRUE);PRESS SPACE TO START



    static int blinkTimer = 0;
    blinkTimer++;
    if ((blinkTimer / 30) % 2 == 0)
    {
        SetFontSize(100);
        DrawString(450, 600, "PRESS SPACE TO START", GetColor(255, 255, 0));
        
       
    }
}

bool TitleScene::Release(void)
{

    if (titleImage != -1)
    {
        DeleteGraph(titleImage);
    }

    return false;
}
