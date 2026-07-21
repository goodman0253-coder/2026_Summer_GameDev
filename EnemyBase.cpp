#include "EnemyBase.h"
#include "Player.h"
#include "Stage.h"
#include <DxLib.h>
#include "GameScene.h"

EnemyBase::EnemyBase()
{

}

EnemyBase::~EnemyBase(void)
{

}

bool EnemyBase::SystemInit(GameScene* gs) // 初期化処理(最初の１回のみ実行)
{
	printfDx("一回目EnemyBaseSystemInit(): imgFName=%s size=%d,%d\n", imgFName.c_str(), size.x, size.y);

	gInst = gs;
	// 敵キャラ個別のパラメータ設定処理
	SetEnemyParam();
	std::string path = "image/";
	path += imgFName;
	printfDx("二回目EnemyBaseSystemInit(): imgFName=%s size=%d,%d\n", imgFName.c_str(), size.x, size.y);
	int err = LoadDivGraph(path.c_str(), CHARA_MAX,
		static_cast<int>(AsoUtility::DIR::MAX), ANIM_NUMS,
		size.x, size.y, img[0]);

	printfDx("三回目EnemyBaseSystemInit(): LoadDivGraph result=%d path=%s\n", err, path.c_str());
	if (err == -1)return false;
	dir = 0;
	return true;
}

void EnemyBase::GameInit(void) // ゲーム起動・再開時に必ず呼び出す処理
{

	// 敵の初期位置を設定する(引数無しの場合デフォルト位置に呼び出し)
	GameInit(Vector2F(500.0f, 1250.0f));

}

void EnemyBase::GameInit(Vector2F spawnPos) // ゲーム起動・再開時に必ず呼び出す処理(スポーン位置指定)
{
	pos = spawnPos;
	animCounter = 0;
	aliveFlg = true;
	hasAppearedOnScreen = false;
	hp = hpMax;
	EoB = eob;
}

void EnemyBase::Update(void) // 更新処理
{
	if (hp <= 0)
	{
		aliveFlg = false;
		return; // これ以上何もしない
	}

	
	// カメラ座標の取得
	float camX = gInst->GetCameraX();
	float camY = gInst->GetCameraY();

	if (EoB == 0)
	{
		// カメラの外に出たら消える
		if (pos.x < camX - 400 || pos.x > camX + 1280 + 400 ||
			pos.y < camY - 400 || pos.y > camY + 720 + 400)
		{
			aliveFlg = false;
		}
		else
		{
			// カメラの中にいるときは更新処理を行う
			if (hp > 0)
			{
				aliveFlg = true;
			}
		}

		if (aliveFlg == false)
		{
			return;
		}
	}
	else
	{
		if (hp > 0)
		{
			aliveFlg = true;
		}
	}

	if (aliveFlg == false)
	{
		return;
	}

	// アニメーションカウンタの進行
	animCounter++;
	animNo = (animCounter / ANIM_INTERVAL) % ANIM_NUMS; //現在表示しているアニメーション番号
	if (animCounter >= ANIM_INTERVAL * ANIM_NUMS)animCounter = 0; // カウンタのリセット

	if (invincibleTimer > 0)
	{
		invincibleTimer--; // 1フレームごとに1減らす（60フレーム = 1秒）
	}
	;
}

