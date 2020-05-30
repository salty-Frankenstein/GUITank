#pragma once
#include"sprite.h"
#include"common.h"
#include<iostream>

const int BARRIER_LAYER = 5;
const int BARRIER_WIDTH = 15;

/* 障碍物基类 */
class Barrier :public Sprite {
public:
	Barrier(int x, int y, SpriteType type, ResourceID id);
	virtual void Show();
	void Update();
	void Delete();
protected:
	ResourceID image;
};

/* 铁墙 */
class IronWall :public Barrier {
public:
	IronWall(int x, int y);
	//void Show();
};

/* 砖墙 */
class BrickWall :public Barrier {
public:
	BrickWall(int x, int y);
	//void Show();
};

/* 水域 */
class WaterWall :public Barrier {
public:
	WaterWall(int x, int y);
	//void Show();
};

/* 玩家的基地 */
class PlayerBase :public Barrier {
public:
	PlayerBase(int x, int y);
	void Show();
	void Delete()override;
};
