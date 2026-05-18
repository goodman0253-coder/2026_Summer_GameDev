#include "Vector2F.h"
#include "Vector2.h"

// デフォルトコンストラクタ
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}

Vector2::Vector2(Vector2F value)
{
<<<<<<< HEAD
=======

>>>>>>> 47ac59c752867f8ce9ca122c0543236f31fd0070
}

Vector2F Vector2::ToVector2F(void)
{
	Vector2F ret;
	ret.x = static_cast<float>(x);
	ret.y = static_cast<float>(y);
	return ret;
}

