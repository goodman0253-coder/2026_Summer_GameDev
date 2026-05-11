#pragma once
#include "BaseScene.h"
class Player;

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
};

