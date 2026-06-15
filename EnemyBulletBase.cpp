#include "EnemyBulletBase.h"
#include "GameScene.h"
#include <DxLib.h>

// EnemyBulletBaseクラスのコンストラクタとデストラクタ
EnemyBulletBase::EnemyBulletBase() :gInst(nullptr), imgHandle(-1), aliveFlg(true) {}
EnemyBulletBase::~EnemyBulletBase(void)
{
}

bool EnemyBulletBase::SystemInit(GameScene* gs) // 初期化処理(最初の１回のみ実行)
{
	gInst = gs;

	imgHandle = LoadGraph("image/Stage1_EnemyA_Bulled.png");
	if (imgHandle == -1) return false;

	size = { 16, 16 };
	return true;
}

void EnemyBulletBase::GameInit(Vector2F spoanPos, Vector2F vel) // ゲーム起動・再開時に必ず呼び出す処理(スポーン位置指定)
{
	pos = spoanPos;
	velocity = vel;
	aliveFlg = true;
}

void EnemyBulletBase::Update(void) // 更新処理
{
	// 弾の位置を移動する(基本移動)
	pos.x += velocity.x;
	pos.y += velocity.y;

	// カメラ座標の取得
	float camX = gInst->GetCameraX();
	float camY = gInst->GetCameraY();

	// カメラの外に出たら消える
	if (pos.x < camX - 200 || pos.x > camX + 1920 + 200 ||
		pos.y < camY - 200 || pos.y > camY + 1080 + 200)
	{
		aliveFlg = false;
	}
}

void EnemyBulletBase::Draw(void) // 描画処理
{
	float camX = gInst->GetCameraX();	//カメラ座標X
	float camY = gInst->GetCameraY();	//カメラ座標Y

	DrawGraph(static_cast<int>(pos.x - size.x / 2 - camX),
				static_cast<int>(pos.y - size.y / 2 - camY),
				imgHandle, true);
	// 当たり判定の可視化（デバッグ用）
	DrawBox(static_cast<int>(pos.x - size.x / 2 - camX), static_cast<int>(pos.y - size.y / 2 - camY),
			static_cast<int>(pos.x + size.x / 2 - camX), static_cast<int>(pos.y + size.y / 2 - camY),
		GetColor(255, 0, 0), FALSE);
}

bool EnemyBulletBase::Release(void) // 解放処理(最後の１回のみ実行)
{
	if (imgHandle != -1) {
		DeleteGraph(imgHandle) == -1;
		imgHandle = -1;
	}
	return true;
}