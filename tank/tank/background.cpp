#include"background.h"
using namespace std;

void Background::Show() {}

void Background::Update() {}

void Background::Delete() {}

void Background::Draw() {
	//COORD pos{ 0, 1 };

	/* 边框 */
	for (int i = 0; i < GRID_X; i++) {
		bufferHdl->Push(make_shared<IronWall>(i * BARRIER_WIDTH, 0));
		bufferHdl->Push(make_shared<IronWall>(i * BARRIER_WIDTH, (GRID_Y-1) * BARRIER_WIDTH));
	}

	for (int i = 1; i <= GRID_Y - 2; i++) {
		bufferHdl->Push(make_shared<IronWall>(0, i * BARRIER_WIDTH));
		bufferHdl->Push(make_shared<IronWall>((GRID_X - 1) * BARRIER_WIDTH, i * BARRIER_WIDTH));
	}

	/*
	SetConsoleTextAttribute(GetStdOHdl(), FOREGROUND_RED);
	pos.X = (GRID_X + 4) * 2;
	pos.Y = 10;
	SetConsolePosition(pos);
	for (int i = 0; i < 5; i++) {
		SetConsolePosition(pos);
		for (int j = 0; j < 5; j++)
			wcout << enemy[i][j];
		pos.Y++;
	}

	SetConsoleTextAttribute(GetStdOHdl(), 14);
	pos.X = (GRID_X + 4) * 2;
	pos.Y = 18;
	SetConsolePosition(pos);
	for (int i = 0; i < 5; i++) {
		SetConsolePosition(pos);
		for (int j = 0; j < 5; j++)
			wcout << player[i][j];
		pos.Y++;
	}

	SetConsoleTextAttribute(GetStdOHdl(), 7);
	pos.X = (GRID_X + 1) * 2;
	pos.Y = GRID_Y - 14;
	DrawTitle(pos, LOGO_PATH);
	*/
}
