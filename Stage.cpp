#include "Stage.h"
#include "DxLib.h"
#include <fstream>
#include <sstream>

Stage::Stage()
{
    // 配列の初期化
    for (int l = 0; l < LAYER_MAX; l++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                stageMap[l][y][x] = -1;
            }
        }
    }
    for (int i = 0; i < TILE_MAX; i++) {
        tileImages[i] = -1;
    }
}

Stage::~Stage()
{
    for (int i = 0; i < TILE_MAX; i++) {
        if (tileImages[i] != -1) {
            DeleteGraph(tileImages[i]);
        }
    }
}

void Stage::Initialize()
{

    int xNum = 8;
    int yNum = 58;
    LoadDivGraph("image/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages);

    //マップCSVを読み込む
    LoadMapCSV("image/MAP02BACKV2.csv", LAYER_BACKGROUND); // 背景用CSV
    LoadMapCSV("image/MAP02MIDV1.csv", LAYER_MIDDLEGROUND); // 中景用CSV（今のメインマップ）
    LoadMapCSV("image/MAP02OBJV1.csv", LAYER_OBJECT); // 障害物用CSV
    LoadMapCSV("image/MAP02FOREV1.csv", LAYER_FOREGROUND); // 前景用CSV

}

void Stage::LoadMapCSV(const std::string& filename, eOfficeMapLayer OLayer)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        printfDx("CSVファイル [%s] の読み込みに失敗/\n", filename.c_str());
        return;
    }

    std::string line;
    int y = 0;

    while (std::getline(file, line) && y < MAP_HEIGHT)
    {
        std::stringstream ss(line);
        std::string value;
        int x = 0;

        while (std::getline(ss, value, ',') && x < MAP_WIDTH)
        {
            stageMap[OLayer][y][x] = std::stoi(value);
            x++;
        }
        y++;
    }
}

// ⭕ 指定されたレイヤーだけを描画する関数にする
void Stage::Draw(float cameraX, float cameraY, eOfficeMapLayer OLayer)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            // 指定されたレイヤーのチップ番号を取得
            int chipIndex = stageMap[OLayer][y][x];

            if (chipIndex >= 0 && chipIndex < TILE_MAX && tileImages[chipIndex] != -1)
            {
                int drawX = x * TILE_SIZE - (int)cameraX;
                int drawY = y * TILE_SIZE - (int)cameraY;
                DrawGraph(drawX, drawY, tileImages[chipIndex], TRUE);
                
            }
        }
    }
}