#pragma once
class GameScene;

class Application
{
public:
	Application();
	~Application();

	bool SystemInit(void);
	bool GameInit(void);
	void Run();
	bool Release(void);

private:
	void Update(void);
	void Draw(void);
	GameScene* gameScene;
};

