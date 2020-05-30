#pragma once
#include "gameobject.h"
#include "resourcepool.h"
#include<string>
#include<fstream>
#include<list>

/* 关卡类，自动内存管理 */
class Stage {
public:
	Stage(int no, Mode mode);
	void StageInit();
	Result Run();
	static ResourcePool* resPoolHdl;	//游戏资源池句柄，实现资源的获取
private:
	void LoadStage(int no);	//载入关卡
	void AddEnemy();
	std::shared_ptr<Number> score;
	std::shared_ptr<Number> playerNum;
	std::shared_ptr<Number> stageNum;
	std::list<COORD> enemyPoint;	//敌人的生成点
	COORD playerPoint;				//玩家的出生点
	Buffer buf;
	Mode mode;
};
