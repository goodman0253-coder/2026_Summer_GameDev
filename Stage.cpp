#include "Stage.h"
#include "DxLib.h"
#include <fstream>
#include <sstream>

Stage::Stage()
{
    // 配列の初期化
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            stageMap[y][x] = -1; 
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
    LoadMapCSV("image/MAP0V1.csv");
}

void Stage::LoadMapCSV(const std::string& filename)
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
            stageMap[y][x] = std::stoi(value);
            x++;
        }
        y++;
    }
}

void Stage::Draw(float cameraX, float cameraY)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int chipIndex = stageMap[y][x];

            // 有効な画像ハンドルがある場合のみ描画
            if (chipIndex >= 0 && chipIndex < TILE_MAX && tileImages[chipIndex] != -1)
            {
                // カメラ座標を引き算してスクロール位置を計算
                int drawX = x * TILE_SIZE - (int)cameraX;
                int drawY = y * TILE_SIZE - (int)cameraY;

                // 画面外（上下左右1マス分余裕を持たせる）のものは描画スキップ（軽量化）
                if (drawX >= -TILE_SIZE && drawX <= 640 &&
                    drawY >= -TILE_SIZE && drawY <= 480)
                {
                    DrawGraph(drawX, drawY, tileImages[chipIndex], TRUE);
                }
            }
        }
    }
}