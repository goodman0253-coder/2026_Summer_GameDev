#pragma once
#include "BaseScene.h"
class Player;
class Stage;

class GameScene:public BaseScene
{


public:
	GameScene();
	~GameScene();
	bool SystemInit(void);
	bool GameInit(void);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Release(void);
private:

	Player* player;
	Stage* stage;
	float cameraX = 0.0f;
	float cameraY = 0.0f;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

};

