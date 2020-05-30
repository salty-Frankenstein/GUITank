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

// TODO
//Buffer testBuf;
//shared_ptr<Number> testnum = make_shared<Number>(200, 200, 5, 0.8);
//Background bg;

Game::Game(GFactory& g) : resPool(g) {
	Sprite::resPoolHdl = &resPool;
	Stage::resPoolHdl = &resPool;
	Menu::resPoolHdl = &resPool;
	// TODO
	
}

void Game::ResourceInit() {
	resPool.ResourceInit();
	//stg = make_shared<Stage>(4, M_EASY);
	//stg->StageInit();
	Game::state = G_MENU;
	//Sprite::bufferHdl = &testBuf;
	/*
	testBuf.Push(make_shared<PlayerTank>(15, 15));
	testBuf.Push(make_shared<BrickWall>(100, 100));
	testBuf.Push(make_shared<WaterWall>(125, 125));
	testBuf.Push(make_shared<HeavyTank>(150, 150));
	testBuf.Push(make_shared<LightTank>(200, 150));
	testBuf.Push(make_shared<ArmoredCar>(250, 150));
	testBuf.Push(make_shared<AntiTankGun>(300, 150));
	testBuf.Push(testnum);
	*/
	//bg.Draw();
	//testBuf.Push(make_shared<Bullet>(S_PLAYER_BULLET, 100, 100, D_RIGHT));
}

/*
shared_ptr<Bitmap> Game::GetBitmapHdl(ResourceID id) {
	assert(id < resPool.bmp.size() &&  id >= 0);
	return resPool.bmp[id];
}
*/

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
	//stg->Run();
	//menu.Run();
	//((Music*)(resPool.sound[SID_START].get()))->active = true;
	//resPool.sound[SID_START]->Play();
	//testnum->SetNumber(Game::gameTime);
	//testBuf.Update();
	//testBuf.Show();
}

Result Game::GameProc() {
	static bool loadStage = true;
	if (loadStage) {
		stagePtr = make_shared<Stage>(stageNow, gameMode);
		stagePtr->StageInit();
		//assert(false);
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
