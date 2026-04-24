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
	Player();

    void Update() override;
        // キー入力で移動したり、重力を
	void Draw() override;
        // プレイヤーを
	void Jump();
        //ジャンプ特有の処理 
};

