#pragma once
#include "GameObject.h"
// プレイヤー（GameObjectを継承）
class Player : public GameObject
{
private:
    float vy;
    int image;
    bool onGround;

public:
    static constexpr int PLAYER_WID = 16;			// プレイヤーの横サイズ
    static constexpr int PLAYER_HIG = 16;			// プレイヤーの縦サイズ

	Player();
    virtual ~Player();

    bool SystemInit();

    bool GameInit();

    void Update() override;

	void Draw() override;

	void Jump();

    float playerPosx = 0.0f;
    float playerPosy = 0.0f;

};

