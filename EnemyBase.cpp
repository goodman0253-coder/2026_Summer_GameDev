#include "EnemyBase.h"
#include "Player.h"
#include "Stage.h"
#include <DxLib.h>
#include "GameScene.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase(void)
{}

bool EnemyBase::SystemInit(GameScene* gs) // 初期化処理(最初の１回のみ実行)
{
	gInst = gs;
	// 敵キャラ個別のパラメータ設定処理
	SetEnemyParam();
	std::string path = "image/";
	path += imgFName;
	int err = LoadDivGraph(path.c_str(), CHARA_MAX,
		static_cast<int>(AsoUtility::DIR::MAX), ANIM_NUMS,
		size.x, size.y, img[0]);
	if (err == -1)return false;
	dir = 0;
	return true;
}

void EnemyBase::GameInit(void) // ゲーム起動・再開時に必ず呼び出す処理
{

	// 敵の初期位置を設定する
	Vector2F epos = { gInst->GetCameraX(), gInst->GetCameraY() };

	//// 画面外のランダムな位置に出現させる
	//switch (eDir) {
	//case AsoUtility::DIR::UP:
	//	epos.x += GetRand(Application::SCREEN_SIZE_WID - 1);
	//	epos.y += Application::SCREEN_SIZE_HIG;
	//	break;
	//case AsoUtility::DIR::DOWN:
	//	epos.x += GetRand(Application::SCREEN_SIZE_WID - 1);
	//	break;
	//case AsoUtility::DIR::LEFT:
	//	epos.y += GetRand(Application::SCREEN_SIZE_HIG - 1);
	//	epos.x += Application::SCREEN_SIZE_WID;
	//	break;
	//case AsoUtility::DIR::RIGHT:
	//	epos.y += GetRand(Application::SCREEN_SIZE_HIG - 1);
	//	break;
	//}
	

	//pos.x = static_cast<float>(epos.x);
	//pos.y = static_cast<float>(epos.y);

	pos.x = 500;
	pos.y = 531;

	animCounter = 0;
	aliveFlg = true;
	hp = hpMax;
}

void EnemyBase::Update(void) // 更新処理
{
	// アニメーションカウンタの進行
	animCounter++;
	animNo = (animCounter / ANIM_INTERVAL) % ANIM_NUMS; //現在表示しているアニメーション番号
	if (animCounter >= ANIM_INTERVAL * ANIM_NUMS)animCounter = 0; // カウンタのリセット
	//// プレイヤーの位置
	//Vector2 pPos = gInst->GetLpPlayer()->GetPlayerPos();
	//// ベクトル(相手 - 自分)
	//Vector2F vec = Vector2F(
	//	static_cast<float>(pPos.x - pos.x),
	//	static_cast<float>(pPos.y - pos.y)
	//);

	//// ベクトルの大きさ(長さ)
	//float size = sqrtf(vec.x * vec.x + vec.y * vec.y);
	//if (size < speed)
	//{
	//	// ブルブルしないように、
	//	// 移動量よりも、位置差が短い場合は移動しない
	//}
	//else
	//{
	//	// 方向(単位ベクトル)
	//	Vector2F direction;
	//	direction.x = vec.x / size;
	//	direction.y = vec.y / size;
	//	// 座標に移動量を加える
	//	pos.x += static_cast<int>(direction.x * speed);
	//	pos.y += static_cast<int>(direction.y * speed);
	//
	//	// 移動方向の設定
	//	setMoveDirection(direction);
	//}
	
}

void EnemyBase::Draw(void) // 描画処理
{
	float stposX = gInst->GetCameraX();	//カメラ座標X
	float stposY = gInst->GetCameraY();	//カメラ座標Y

	printfDx("表示");
	DrawFormatString(0, 40, GetColor(255, 255, 255), "Counter:%d  No:%d", animCounter, animNo);
	DrawGraph(pos.x - size.x / 2 - stposX,
		pos.y - size.y / 2 - stposY,
		img[dir][animNo], true);

	//DrawGraph(150,500,img[0][0], true);
}

bool EnemyBase::Release(void) // 解放処理(最後の１回のみ実行)
{
	// 敵画像の解放
	bool bval = true;
	for (int dir = static_cast<int>(AsoUtility::DIR::MAX) - 1; dir >= 0; dir--) {
		for (int anim = ANIM_NUMS - 1; anim >= 0; anim--) {
			if (DeleteGraph(img[dir][anim]) == -1)bval = false;
		}
	}
	return bval;
}

void EnemyBase::SetEnemyParam(void) // 敵キャラ個別のパラメータ設定処理
{
	// 敵の画像ファイル名
	imgFName = "Girl_stage1_A.png";
	// 敵の画像サイズ
	size = { 64, 64 };
	// 敵の移動速度
	speed = 0.0f;
	// 敵のヒットポイント最大値
	hpMax = 1;
}

// プレイヤーにダメージを与える
// Input:
// int dp : ダメージ
// Ountput:
// 無し
void EnemyBase::SetDamage(int dp)
{
	hp -= dp;
	if (hp <= 0) {
		hp = 0;
		aliveFlg = false;
	}
}

void EnemyBase::setMoveDirection(Vector2F dirVec)
{
	// 向きを変える(移動量が大きい向きを優先)
	if (abs(dirVec.x) < abs(dirVec.y))
	{
		// 上下
		if (dirVec.y > 0.0f)
		{
			dir = static_cast<int> (AsoUtility::DIR::DOWN);
		}
		else
		{
			dir = static_cast<int> (AsoUtility::DIR::UP);
		}
	}
	else
	{
		// 左右
		if (dirVec.x > 0.0f)
		{
			dir = static_cast<int> (AsoUtility::DIR::RIGHT);
		}
		else
		{
			dir = static_cast<int>(AsoUtility::DIR::LEFT);
		}
	}
}