#include"menu.h"
#include"game.h"
using namespace std;

Menu::Menu() {
	buttons[B_EASY] = make_shared<Button>(30, 18, "EASY");
	buttons[B_NORMAL] = make_shared<Button>(30, 20, "NORMAL");
	buttons[B_HARD] = make_shared<Button>(30, 22, "HARD");
	buttons[B_EXIT] = make_shared<Button>(30, 24, "EXIT");
	for (int i = 0; i < BUTTON_NUM; i++)
		buf.Push(buttons[i]);
	nowActive = 0;
}

void Menu::Run() {
	SetFontSize(20);
	system("cls");
	DrawTitle({ 10,4 }, LOGO_PATH);
	while (Game::state == G_MENU) {
		for (int i = 0; i < BUTTON_NUM; i++)
			if (i == nowActive)buttons[i]->isActive = true;
			else buttons[i]->isActive = false;
		buf.Show();
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
