#include "SoundManager.h"
#include <DxLib.h>

SoundManager::~SoundManager()
{
    ReleaseAll();
}

void SoundManager::LoadBGM(const std::string& key, const char* filePath)
{
    // 既に同じキーで読み込まれていなければロード
    if (bgmList.find(key) == bgmList.end())
    {
        int handle = LoadSoundMem(filePath);
        if (handle != -1) bgmList[key] = handle;
    }
}

void SoundManager::LoadSE(const std::string& key, const char* filePath)
{
    if (seList.find(key) == seList.end())
    {
        int handle = LoadSoundMem(filePath);
        if (handle != -1) seList[key] = handle;
    }
}

void SoundManager::PlayBGM(const std::string& key, bool loop)
{
    // 指定されたBGMが登録されていなければ何もしない
    if (bgmList.find(key) == bgmList.end()) return;

    // 既に同じBGMが流れているなら重ねて再生しない
    if (currentBgmKey == key) return;

    // 別のBGMが流れているなら止める
    StopBGM();

    int playType = loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
    PlaySoundMem(bgmList[key], playType, TRUE);
    currentBgmKey = key;
}

void SoundManager::StopBGM()
{
    if (currentBgmKey != "" && bgmList.find(currentBgmKey) != bgmList.end())
    {
        StopSoundMem(bgmList[currentBgmKey]);
    }
    currentBgmKey = "";
}

void SoundManager::PlaySE(const std::string& key)
{
    if (seList.find(key) != seList.end())
    {
        // SEは重なって鳴ることが多いので、常に裏で1回再生
        PlaySoundMem(seList[key], DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::ReleaseAll()
{
    StopBGM();

    // BGMのメモリ解放
    for (auto& pair : bgmList)
    {
        DeleteSoundMem(pair.second);
    }
    bgmList.clear();

    // SEのメモリ解放
    for (auto& pair : seList)
    {
        DeleteSoundMem(pair.second);
    }
    seList.clear();
}

