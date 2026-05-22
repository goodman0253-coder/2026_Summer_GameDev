#pragma once
#include "BaseScene.h"
#include "EnemyBase.h"
#include <vector>
class Player;
class Stage;

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
private:

	Player* player;
	Stage* stage;
	std::vector<EnemyBase*> enemys;
	float cameraX = 0.0f;
	float cameraY = 0.0f;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

};

