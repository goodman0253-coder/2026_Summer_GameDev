#pragma once
#include "GameObject.h"
#include "AsoUtility.h"

class SceneManager;
class GameScene;
class BreadBase;

class Player : public GameObject
{
public:
    static constexpr int PLAYER_WID = 64;			// プレイヤーの横サイズ
    static constexpr int PLAYER_HIG = 64;			// プレイヤーの縦サイズ
    static constexpr int PLAYER_ANIM_XNUM = 4; // 爆発画像ファイル内の横方向のパターン数
    static constexpr int PLAYER_ANIM_YNUM = 2; // 爆発画像ファイル内の縦方向のパターン数
    static constexpr int PLAYER_ANIM_MAX = PLAYER_ANIM_XNUM * PLAYER_ANIM_YNUM;// 爆発アニメーションのパターン数

	Player();
    ~Player();

    bool SystemInit();

    bool GameInit();

    void Update() override;

	void Draw(float camX, float camY) override;

    void Run();

	void Jump();

	// 外部からプレイヤーの幅と高さを取得するための関数
	int GetWid()const { return PLAYER_WID; }
	int GetHig()const { return PLAYER_HIG; }

    // 外部（GameSceneなど）から体力を取得するための関数
    int GetHp() const { return hp; }

    // 無敵中かどうかを判定する関数（タイマーが0より大きければ無敵）
    bool IsInvincible() const { return invincibleTimer > 0; }

    // ダメージを受ける関数
    void ApplyDamage();

    void Die();

    // アニメーション状態
    enum class ANIM_STATE
    {
        IDLE,
        RUN,
        JUMP,
        THROW,
        MAX
    };

    //パン
    enum class BREAD_TYPE
    {
        NORMAL,   // 通常のパン
        MELONPAN,    // メロンパン
		CROISSANT,  // クロワッサン
        MAX       // 種類の最大数（切り替えループ用）
    };


    float playerPosx;
    float playerPosy;

    float GetPosX() const { return playerPosx; }
    float GetPosY() const { return playerPosy; }

    void SetGameScene(GameScene* scene) { gameScene = scene; };

    BREAD_TYPE GetCurrentBreadType() const { return currentBreadType; }
    int GetShotBreadTimer(int idx) const { return shotBreadTimers[idx]; }
    int GetMaxCoolTime(int idx) const { return MAX_COOL_TIME[idx]; }

    // 指定した種類のパンを解放する関数
    void UnlockBread(BREAD_TYPE type) { isBreadUnlocked[static_cast<int>(type)] = true; }

    // 指定した種類のパンが解放されているか確認する関数
    bool IsBreadUnlocked(BREAD_TYPE type) const { return isBreadUnlocked[static_cast<int>(type)]; }

private:
    float vy;
    int image;
    bool onGround;
    float speed = 5;
    int hp = 5;                        // 現在の体力（初期値マックス5）
    static const int MAX_HP = 5;       // 最大体力
    int invincibleTimer = 0;           // 無敵時間タイマー（フレーム単位）
    bool jumpableFlg = false;

    int breadThrowPoseTime = 60;
    bool breadThrowPoseFlg = false;

    int playerImageArray[PLAYER_ANIM_MAX];

    int shotCoolTime;      // クールタイム用のタイマーカウンター
    AsoUtility::DIR playerDir;

    int animTimer = 0;
    int animNoNow = 1;

    const int ANIM_SPEED = 8;
    const int ANIM_RUN_NO_MAX = 2;

    bool isMoving = false;
    
    // アニメーション状態
    ANIM_STATE animState;

    GameScene* gameScene = nullptr;
    SceneManager* sceneManager = nullptr;

    BREAD_TYPE currentBreadType = BREAD_TYPE::NORMAL;
    int shotBreadTimers[static_cast<int>(BREAD_TYPE::MAX)] = { 0 };

    const int MAX_COOL_TIME[static_cast<int>(BREAD_TYPE::MAX)] = 
    {
        45,  // NORMAL のクールタイム
        120, //Melonoanのクールタイム
    };
    int breadIdx; 

    bool isBreadUnlocked[static_cast<int>(BREAD_TYPE::MAX)] = { true, false };

};

