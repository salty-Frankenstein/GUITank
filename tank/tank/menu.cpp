#include"menu.h"
#include"game.h"
using namespace std;

ResourcePool* Menu::resPoolHdl = nullptr;
ResourceID Menu::cover = BID_COVER;

Menu::Menu() {
	buttons[B_EASY] = make_shared<Button>(380, 380, 150, 50, BID_EASY1, BID_EASY0);
	buttons[B_NORMAL] = make_shared<Button>(380, 440, 200, 50, BID_NORMAL1, BID_NORMAL0);
	buttons[B_HARD] = make_shared<Button>(380, 500, 150, 50, BID_HARD1, BID_HARD0);
	buttons[B_EXIT] = make_shared<Button>(380, 560, 150, 50, BID_EXIT1, BID_EXIT0);
	for (int i = 0; i < BUTTON_NUM; i++)
		buf.Push(buttons[i]);
	nowActive = 0;
}

void Menu::Run() {
	DRAWBITMAP(*resPoolHdl, cover, 0, 0, 960, 720);

	static GameTime keyDownTime = 0;

	if (Game::state == G_MENU) {
		for (int i = 0; i < BUTTON_NUM; i++)
			if (i == nowActive)buttons[i]->isActive = true;
			else buttons[i]->isActive = false;
		buf.Show();

		if (!(getKey[VK_UP] || getKey[VK_DOWN] || getKey['Z']))keyDownTime = Game::GetGameTime();
		if ((Game::GetGameTime() - keyDownTime) % 10 == 1) {
			if (getKey[VK_UP])
				nowActive = (nowActive + BUTTON_NUM - 1) % BUTTON_NUM;
			if (getKey[VK_DOWN])
				nowActive = (nowActive + 1) % BUTTON_NUM;
			if (getKey['Z']) {
				switch (MenuButton(nowActive)) {
				case B_EASY:Game::gameMode = M_EASY; Game::state = G_GAME; break;
				case B_NORMAL:Game::gameMode = M_NORMAL; Game::state = G_GAME; break;
				case B_HARD:Game::gameMode = M_HARD; Game::state = G_GAME; break;
				case B_EXIT:Game::state = G_EXIT; break;
				}
			}
		}
		return;
		//TODO
		if (_kbhit()) {
			switch (_getch()) {
			case 72:nowActive = (nowActive + BUTTON_NUM - 1) % BUTTON_NUM; break;
			case 80:nowActive = (nowActive + 1) % BUTTON_NUM; break;
			case 'z':
				switch (MenuButton(nowActive)) {
				case B_EASY:Game::gameMode = M_EASY; Game::state = G_GAME; break;
				case B_NORMAL:Game::gameMode = M_NORMAL; Game::state = G_GAME; break;
				case B_HARD:Game::gameMode = M_HARD; Game::state = G_GAME; break;
				case B_EXIT:Game::state = G_EXIT; break;
				}
				break;
			default: break;
			}
		}
	}
}
