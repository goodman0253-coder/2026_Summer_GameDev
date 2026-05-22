#pragma once
#include <string>

enum eOfficeMapLayer
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
    Stage();
    ~Stage();

    void Initialize(); // 初期化（画像の読み込みやCSV読み込みのトリガー）
    void Draw(float cameraX, float cameraY, eOfficeMapLayer OLayer); // 描画処理
private:
    static const int TILE_SIZE = 32;     // タイル1マスのサイズ(32x32ピクセル)
    static const int MAP_WIDTH = 200;    // CSVの横の列数 (※MAP0V1.csvの実際の列数に合わせてください)
    static const int MAP_HEIGHT = 20;    // CSVの縦の行数

    int stageMap[LAYER_MAX][MAP_HEIGHT][MAP_WIDTH]; // マップデータを保持する配列

    static const int TILE_MAX = 500;     // 読み込むタイルの最大数
    int tileImages[TILE_MAX];            // 分割した画像を保存する配列

    // CSVファイルを読み込むための内部関数
    void LoadMapCSV(const std::string& filename,eOfficeMapLayer OLayer);

};

