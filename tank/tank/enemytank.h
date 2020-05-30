#pragma once
#include"tankbase.h"
#include<array>

/* 敌方坦克原型 */
class EnemyTank :public TankBase {
public:
	EnemyTank(int x, int y, int hp, int damage, int speed, int shootSpeed);
	void Update();
	void DrawTank();
	const static int WIDTH_X = 45;
	const static int WIDTH_Y = 45;
	virtual ResourceID GetImage();
protected:
	void GoStraight();
	int shootSpeed;	//0~29
private:
	ResourceID image;
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
	ResourceID GetImage()override;
private:
	const static int HP = 2;
	const static int DAMAGE = 1;
	const static int SPEED = 17;
	const static int SHOOT_SPEED = 1;
	ResourceID imageG;
	ResourceID imageB;
};


/* 重型坦克 */
class HeavyTank :public EnemyTank {
public:
	HeavyTank(int x, int y);
	ResourceID GetImage()override;
private:
	const static int HP = 3;
	const static int DAMAGE = 1;
	const static int SPEED = 13;
	const static int SHOOT_SPEED = 1;
	ResourceID imageR;
	ResourceID imageG;
	ResourceID imageB;
};

/* 反坦克炮 */
class AntiTankGun :public EnemyTank {
public:
	AntiTankGun(int x, int y);
	ResourceID GetImage()override;
private:
	const static int HP = 1;
	const static int DAMAGE = 1;
	const static int SPEED = 8;
	const static int SHOOT_SPEED = 15;
	ResourceID image;
};

