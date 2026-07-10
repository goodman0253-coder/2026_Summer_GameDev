#include "Stage.h"
#include "DxLib.h"
#include <fstream>
#include <sstream>

Stage::Stage()
{
    // 配列の初期化
    for (int l = 0; l < LAYER_MAX; l++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                stageMap[l][y][x] = -1;
            }
        }
    }
    for (int i = 0; i < TILE_MAX; i++) {
        tileImages[i] = -1;
    }

    // collisionMap の初期化
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            collisionMap[y][x] = -1; // 初期状態はすべて通り抜け可能
        }
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

void Stage::Initialize(int stageNum)
{
    for (int i = 0; i < TILE_MAX; i++) {
        if (tileImages[i] != -1) {
            DeleteGraph(tileImages[i]);
            tileImages[i] = -1;
        }
    }

    if (stageNum == 1)
    {
        int xNum = 8;
        int yNum = 58;
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages);
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages2);
       
        LoadMapCSV("Data/MAP01BACKV1.csv", LAYER_BACKGROUND); // 背景用CSV
        LoadMapCSV("Data/MAP01MIDV1.csv", LAYER_MIDDLEGROUND); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP01OBJV1.csv", LAYER_OBJECT); // 障害物用CSV
        LoadMapCSV("Data/MAP01FOREV1.csv", LAYER_FOREGROUND); // 前景用CSV
        // ステージ1の当たり判定CSVをロード
        LoadCollisionCSV("Data/AGS_Map_School_Collision.csv");
    }
    else if (stageNum == 2) // ステージ２マップCSVを読み込む
    {

        int xNum = 8;
        int yNum = 58;
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages);

        LoadMapCSV("Data/MAP02BACKV5.csv", LAYER_BACKGROUND); // 背景用CSV
        LoadMapCSV("Data/MAP02MIDV5.csv", LAYER_MIDDLEGROUND); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP02OBJV5.csv", LAYER_OBJECT); // 障害物用CSV
        LoadMapCSV("Data/MAP02FOREV5.csv", LAYER_FOREGROUND); // 前景用CSV
    
        LoadCollisionCSV("Data/AGS_Map_Office_Collision.csv");

	}
    else if (stageNum == 3) // ステージ３マップCSVを読み込む
    {
        int xNum = 8;
        int yNum = 58;
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages);
        LoadMapCSV("Data/MAP03BACKV1.csv", LAYER_BACKGROUND); // 背景用CSV
        LoadMapCSV("Data/MAP03MIDV1.csv", LAYER_MIDDLEGROUND); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP03OBJV1.csv", LAYER_OBJECT); // 障害物用CSV
        LoadMapCSV("Data/MAP03FOREV1.csv", LAYER_FOREGROUND); // 前景用CSV
        LoadCollisionCSV("Data/AGS_Map_School_Collision.csv");
    }
}

void Stage::LoadMapCSV(const std::string& filename, eMapLayer OLayer)
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

void Stage::LoadCollisionCSV(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        printfDx("衝突判定CSV [%s] の読み込みに失敗\n", filename.c_str());
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
            collisionMap[y][x] = std::stoi(value);
            x++;
        }
        y++;
    }
}

// 指定されたレイヤーだけを描画する関数にする
void Stage::Draw(float cameraX, float cameraY, eMapLayer OLayer)
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

bool Stage::CheckCollision(float worldX, float worldY)
{
    // ドット単位のワールド座標を、マップ配列のインデックスに変換
    int mapX = (int)floorf(worldX / TILE_SIZE);
    int mapY = (int)floorf(worldY / TILE_SIZE);
    // 配列の限界（MAX_MAP_WIDTH / HEIGHT）および現在の設定サイズを絶対に超えないようにチェック
    if (mapX < 0 || mapX >= MAP_WIDTH ||
        mapY < 0 || mapY >= MAP_HEIGHT)
    {
        return false; // 範囲外は一旦「壁なし」にしてプレイヤーの消失を防ぐ
    }

    // 1であれば壁（接触）、それ以外（-1など）は通行可能
    return (collisionMap[mapY][mapX] == 1);
}