void EnemyBase::Draw(void) // 描画処理
{
	// 死んでいるときは消して描画しない
	if (!aliveFlg)return;

	bool skipSprite = false;
	if (IsInvincible())
	{
		if ((invincibleTimer / 4) % 2 == 0)
		{
			skipSprite = true; // このフレームは本体の描画をスキップ
		}
	}

	float stposX = gInst->GetCameraX();	//カメラ座標X
	float stposY = gInst->GetCameraY();	//カメラ座標Y

	// 敵の画像を描画する
	if (!skipSprite)
	{
		DrawGraph(pos.x - size.x / 2 - stposX,
			pos.y - size.y / 2 - stposY,
			img[dir][animNo], true);
	}

	//// 当たり判定の可視化（デバッグ用）
	//if (EoB == 0);
	//{
	//	DrawBox(pos.x - 16 - stposX, pos.y - size.y / 2 - stposY,
	//		pos.x + 16 - stposX, pos.y + size.y / 2 - stposY,
	//		GetColor(255, 0, 0), FALSE);
	//}
	//
	//if (EoB > 0);
	//{
	//	DrawBox(pos.x - size.x / 2 - stposX, pos.y - size.y / 2 - stposY,
	//		pos.x + size.x/2 - stposX, pos.y + size.y / 2 - stposY,
	//		GetColor(255, 0, 0), FALSE);
	//}
	

	// 敵ののこりHPを表示する（デバッグ用）
	//DrawFormatString(pos.x - stposX, pos.y - size.y / 2 - 20 - stposY, GetColor(255, 255, 255), "HP: %d", hp);

	// 生死を表示（デバッグ用）
	//DrawFormatString(pos.x - stposX, pos.y + size.y / 2 + 5 - stposY, GetColor(255, 255, 255), "Alive: %s", aliveFlg ?"True" : "False");

	 // ボスの場合、画面右上に体力ゲージを表示する
	 if (EoB > 0)
	 {
		 float camX = gInst->GetCameraX();
		 float camY = gInst->GetCameraY();

		 // 画面サイズを取得
		 float screenW = 1280.0f;
		 float screenH = 720.0f;

		 // ボスが画面内に映っているかを判定
		 bool isVisibleX = (pos.x + size.x / 2.0f > camX) && (pos.x - size.x / 2.0f < camX + screenW);
		 bool isVisibleY = (pos.y + size.y / 2.0f > camY) && (pos.y - size.y / 2.0f < camY + screenH);

		 if (isVisibleX && isVisibleY)
		 {
			 hasAppearedOnScreen = true;
		 }

		 // 画面内に一度でも映ったことがあればゲージを描画し続ける
		 if (hasAppearedOnScreen)
		 {
			 int currentHp = hp;
			 int maxHp = hpMax;
			 int gaugeWidth = 300;
			 int gaugeHeight = 24;

			 int gaugeX = 1280 - gaugeWidth - 50;
			 int gaugeY = 50;


			 // HPゲージの背景を描画
			 DrawBox(gaugeX - 10, gaugeY - 35, gaugeX + gaugeWidth + 10, gaugeY + gaugeHeight + 10, GetColor(0, 0, 0), TRUE);
			 // HPゲージの枠を描画
			 DrawBox(gaugeX, gaugeY, gaugeX + gaugeWidth, gaugeY + gaugeHeight, GetColor(255, 255, 255), FALSE);

			 DrawFormatString(gaugeX, gaugeY - 25, GetColor(255, 255, 255), "Boss HP  %d / %d", currentHp, maxHp);

			 // 現在のHPに応じたゲージの幅を計算
			 int currentBarWidth = (int)((float)currentHp / (float)maxHp * gaugeWidth);
			 if (currentBarWidth < 0) currentBarWidth = 0;

			 // HPゲージの色を決定
			 unsigned int barColor = (currentHp <= maxHp / 4) ? GetColor(255, 0, 0) : GetColor(0, 255, 0);

			 // 現在のHPに応じたゲージを描画
			 if (currentBarWidth > 0)
			 {
				 DrawBox(gaugeX + 2, gaugeY + 2, gaugeX + currentBarWidth - 2, gaugeY + gaugeHeight - 2, barColor, TRUE);
			 }
		 }
	 }

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

// 敵にダメージを与える
void EnemyBase::SetDamage(int dp)
{
	if (IsInvincible()) 
	{
		return; // 無敵中はダメージを受けない
	}

	hp -= dp;
	if (hp <= 0) {
		hp = 0;
		aliveFlg = false;
	}

	if (hp > 0)
	{
		// まだ生きていれば1秒間（60フレーム×1＝60フレーム）の無敵をつける
		invincibleTimer = 60;
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
			dir = static_cast<int> (AsoUtility::DIR::LEFT);
		}
		else
		{
			dir = static_cast<int>(AsoUtility::DIR::RIGHT);
		}
	}
}