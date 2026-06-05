#pragma once
#include "Vector2.h"
#include "Vector2F.h"
class GameScene;

class EnemyBulletBase
{
public:
	EnemyBulletBase();
	~EnemyBulletBase(void);


	virtual bool SystemInit(GameScene* gs); // 初期化処理(最初の１回のみ実行)
	virtual void GameInit(Vector2F spoanPos, Vector2F vel); // ゲーム起動・再開時に必ず呼び出す処理(スポーン位置指定)
	virtual void Update(void) = 0; // 更新処理
	virtual void Draw(void) = 0; // 描画処理
	virtual bool Release(void) = 0; // 解放処理(最後の１回のみ実行)
	
	bool GetAlive(void) { return aliveFlg; }
	void SetAlive(bool bflg) { aliveFlg = bflg; }
	Vector2F GetPos(void) { return pos; }
	Vector2 GetSize(void) { return size; }


protected:
	GameScene* gInst; // ゲームシーンのインスタンスのポインタ
	Vector2F pos; // 弾の現在座標
	Vector2F velocity; // 弾の移動速度、ベクトル
	Vector2 size; // 弾の当たり判定サイズ
	int imgHandle; // 弾の画像ハンドル番号
	bool aliveFlg; // 生存状態

};