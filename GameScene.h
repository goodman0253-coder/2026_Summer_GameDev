#pragma once
class Player;

class GameScene
{
public:
	GameScene();
	~GameScene();
	bool SystemInit(void);
	bool GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);
private:
	Player* player;
};

