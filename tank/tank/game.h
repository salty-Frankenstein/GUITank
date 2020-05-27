#pragma once
#include "gameobject.h"
#include "stage.h"
#include "menu.h"
#include "graphics.h"
#include"dataaccess.h"
#include <vector>

#define GETBITMAP(game, id) (*game.GetBitmapHdl(id))

typedef unsigned long long GameTime;

enum GameState { G_MENU, G_GAME, G_HISCORE, G_GAMEOVER, G_WIN, G_EXIT };

/* 游戏主流程控制 */
class Game {
public:
	Game(GFactory&);
	~Game();
	void Run();
	void ResourceInit();
	std::shared_ptr<Bitmap> GetBitmapHdl(ResourceID id);

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

	/* 游戏资源池 */
	GFactory *gf;
	DataAccess* dao;
	std::vector<std::shared_ptr<Bitmap>> bmpPool;
private:
	std::shared_ptr<Stage> stagePtr;
	Menu menu;
	static GameTime gameTime;
};
