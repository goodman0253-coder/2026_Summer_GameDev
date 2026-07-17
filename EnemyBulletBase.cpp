#include "EnemyBulletBase.h"
#include "GameScene.h"
#include <math.h>
#include <DxLib.h>

// EnemyBulletBaseクラスのコンストラクタとデストラクタ
EnemyBulletBase::EnemyBulletBase() :gInst(nullptr), imgHandle(-1), aliveFlg(true), isRotation(true) {}
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
	aliveTimer = 180.0f;
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
	if (pos.x < camX - 20 || pos.x > camX + 1280 + 20 ||
		pos.y < camY - 20 || pos.y > camY + 720 + 20)
	{
		aliveFlg = false;
	}
	aliveTimer -= 1.0f;
	if (aliveTimer <= 0.0f)
	{
		aliveFlg = false;
	}
}

void EnemyBulletBase::Draw(void) // 描画処理
{
	float camX = gInst->GetCameraX();	//カメラ座標X
	float camY = gInst->GetCameraY();	//カメラ座標Y

	double angle = 0.0;

	if (isRotation)
	{
		angle = atan2(velocity.y, velocity.x); // ラジアンを求める
	}

	DrawRotaGraph(static_cast<int>(pos.x - camX),
					static_cast<int>(pos.y - camY),
					1.0, angle,
					imgHandle,
					true);
}

bool EnemyBulletBase::Release(void) // 解放処理(最後の１回のみ実行)
{
	if (imgHandle != -1) {
		DeleteGraph(imgHandle) == -1;
		imgHandle = -1;
	}
	return true;
}