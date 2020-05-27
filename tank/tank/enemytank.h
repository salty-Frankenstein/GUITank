#pragma once
#include"tankbase.h"
#include<array>

/* 敌方坦克原型 */
class EnemyTank :public TankBase {
public:
	EnemyTank(int x, int y, int hp, int damage, int speed, int shootSpeed);
	void Update();
	void DrawTank();
	const static int WIDTH_X = 3;
	const static int WIDTH_Y = 3;
	virtual const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> GetImage();	//有新image的子类重写此函数
protected:
	void GoStraight();
	static const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> image;
	int shootSpeed;	//0~29
};

/* 轻型坦克 */
class LightTank :public EnemyTank {
public:
	LightTank(int x, int y);
private:
	const static int HP = 1;
	const static int DAMAGE = 1;
	const static int SPEED = 13;
	const static int SHOOT_SPEED = 1;
};

/* 装甲车 */
class ArmoredCar :public EnemyTank {
public:
	ArmoredCar(int x, int y);
	const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> GetImage()override;
private:
	const static int HP = 2;
	const static int DAMAGE = 1;
	const static int SPEED = 17;
	const static int SHOOT_SPEED = 1;
	static const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> image;
};


/* 重型坦克 */
class HeavyTank :public EnemyTank {
public:
	HeavyTank(int x, int y);
private:
	const static int HP = 3;
	const static int DAMAGE = 1;
	const static int SPEED = 13;
	const static int SHOOT_SPEED = 1;
};

/* 反坦克炮 */
class AntiTankGun :public EnemyTank {
public:
	AntiTankGun(int x, int y);
	const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> GetImage()override;
private:
	const static int HP = 1;
	const static int DAMAGE = 1;
	const static int SPEED = 8;
	const static int SHOOT_SPEED = 15;
	static const std::array<std::array<wchar_t, WIDTH_X>, WIDTH_Y> image;
};

