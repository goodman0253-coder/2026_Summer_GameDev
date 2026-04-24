#pragma once
class GameObject
{ 
protected:
    float x, y; // 座標
public:
	virtual ~GameObject() {} // 仮想デストラクタ
    virtual void Update() = 0; // 更新処理（純粋仮想関数）
    virtual void Draw() = 0;   // 描画処理
};



