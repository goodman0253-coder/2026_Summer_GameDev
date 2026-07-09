#pragma once
#include <string>

enum eMapLayer
{
    LAYER_BACKGROUND = 0, // 背景
    LAYER_MIDDLEGROUND,   // 奥の壁や床
    LAYER_OBJECT,         // 障害物
    LAYER_FOREGROUND,     // 前景

    LAYER_MAX
};

class Stage
{

public:
    static const int TILE_SIZE = 32;     // タイル1マスのサイズ(32x32ピクセル)
    static const int MAP_WIDTH = 230;
    static const int MAP_HEIGHT = 60;

    Stage();
    ~Stage();

    void Initialize(int stageNum); // 初期化（画像の読み込みやCSV読み込みのトリガー）
    void Draw(float cameraX, float cameraY, eMapLayer OLayer); // 描画処理

    bool CheckCollision(float worldX, float worldY);

    int GetMapWidth() const { return MAP_WIDTH; }
    int GetMapHeight() const { return MAP_HEIGHT; }

private:
    int stageMap[LAYER_MAX][MAP_HEIGHT][MAP_WIDTH];
    int collisionMap[MAP_HEIGHT][MAP_WIDTH];

    static const int TILE_MAX = 500;     // 読み込むタイルの最大数
    int tileImages[TILE_MAX];            // 分割した画像を保存する配列
    int tileImages2[TILE_MAX];            // 分割した画像を保存する配列

    // CSVファイルを読み込むための内部関数
    void LoadMapCSV(const std::string& filename, eMapLayer OLayer);

    void LoadCollisionCSV(const std::string& filename);
};

