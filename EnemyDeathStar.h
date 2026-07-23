#pragma once
#include "EnemyBulletBase.h"
class GameScene;
class Star
{
public:
	bool SystemInit(GameScene* gs);
	void SetPos(Vector2F p) { pos = p; }
	void Update(void);
	void Draw(void);
	bool Release(void);
private:
	GameScene* gInst; // ゲームシーンのインスタンスのポインタ
	Vector2F pos; // 弾の現在座標
	Vector2F velocity; // 弾の移動速度、ベクトル
	Vector2 size; // 弾の当たり判定サイズ
	int imgHandle; // 弾の画像ハンドル番号
	bool aliveFlg; // 生存状態
	float aliveTimer; // 生存時間
	int deleteTimer = 0; // 弾の寿命を管理するタイマー
	int deleteLimit = 300; // 弾の寿命の上限（フレーム数）
	float randSP = 0.0f;
	float randSP2 = 0.0f;
	float randRad = 0.0f;
	float SP = 0.0f;
	float rad = 0.0f;
};