#pragma once
#include "BaseScene.h"
#include "EnemyBase.h"
#include <vector>
class Player;
class Stage;
class EnemyBulletBase;

class GameScene:public BaseScene
{
public:
	Stage* GetLpStage(void) { return stage; }
	Player* GetLpPlayer(void) { return player; }
	GameScene();
	~GameScene();
	bool SystemInit(void);
	bool GameInit(void);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Release(void);

	float GetCameraX() const { return cameraX; }
	float GetCameraY() const { return cameraY; }

	void AddEnemyBullet(EnemyBulletBase* newBullet, Vector2F spawnPos, Vector2F vel);
private:

	Player* player;
	Stage* stage;
	std::vector<EnemyBase*> enemys;
	std::vector<EnemyBulletBase*> enemyBullets;

	float cameraX = 0.0f;
	float cameraY = 0.0f;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	bool isPlayerAlive = true; // プレイヤーの生存状態を管理するフラグ

};

