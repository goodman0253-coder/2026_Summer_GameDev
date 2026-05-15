#pragma once

class TitleScene
{
public:
	TitleScene(void);
	~TitleScene(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);


private:
	int image;
	int prevSpaceKey, nowSpaceKey;

};