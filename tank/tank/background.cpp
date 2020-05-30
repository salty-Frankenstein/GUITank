#include"background.h"
using namespace std;

ResourceID Background::image = BID_BACKGROUND;

Background::Background()
	: Sprite(0, 0, BACKGROUND_LAYER) {}

void Background::Show() {
	DRAWBITMAP(*resPoolHdl, image, 0, 0, 960, 720);
}

void Background::Update() {}

void Background::Delete() {}

void Background::Draw() {
	/* 边框 */
	for (int i = 0; i < GRID_X; i++) {
		bufferHdl->Push(make_shared<IronWall>(i * BARRIER_WIDTH, 0));
		bufferHdl->Push(make_shared<IronWall>(i * BARRIER_WIDTH, (GRID_Y-1) * BARRIER_WIDTH));
	}

	for (int i = 1; i <= GRID_Y - 2; i++) {
		bufferHdl->Push(make_shared<IronWall>(0, i * BARRIER_WIDTH));
		bufferHdl->Push(make_shared<IronWall>((GRID_X - 1) * BARRIER_WIDTH, i * BARRIER_WIDTH));
	}
}
