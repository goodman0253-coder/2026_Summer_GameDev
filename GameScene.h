#pragma once
#include "BaseScene.h"
#include "EnemyBase.h"
#include <vector>
#include "BreadBase.h"
class Player;
class Stage;
class SceneManager;
class Application;

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
	void AddBread(BreadBase* bread) { breadList.push_back(bread); }

	float GetCameraX() const { return cameraX; }
	float GetCameraY() const { return cameraY; }
	float GetScreenW() const { return SCREEN_WIDTH; }

	void SetSceneManager(SceneManager* sm) { sceneManager = sm; }
private:

	Player* player;
	Stage* stage;
	SceneManager* sceneManager = nullptr;
	Application* application = nullptr;
	std::vector<EnemyBase*> enemys;
	std::vector<BreadBase*> breadList;
	float cameraX = 0.0f;
	float cameraY = 0.0f;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	//仮のクリア
	bool isClearTriggered = false; // クリア演出が開始されたか
	int clearTimer = 0;            // 3秒を数えるためのタイマー
	
};

