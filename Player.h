#pragma once
#include "GameObject.h"
// プレイヤー（GameObjectを継承）
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

    float playerPosx ;
    float playerPosy ;

    float GetX() const { return playerPosx; }
    float GetY() const { return playerPosy; }

private:
    float vy;
    int image;
    bool onGround;
    float speed = 5;

    int playerImageArray[PLAYER_ANIM_MAX]; // 爆発の画像のハンドル番号テーブル

    int animTimer = 0;
    int animNoNow = 0;

    const int ANIM_SPEED = 8;

};

