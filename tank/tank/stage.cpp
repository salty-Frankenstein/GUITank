#include"stage.h"
#include"game.h"
using namespace std;

Stage::Stage(int no, Mode _mode) {
	Sprite::bufferHdl = &buf;
	stageNum = make_shared<Number>((GRID_X + 11) * 2, 2, 2);
	stageNum->SetNumber(no);
	score = make_shared<Number>((GRID_X + 11) * 2, 10, 2);
	playerNum = make_shared<Number>((GRID_X + 11) * 2, 18, 2);
	buf.Push(stageNum);
	buf.Push(score);
	buf.Push(playerNum);
	Game::playerAlive = false;
	Game::player = 5;
	Game::enemyNow = 0;
	Game::enemyMax = 0;
	Game::enemyKill = 0;
	LoadStage(no);
	mode = _mode;
}

bool Stage::Run() {
	//SetFontSize(14);
	//system("cls");
	shared_ptr<Background> bg = make_shared<Background>();
	bg->Draw();
	buf.Push(bg);

	while (Game::state == G_GAME) {
		score->SetNumber(Game::enemyMax - Game::enemyKill);
		playerNum->SetNumber(Game::player);
		/* 玩家重生 */
		if (!Game::playerAlive) {
			buf.Push(make_shared<PlayerTank>(playerPoint.X, playerPoint.Y));
			Game::playerAlive = true;
		}
		AddEnemy();	//刷新敌人
		buf.Sort();
		buf.Show();
		buf.Update();

		if (Game::player == 0) {
			return false;
		}
		if (Game::enemyMax == Game::enemyKill)
			return true;
		Sleep(20);
		Game::AddGameTime();
	}
	return false;
}

void Stage::LoadStage(int no) {	//读取关卡文件
	string file = "./stage/" + to_string(no) + ".txt";
	ifstream fin(file);
	fin >> Game::enemyMax;
	string s;
	do {
		getline(fin, s);
	} while (s[0] != '$');
	for (SHORT i = 1; i <= GRID_Y-2; i++) {
		getline(fin, s);
		for (SHORT j = 1; j <= GRID_X - 2; j++) {
			switch (s[j]) {	//在对象池添加相应对象
			case '#':buf.Push(make_shared<BrickWall>(2 * j, i)); break;
			case '=':buf.Push(make_shared<IronWall>(2 * j, i)); break;
			case '~':buf.Push(make_shared<WaterWall>(2 * j, i)); break;
			case 'P':playerPoint = { 2 * j, i }; break;
			case 'E':enemyPoint.push_back({ 2 * j, i }); break;
			case 'B':buf.Push(make_shared<PlayerBase>(2 * j, i)); break;
			default:break;
			}
		}
	}
}

void Stage::AddEnemy() {
	static RandomInt randomInt;
	for (auto i = enemyPoint.begin(); i != enemyPoint.end(); i++) {
		/* 判断还有敌人没有生成，且生成点上没有其他对象 */
		if (Game::enemyMax - Game::enemyNow > 0 && Game::GetGameTime() % 10 == 0 && randomInt(1, mode) == 1
			&& buf.Any([=](shared_ptr<Sprite> s) { return IsTank(s) && IsHit(*i, 3, 3, s->GetPos(), 3, 3); }) == nullptr) {
			switch (randomInt(1,4)) {
			case 1:buf.Push(make_shared<LightTank>(i->X, i->Y)); break;
			case 2:buf.Push(make_shared<ArmoredCar>(i->X, i->Y)); break;
			case 3:buf.Push(make_shared<HeavyTank>(i->X, i->Y)); break;
			case 4:buf.Push(make_shared<AntiTankGun>(i->X, i->Y)); break;
			}
			Game::enemyNow++;
		}
	}
}
