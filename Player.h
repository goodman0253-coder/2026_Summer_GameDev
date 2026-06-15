#pragma once
#include "GameObject.h"
#include "AsoUtility.h"

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

    // 外部（GameSceneなど）から体力を取得するための関数
    int GetHp() const { return hp; }

    // 無敵中かどうかを判定する関数（タイマーが0より大きければ無敵）
    bool IsInvincible() const { return invincibleTimer > 0; }

    // ダメージを受ける関数
    void ApplyDamage();

    // アニメーション状態
    enum class ANIM_STATE
    {
        IDLE,
        RUN,
        JUMP,
        THROW,
        MAX
    };

    float playerPosx ;
    float playerPosy ;

    float GetX() const { return playerPosx; }
    float GetY() const { return playerPosy; }

    void SetGameScene(GameScene* scene) { gameScene = scene; };

private:
    float vy;
    int image;
    bool onGround;
    float speed = 5;
    int hp = 5;                        // 現在の体力（初期値マックス5）
    static const int MAX_HP = 5;       // 最大体力
    int invincibleTimer = 0;           // 無敵時間タイマー（フレーム単位）

    int playerImageArray[PLAYER_ANIM_MAX];

    int shotCoolTime;      // クールタイム用のタイマーカウンター
    AsoUtility::DIR playerDir;

    int animTimer = 0;
    int animNoNow = 0;

    const int ANIM_SPEED = 8;
    
    // アニメーション状態
    ANIM_STATE animState;

    GameScene* gameScene = nullptr;

};

