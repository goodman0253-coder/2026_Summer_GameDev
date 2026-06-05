#include "GameClearScene.h"
#include "SceneManager.h"
#include <DxLib.h>
#include <string>

#include "Application.h"

void GameClearScene::Initialize()
{
    gameClearImage = LoadGraph("image/GameClear.png");

}

void GameClearScene::Update()
{

    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        sceneManager->ChangeScene(SCENE_TITLE);
    }
}

void GameClearScene::Draw(void)
{


    if (gameClearImage != -1)
    {
        DrawExtendGraph(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, gameClearImage, true);
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

bool GameClearScene::Release(void)
{

    if (gameClearImage != -1)
    {
        DeleteGraph(gameClearImage);
    }

    return false;
}

                 
   