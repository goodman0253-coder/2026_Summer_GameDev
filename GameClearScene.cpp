#include "GameClearScene.h"
#include "SceneManager.h"
#include <DxLib.h>
#include <string>
#include "Application.h"
#include "InputManager.h"

void GameClearScene::Initialize()
{
    gameClearImage = LoadGraph("image/GameClear.png");

}

void GameClearScene::Update()
{

    if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
    {
        if (sceneManager != nullptr)
        {
            sceneManager->ChangeScene(SCENE_TITLE);
        }
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

bool GameClearScene::Release(void)
{

    if (gameClearImage != -1)
    {
        DeleteGraph(gameClearImage);
    }

    return false;
}

                 
   