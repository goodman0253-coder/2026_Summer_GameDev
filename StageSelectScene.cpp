#include "StageSelectScene.h"
#include <DxLib.h>
#include <string>
#include "Application.h"
#include "SceneManager.h"
#include "InputManager.h"

void StageSelectScene::Initialize()
{
    stageSelectImage = LoadGraph("image/StageSelect.png");
    fontStageSelect = CreateFontToHandle("MS ゴシック", 48, 3, DX_FONTTYPE_ANTIALIASING);
    fontMenu = CreateFontToHandle("MS ゴシック", 80, 2, DX_FONTTYPE_ANTIALIASING);
}

void StageSelectScene::Update()
{
    if (sceneManager == nullptr) return;

    // 矢印キー「右」またはパッドの「右」が押されたらカーソルを右に進める
    if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_RIGHT) ||
        InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
    {
        currentCursor++;
        if (currentCursor > MAX_STAGES)
        {
            currentCursor = 1; // 一番右に達したら最初に戻る
        }
    }

    // 矢印キー「左」またはパッドの「左」が押されたらカーソルを左に戻す
    if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_LEFT) ||
        InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
    {
        currentCursor--;
        if (currentCursor < 1)
        {
            currentCursor = MAX_STAGES; // 一番左に達したら最大に戻る
        }
    }

    // スペースキー（またはパッドのAボタン）で選択中のステージを決定
    if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) ||
        InputManager::GetInstance().IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
    {
        // 決定されたステージ番号をSceneManagerに記憶させてゲームシーンを開始
        sceneManager->SetSelectStageNum(currentCursor);
        sceneManager->ChangeScene(SCENE_GAME);
    }
}

void StageSelectScene::Draw(void)
{
    // 背景の描画
    if (stageSelectImage != -1)
    {
        DrawExtendGraph(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, stageSelectImage, true);
    }
    else
    {
        DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(15, 25, 45), TRUE);
    }

    // タイトルの表示
    unsigned int white = GetColor(255, 255, 255);
    unsigned int yellow = GetColor(255, 255, 0); // 選択中メニューの強調色
    unsigned int gray = GetColor(120, 120, 120);  // 非選択メニューの色

    // 選択中のステージに応じてテキストの色を変化させ、前に「▶」を付ける演出
    unsigned int stage1Color = (currentCursor == 1) ? yellow : gray;
    std::string stage1Text = (currentCursor == 1) ? "! STAGE 1" : "  STAGE 1";
    DrawStringToHandle(200, 400, stage1Text.c_str(), stage1Color, fontMenu);

    unsigned int stage2Color = (currentCursor == 2) ? yellow : gray;
    std::string stage2Text = (currentCursor == 2) ? "! STAGE 2" : "  STAGE 2";
    DrawStringToHandle(750, 400, stage2Text.c_str(), stage2Color, fontMenu);

    unsigned int stage3Color = (currentCursor == 3) ? yellow : gray;
    std::string stage3Text = (currentCursor == 3) ? "! STAGE 3" : "  STAGE 3";
    DrawStringToHandle(1300, 400, stage3Text.c_str(), stage3Color, fontMenu);

}

bool StageSelectScene::Release(void)
{

    if (stageSelectImage != -1)
    {
        DeleteGraph(stageSelectImage);
        stageSelectImage = -1;
    }
    if (fontStageSelect != -1)
    {
        DeleteFontToHandle(fontStageSelect);
        fontStageSelect = -1;
    }
    if (fontMenu != -1)
    {
        DeleteFontToHandle(fontMenu);
        fontMenu = -1;
    }

    return false;
}