#include "DxLib.h"
#include "Player.h"

Player::Player() 
{



	LoadDivGraph("image/player.png", PLAYER_ANIM_MAX,PLAYER_ANIM_XNUM, PLAYER_ANIM_YNUM,PLAYER_WID, PLAYER_HIG, playerImageArray)
}

Player::~Player()
{

}


bool Player::SystemInit()
{

	
=======
bool Player::SystemInit()  
{  
	vy = 0.0f;  
		return false;
	}


	return true;

}

bool Player::GameInit()
{
	vy = 0.0f;
	playerPosx = 100;
	playerPosy = 100;
	return true;
}

void Player::Update() 
{
    // 前に書いた移動や重力の処理をここに書く
    if (CheckHitKey(KEY_INPUT_RIGHT)) playerPosx += 5.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPosx -= 5.0f;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		Jump();
	}


	vy += 0.5f; // 重力
	if (vy > 5.0f)
	{
		vy = 5.0f;
	}
	playerPosy += vy; // 座標を更新

	// 地面に衝突したら止まる
	if (playerPosy > 300.0f)
	{
		playerPosy = 300.0f;
		vy = 0.0f;
	}
}

void Player::Draw()
{

	// もし image が -1 (失敗状態) なら、今この瞬間に読み込みを試みる
#if 0 
	if (image == -1) {
		image = LoadGraph("player.png");

		if (image != -1) {
			// ここで成功したら「読み込むタイミングが早すぎた」のが原因
			printfDx("Draw内で読み込み成功！ハンドル: %d\n", image);
		}
		else {
			// ここでも失敗したら「ファイル名か場所」が原因
			printfDx("Draw内でも読み込み失敗...パスを確認してください\n");
		}
	}
	printfDx("Handle: %d  Pos: %f, %f\n", image, 30, 30);
#endif
	printfDx("X:%.1f Y:%.1f Handle:%d\n", playerPosx, playerPosy, image);

    DrawGraph((int)playerPosx, (int)playerPosy, playerImageArray[0], TRUE);


}


void Player::Jump() 
{
    vy = -12.0f;
}