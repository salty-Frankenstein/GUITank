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

Game::Game(GFactory& g) : gf(&g) {
	dao = new NormalDataAccess();
	//dao = new CompressedDataAccess(".\\", "src");
}

Game::~Game() {
	delete dao;
}

void Game::ResourceInit() {
	gf->Create();

	bmpPool.push_back(make_shared<Bitmap>(dao->GetFile(".\\src\\p1tankU.gif")));
	for (auto bmp : bmpPool) {
		bmp->Create();
		gf->CreateBitmap(*bmp);
	}
	
}

shared_ptr<Bitmap> Game::GetBitmapHdl(ResourceID id) {
	assert(id < bmpPool.size() &&  id >= 0);
	return bmpPool[id];
}

void Game::Run() {
	system("cls");
	bool win = true;
	/* 游戏主流程状态机 */
	while (state != G_EXIT) {
		switch (state) {
		case G_MENU:
			menu.Run();
			break;
		case G_GAME:
			for (int stage = 1; stage <= MAX_STAGE; stage++) {
				stagePtr = make_shared<Stage>(stage, gameMode);
				if (!stagePtr->Run()) {
					win = false;
					break;
				}
			}
			if (win)state = G_WIN;
			else state = G_GAMEOVER;
			break;
		case G_GAMEOVER:
			SetFontSize(18);
			system("cls");
			DrawTitle({ 10,10 }, GAMEOVER_PATH);
			cout << "press any key to return" << endl;
			_getch();
			state = G_MENU;
			break;
		case G_WIN:
			SetFontSize(18);
			system("cls");
			DrawTitle({ 10,10 }, WIN_PATH);
			cout << "press any key to return" << endl;
			_getch();
			state = G_MENU;
			break;
		default:break;
		}
	}
}

GameTime Game::GetGameTime() {
	return gameTime;
}

void Game::AddGameTime() {
	gameTime++;
}
