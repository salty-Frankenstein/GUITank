#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <cassert>
using namespace std;

Mode Game::gameMode = M_EASY;
GameTime Game::gameTime = 0;
int Game::player = 0;
int Game::enemyMax = 0;
int Game::enemyNow = 0;
int Game::enemyKill = 0;
bool Game::playerAlive = true;
GameState Game::state = G_MENU;
int Game::stageNow = 1;

Game::Game(GFactory& g) : resPool(g) {
	Sprite::resPoolHdl = &resPool;
	Stage::resPoolHdl = &resPool;
	Menu::resPoolHdl = &resPool;
	// TODO
	
}

void Game::ResourceInit() {
	resPool.ResourceInit();
	Game::state = G_MENU;
}

bool Game::Run() {
	gameTime++;
	bool win = true;
	if (state != G_EXIT) {
		switch (state)
		{
		case G_MENU:
			menu.Run();
			break;
		case G_GAME:
			switch (GameProc()) {
			case R_LOSE:state = G_GAMEOVER; break;
			case R_WIN:state = G_WIN; break;
			case R_CONTINUE:break;
			}
			break;
		case G_HISCORE:
			break;
		case G_GAMEOVER:
			DRAWBITMAP(resPool, BID_GAMEOVER, 0, 0, 960, 720);
			if (getKey[VK_ESCAPE]) state = G_MENU;
			break;
		case G_WIN:
			DRAWBITMAP(resPool, BID_GAMEOVER, 0, 0, 960, 720);
			if (getKey[VK_ESCAPE]) state = G_MENU;
			break;
		default:
			break;
		}

		return true;
	}
	return false;
}

Result Game::GameProc() {
	static bool loadStage = true;
	if (loadStage) {
		stagePtr = make_shared<Stage>(stageNow, gameMode);
		stagePtr->StageInit();
		loadStage = false;
	}
	
	switch (stagePtr->Run()) {
	case R_LOSE:
		return R_LOSE;
	case R_CONTINUE:
		return R_CONTINUE;
	case R_WIN:
		if (stageNow == MAX_STAGE)
			return R_WIN;
		stageNow++;
		loadStage = true;
		break;
	}
	return R_CONTINUE;
}

GameTime Game::GetGameTime() {
	return gameTime;
}

void Game::AddGameTime() {
	gameTime++;
}

GFactory* Game::GetGFHdl() {
	return resPool.gf;
}

void Game::ClearFile() {
	resPool.ResourceClear();
	resPool.dao->ClearFile();
}
