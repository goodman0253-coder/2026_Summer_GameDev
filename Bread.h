#pragma once
class Bread
{
public:
	static constexpr int BREAD_SIZE_WID = 16;
	static constexpr int BREAD_SIZE_HIG = 16;
	static constexpr int BREAD_MOVE_SPEED = 5;

	Bread(void);
	~Bread(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	void BreadCreate(VECTOR bpos);

	bool GetShotFlg(void) { return shotFlg; }
	void SetShotFlg(void) { shotFlg = false; }
	VECTOR GetBreadPos(void) { return pos; }

private:
	int image;
	VECTOR pos;
	bool shotFlg;

};