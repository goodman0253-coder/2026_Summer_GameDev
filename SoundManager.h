#pragma once
#include <map>
#include <string>

class SoundManager
{
private:
    // コンストラクタを隠して外部からの new を禁止する（シングルトン）
    SoundManager() = default;
    ~SoundManager();

    std::map<std::string, int> bgmList; // BGM管理用 (キー名, ハンドル)
    std::map<std::string, int> seList;  // SE管理用 (キー名, ハンドル)

    std::string currentBgmKey = "";    // 現在再生中のBGM名

public:
    // 唯一のインスタンスを取得する関数
    static SoundManager& GetInstance()
    {
        static SoundManager instance;
        return instance;
    }

    // 音声の読み込み
    void LoadBGM(const std::string& key, const char* filePath);
    void LoadSE(const std::string& key, const char* filePath);

    int GetSEHandle(const std::string& key) { return (seList.find(key) != seList.end()) ? seList[key] : -1; }

    // 再生・停止
    void PlayBGM(const std::string& key, bool loop = true);
    void StopBGM();
    void PlaySE(const std::string& key);

    // 全解放（ゲーム終了時に呼ぶ）
    void ReleaseAll();
};

