#pragma once
class BaseScene;
class TitleScene;
class GameScene;

class Application
{
public:
	static constexpr int SCREEN_SIZE_WID = 1920; // ゲーム画面の横サイズ
	static constexpr int SCREEN_SIZE_HIG = 1080; // ゲーム画面の縦サイズ
	Application();
	~Application();

	bool SystemInit(void);
	bool GameInit(void);
	void Run();
	bool Release(void);

	
private:
	void Update(void);
	void Draw(void);

	TitleScene* titleScene = nullptr;
	GameScene* gameScene = nullptr;

	BaseScene* currentScene = nullptr;

};

