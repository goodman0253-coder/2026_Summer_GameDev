#include "GameOverScene.h"
#include "SceneManager.h"
#include <DxLib.h>
#include <string>
#include "Application.h"
#include "InputManager.h"

void GameOverScene::Initialize()
{
    gameOverImage = LoadGraph("image/GameOver.png");

}

void GameOverScene::Update()
{

    if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
    {
        if (sceneManager != nullptr)
        {
            sceneManager->ChangeScene(SCENE_TITLE);
        }
    }
}

void GameOverScene::Draw(void)
{


    if (gameOverImage != -1)
    {
        DrawExtendGraph(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, gameOverImage, true);
    }
    //else
    //{
    //    DrawBox(0, 0, 640, 480, GetColor(0, 0, 0), TRUE);
    //}
    //DrawBox(0, 0, 640, 480, 0xffffff, TRUE);PRESS SPACE TO START


#if 0
    static int blinkTimer = 0;
    blinkTimer++;
    if ((blinkTimer / 30) % 2 == 0)
    {
        SetFontSize(100);
        DrawString(450, 600, "PRESS SPACE TO START", GetColor(255, 255, 0));


    }
#endif
}

bool GameOverScene::Release(void)
{

    if (gameOverImage != -1)
    {
        DeleteGraph(gameOverImage);
    }

    return false;
}
