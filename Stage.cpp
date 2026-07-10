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
    for (int l = 0; l < LAYER_MAX; l++)
    {
        for (int i = 0; i < TILE_MAX; i++)
        {
            tileImages[l][i] = -1;
        }
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
#if 0
    for (int l = 0; l < LAYER_MAX; l++)
    {
        for (int i = 0; i < TILE_MAX; i++) {
            if (tileImages[l][i] != -1) {
                DeleteGraph(tileImages[l][i]);
            }
        }
    }
#endif
	InitGraph();
}

void Stage::Initialize(int stageNum)
{
    for (int l = 0; l < LAYER_MAX; l++)
    {
        for (int i = 0; i < TILE_MAX; i++) 
        {
            if (tileImages[l][i] != -1)
            {
                DeleteGraph(tileImages[l][i]);
                tileImages[l][i] = -1;
            }
        }
    }

    if (stageNum == 1)
    {
        int xNum = 8;
        int yNumE = 57;
        int yNumI = 50;
		int yNumG = 50;

        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumE, xNum, yNumE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDSE]);
        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumE, xNum, yNumE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_MIDDLEGROUNDSE]);
        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumE, xNum, yNumE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTSE]);
        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumE, xNum, yNumE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_FOREGROUNDSE]);
        LoadDivGraph("Data/ST-Schl-Gym.png", xNum * yNumG, xNum, yNumG, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDSG]);
        LoadDivGraph("Data/ST-Schl-Gym.png", xNum * yNumG, xNum, yNumG, TILE_SIZE, TILE_SIZE, tileImages[LAYER_MIDDLEGROUNDSG]);
        LoadDivGraph("Data/ST-Schl-Gym.png", xNum * yNumG, xNum, yNumG, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTSG]);
        LoadDivGraph("Data/ST-Schl-Gym.png", xNum * yNumG, xNum, yNumG, TILE_SIZE, TILE_SIZE, tileImages[LAYER_FOREGROUNDSG]);
        LoadDivGraph("Data/ST-Schl-I01.png", xNum * yNumI, xNum, yNumI, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTSI]);

        LoadMapCSV("Data/MAP01BACKV6E.csv", LAYER_BACKGROUNDSE); // 背景用CSV
        LoadMapCSV("Data/MAP01MIDV6E.csv", LAYER_MIDDLEGROUNDSE); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP01OBJV6E.csv", LAYER_OBJECTSE); // 障害物用CSV
        LoadMapCSV("Data/MAP01FOREV6E.csv", LAYER_FOREGROUNDSE); // 前景用CSV
        LoadMapCSV("Data/MAP01BACKV6G.csv", LAYER_BACKGROUNDSG); // 背景用CSV
        LoadMapCSV("Data/MAP01MIDV6G.csv", LAYER_MIDDLEGROUNDSG); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP01OBJV6G.csv", LAYER_OBJECTSG); // 障害物用CSV
        LoadMapCSV("Data/MAP01FOREV6G.csv", LAYER_FOREGROUNDSG); // 前景用CSV
        LoadMapCSV("Data/MAP01OBJV6I.csv", LAYER_OBJECTSI); // 障害物用CSV
        // ステージ1の当たり判定CSVをロード
        LoadCollisionCSV("Data/AGS_Map_School_Collision.csv");
    }
    else if (stageNum == 2) // ステージ２マップCSVを読み込む
    {

        int xNum = 8;
        int yNum = 58;
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDO]);
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages[LAYER_MIDDLEGROUNDO]);
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTO]);
        LoadDivGraph("Data/MAP-Office.png", xNum * yNum, xNum, yNum, TILE_SIZE, TILE_SIZE, tileImages[LAYER_FOREGROUNDO]);

        LoadMapCSV("Data/MAP02BACKV5.csv", LAYER_BACKGROUNDO); // 背景用CSV
        LoadMapCSV("Data/MAP02MIDV5.csv", LAYER_MIDDLEGROUNDO); // 中景用CSV（今のメインマップ）
        LoadMapCSV("Data/MAP02OBJV5.csv", LAYER_OBJECTO); // 障害物用CSV
        LoadMapCSV("Data/MAP02FOREV5.csv", LAYER_FOREGROUNDO); // 前景用CSV
    
        LoadCollisionCSV("Data/AGS_Map_Office_Collision.csv");

	}
    else if (stageNum == 3) // ステージ３マップCSVを読み込む
    {
        int xNum = 8;
        int yNumC = 54;
        int yNumSE = 57;
        int yNumTE = 50;
        int yNumO = 58;

        LoadDivGraph("Data/ST-Convi-E01.png", xNum * yNumC, xNum, yNumC, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDC]);
        LoadDivGraph("Data/ST-Convi-E01.png", xNum * yNumC, xNum, yNumC, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTC]);
        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumSE, xNum, yNumSE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDSE]);
        LoadDivGraph("Data/ST-Schl-E01.png", xNum * yNumSE, xNum, yNumSE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_MIDDLEGROUNDSE]);
        LoadDivGraph("Data/ST-Town-E01.png", xNum * yNumTE, xNum, yNumTE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_BACKGROUNDTE]);
        LoadDivGraph("Data/ST-Town-E01.png", xNum * yNumTE, xNum, yNumTE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_MIDDLEGROUNDTE]);
        LoadDivGraph("Data/ST-Town-E01.png", xNum * yNumTE, xNum, yNumTE, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTTE]);
        LoadDivGraph("Data/MAP-Office.png", xNum * yNumO, xNum, yNumO, TILE_SIZE, TILE_SIZE, tileImages[LAYER_OBJECTO]);
      

        LoadMapCSV("Data/MAP03BACKV1C.csv", LAYER_BACKGROUNDC); 
        LoadMapCSV("Data/MAP03BACKV1SE.csv", LAYER_BACKGROUNDSE);
        LoadMapCSV("Data/MAP03BACKV1TE.csv", LAYER_BACKGROUNDTE);
        LoadMapCSV("Data/MAP03MIDV1SE.csv", LAYER_MIDDLEGROUNDSE);
        LoadMapCSV("Data/MAP03MIDV1TE.csv", LAYER_MIDDLEGROUNDTE);
        LoadMapCSV("Data/MAP03OBJV1C.csv", LAYER_OBJECTC);
        LoadMapCSV("Data/MAP03OBJV1O.csv", LAYER_OBJECTO); 
        LoadMapCSV("Data/MAP03OBJV1TE.csv", LAYER_OBJECTTE);

        LoadCollisionCSV("Data/AGS_Map_Street_Collision.csv");
    }
}

void Stage::LoadMapCSV(const std::string& filename, eMapLayer Layer)
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
            stageMap[Layer][y][x] = std::stoi(value);
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
void Stage::Draw(float cameraX, float cameraY, eMapLayer Layer)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            // 指定されたレイヤーのチップ番号を取得
            int chipIndex = stageMap[Layer][y][x];

            // 0未満、または TILE_MAX 以上の不正な数値はスルー
            if (chipIndex < 0 || chipIndex >= TILE_MAX) continue;

            // 画像ハンドルが有効な場合のみ描画
            if (tileImages[Layer][chipIndex] != -1)
            {
                int drawX = x * TILE_SIZE - (int)cameraX;
                int drawY = y * TILE_SIZE - (int)cameraY;

                DrawGraph(drawX, drawY, tileImages[Layer][chipIndex], TRUE);
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