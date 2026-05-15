#pragma once
#include "Bread.h"
#include "Player.h"

class BreadManager
{
public:

	BreadManager(void);
	~BreadManager(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	void Collision(void);

private:
	Bread* bread;
	Player* plInst;

	int image;
	int prevShotKey, nowShotkey;

};




