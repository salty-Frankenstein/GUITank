﻿#pragma once
#ifndef GAME_H
#define GAME_H

#include "gameobject.h"
#include "stage.h"
#include "menu.h"
#include"resourcepool.h"
#include <vector>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef unsigned long long GameTime;

enum GameState { G_MENU, G_GAME, G_HISCORE, G_GAMEOVER, G_WIN, G_EXIT };

/* 游戏主流程控制 */
class Game {
public:
	Game(GFactory&);
	bool Run();
	void ResourceInit();

	static GameTime GetGameTime();
	static void AddGameTime();

	/* 游戏逻辑全局量 */
	static Mode gameMode;
	static int player;
	static int enemyNow;
	static int enemyMax;
	static int enemyKill;
	static bool playerAlive;
	static GameState state;
	static const int MAX_STAGE = 5;
	static int stageNow;
	/* 游戏资源池 */
	ResourcePool resPool;
	GFactory* GetGFHdl();
	void ClearFile();

private:
	std::shared_ptr<Stage> stagePtr;
	Menu menu;
	static GameTime gameTime;
	Result GameProc();
};

#endif 
