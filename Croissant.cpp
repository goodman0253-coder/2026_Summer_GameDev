#include "Croissant.h"
#include "BreadBase.h"
#include <DxLib.h>
#include "Player.h"
#include <math.h>

Croissant::Croissant(float spawnX, float spawnY, AsoUtility::DIR direction, Player* player): BreadBase(spawnX, spawnY, direction)
{
	playerLp = player;

	//speedX = 0.0f;

	width = 32;
	height = 32;
	isAlive = true;

	startX = spawnX;
	startY = spawnY;

	// プレイヤーの向きによって、右カーブか左カーブかを決定する
	if (direction == AsoUtility::DIR::LEFT)
	{
		directionSign = -1;
	}
	else
	{
		directionSign = 1;
	}

	imageHandle = LoadGraph("image/croissant.png");
}

void Croissant::Update()
{
	if (!isAlive) return;

	timer++;

	if (state == State::FORWARD)
	{
		// 往路：投げた方向にまっすぐ飛ぶ
		// speedX は BreadBase のコンストラクターで自動計算された値を使用
		x += speedX;


		if (timer > 30)
		{
			state = State::FORWARD_UP;
		}
	}
	else if (state == State::FORWARD_UP)
	{
		// 往路：上方向に飛ぶ
		x += speedX; // 投げた方向に移動
		y -= speed; // 上方向に移動
		if (timer > 45)
		{
			state = State::UP;
		}
	}
	else if (state == State::UP)
	{
		// 往路：上方向に飛ぶ
		y -= speed; // 上方向に移動
		if (timer > 60)
		{
			state = State::BACK_UP;
		}
	}
	else if (state == State::BACK_UP)
	{
		// 復路：上方向に飛ぶ
		x -= speedX; // 投げた方向と逆に移動
		y -= speed; // 上方向に移動
		if (timer > 75)
		{
			state = State::RETURN;
		}
	}
	else if (state == State::RETURN)
	{
		float targetX = startX;
		float targetY = startY;

		// 発射位置へのベクトルを計算
		float dx = targetX - x;
		float dy = targetY - y;
		float distance = sqrtf(dx * dx + dy * dy);

		if (distance > 5.0f)
		{
			// 発射位置に向かってじわじわ加速しながら戻る
			x += (dx / distance) * (speed + 2.0f);
			y += (dy / distance) * (speed + 2.0f);
		}


		if (distance < 20.0f)
		{
			Kill();
		}
	}


#if 0
		theta += 0.035f;

		float duration = 120.0f;
		float progress = (float)timer / duration; // 0.0（開始） 〜 1.0（終了）

		if (progress <= 1.0f)
		{
			// 💡 progress に DX_PI (180度) をかけることで、sin波が 0 -> 1 -> 0 と滑らかに変化します。
			float angleRad = progress * DX_PI;
			float wave = sinf(angleRad); // 0.0 から始まって、中間で 1.0 になり、最後は 0.0 に戻る

			// 横方向（X軸）：行きは前に進み、戻りは後ろに帰る
			x = startX + (wave * maxRangeX * directionSign);

			// 縦方向（Y軸）：上にふんわりと丸みを帯びて膨らむカーブを描く
			// wave（0 -> 1 -> 0）をそのまま使うことで、上に行って戻る動きになります
			y = startY - (wave * maxRangeY);
		}
		else
		{
			// 120フレーム（progressが1.0を超えたら）経過で、発射位置にぴったり戻って消滅
			Kill(); //[cite: 22]
		}
#endif

}

void Croissant::Draw(float camX, float camY)
{
	if (!isAlive) return;

	int drawX = (int)(x - camX) + width ;
	int drawY = (int)(y - camY) + height ;

	if (imageHandle != -1)
	{
		// 回転描画：timerを使って毎フレーム回転角を増やす
		double angle = (timer * 15.0) * DX_PI / 180.0;
		DrawRotaGraph(drawX, drawY, 2, angle, imageHandle, TRUE);
	}
}