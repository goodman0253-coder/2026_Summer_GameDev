#pragma once
#include <string>
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"
#include "Application.h"

class GameScene;

class EnemyBase
{
public:
	enum class ENEMY_TYPE //ENEMYの種類
	{
		E_TYPE_ST1_A,
		
		E_TYPE_MAX,
	};
	static constexpr int ANIM_NUMS = 2; // 表示するアニメーションの数
	static constexpr int CHARA_MAX = ANIM_NUMS * static_cast<int>(AsoUtility::DIR::MAX);
	static constexpr int ANIM_INTERVAL = 30; // アニメーションの更新間隔
	int animNo; // 現在表示しているアニメーション番号

	EnemyBase();
	~EnemyBase(void);

	virtual bool SystemInit(GameScene* gs); // 初期化処理(最初の１回のみ実行)
	virtual void GameInit(void); // ゲーム起動・再開時に必ず呼び出す処理
	virtual void GameInit(Vector2F spawnPos); // ゲーム起動・再開時に必ず呼び出す処理(スポーン位置指定)
	virtual void Update(void); // 更新処理
	virtual void Draw(void); // 描画処理
	virtual bool Release(void); // 解放処理(最後の１回のみ実行)

	// 敵キャラ個別のパラメータ設定処理
	virtual void SetEnemyParam(void) = 0;

	// 敵の座標を取得
	virtual Vector2F GetEnemyPos(void) { return pos; }

	// 敵の画像サイズを取得
	virtual Vector2 GetEnemySize(void) { return size; }

	// 敵の生存状態を取得する
	virtual bool GetAlive(void) { return aliveFlg; }

	// 敵の生存状態を設定する
	virtual void SetAlive(bool bflg) { aliveFlg = bflg; }

	// 移動方向の設定
	virtual void setMoveDirection(Vector2F dirVec);

	// 敵にダメージを与える
	void SetDamage(int dp);
	
	// 敵の画像サイズ
	Vector2 size;
protected:
	GameScene* gInst; // ゲームシーンのインスタンスのポインタ

	// 敵画像のハンドル番号テーブル
	int img[static_cast<int>(AsoUtility::DIR::MAX)][ANIM_NUMS];

	Vector2F pos; // 敵表示座標
	int dir; // 敵が向いている方向
	int animCounter; // アニメーションカウンター
	int hp; // ヒットポイント
	int hpMax; // ヒットポイント最大値
	bool aliveFlg; // 生存フラグ

	// 敵の画像ファイル名
	std::string imgFName;
	// 敵の移動速度
	float speed;
};

