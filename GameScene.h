#pragma once
#include "BaseScene.h"
#include "EnemyBase.h"
#include <vector>
#include "BreadBase.h"
#include "RecipeBase.h"
class Player;
class Stage;

class SceneManager;
class Application;

class EnemyBulletBase;


class GameScene :public BaseScene
{
private:

	Player* player = nullptr;
	Stage* stage = nullptr;
	SceneManager* sceneManager = nullptr;
	Application* application = nullptr;
	std::vector<EnemyBase*> enemys;
	std::vector<EnemyBulletBase*> enemyBullets;

	std::vector<BreadBase*> breadList;
	std::vector<RecipeBase*> recipeList;

	float cameraX = 0.0f;
	float cameraY = 800.0f;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	int buttunImageC = -1;
	int buttunImageV = -1;
	int RTImage = -1;
	int LTImage = -1;
	int attackUIImage = -1;
	int changeUIImage = -1;

	// 仮のクリア条件とタイマー
	bool isClearTriggered = false; // クリア条件が満たされたかどうか
	int clearTimer = 0;            // クリア条件が満たされてからの経過フレーム数
	bool isPlayerAlive = true; // プレイヤーが生存しているかどうか

	int currentStageNum = 1;


	struct EnemySpawnDate {
		int enemyType;
		float spawnX;
		float spawnY;
		bool isSpawned;
	};

	std::vector<EnemySpawnDate> enemySpawnList; // 敵のスポーンデータを格納するベクター
	static constexpr int CHIP_SIZE = 32;

	void LoadEnemyCSV(const std::string& filePath); // CSVファイルから敵のスポーンデータを読み込む関数

	EnemyBase* CreateEnemyFromType(int enemyType);
public:
	int PX = 0; // プレイヤーのX座標
	int PY = 0; // プレイヤーのY座標
	int BX = 0; // 敵の弾のX座標
	int BY = 0; // 敵の弾のY座標
	int EX = 0; // 敵のX座標
	int EY = 0; // 敵のY座標
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
	void AddRecipe(RecipeBase* recipe) { recipeList.push_back(recipe); }
	size_t GetBreadCount() const { return breadList.size(); }

	float GetCameraX() const { return cameraX; }
	float GetCameraY() const { return cameraY; }
	float GetScreenW() const { return SCREEN_WIDTH; }

	void SetSceneManager(SceneManager* sm) { sceneManager = sm; }

	void AddEnemyBullet(EnemyBulletBase* newBullet, Vector2F spawnPos, Vector2F vel);

	void SetStageNum(int num) { currentStageNum = num; }

	void CollisionCheckPB(); // プレイヤーと敵の弾の当たり判定を行う関数
	void CollisionCheckPE(); // プレイヤーと敵の当たり判定を行う関数
	void CollisionCheckEB(); // 敵とパンの当たり判定を行う関数
	void CollisionCheckPR(); // プレイヤーとレシピアイテムの当たり判定を行う関数
};

