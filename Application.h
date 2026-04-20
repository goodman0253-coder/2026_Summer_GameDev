#pragma once
class Application
{
public:
	Application();
	~Application();

	bool SystemInit(void);
	void Run();
	bool Release(void);

private:
	void Update(void);
	void Draw(void);

};

