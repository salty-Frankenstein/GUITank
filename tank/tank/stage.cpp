#include"stage.h"
#include"game.h"
#include<cassert>
using namespace std;

ResourcePool* Stage::resPoolHdl = nullptr;

Stage::Stage(int no, Mode _mode) {
	Sprite::bufferHdl = &buf;
	
	stageNum = make_shared<Number>((GRID_X + 11) * BARRIER_WIDTH, 2 * BARRIER_WIDTH, 2);
	stageNum->SetNumber(no);
	score = make_shared<Number>((GRID_X + 11) * BARRIER_WIDTH, 10 * BARRIER_WIDTH, 2);
	playerNum = make_shared<Number>((GRID_X + 11) * BARRIER_WIDTH, 18 * BARRIER_WIDTH, 2);
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

void Stage::StageInit() {
	shared_ptr<Background> bg = make_shared<Background>();
	bg->Draw();
	buf.Push(bg);
}

bool Stage::Run() {
	if (Game::state == G_GAME) {
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
		Game::AddGameTime();
	}
	return false;
}

void Stage::LoadStage(int no) {	//读取关卡文件
	string file = ".\\res\\stage\\" + to_string(no) + ".txt";
	assert(resPoolHdl != nullptr);
	assert(resPoolHdl->dao != nullptr);
	ifstream fin(resPoolHdl->dao->GetFile(file));
	assert(fin.is_open());
	fin >> Game::enemyMax;
	string s;
	do {
		getline(fin, s);
	} while (s[0] != '$');
	for (SHORT i = 1; i <= GRID_Y - 2; i++) {
		getline(fin, s);
		for (SHORT j = 1; j <= GRID_X - 2; j++) {
			switch (s[j]) {	//在对象池添加相应对象
			case '#':buf.Push(make_shared<BrickWall>(j * BARRIER_WIDTH, i * BARRIER_WIDTH)); break;
			case '=':buf.Push(make_shared<IronWall>(j * BARRIER_WIDTH, i * BARRIER_WIDTH)); break;
			case '~':buf.Push(make_shared<WaterWall>(j * BARRIER_WIDTH, i * BARRIER_WIDTH)); break;
			case 'P':playerPoint = { j * BARRIER_WIDTH, i * BARRIER_WIDTH }; break;
			case 'E':enemyPoint.push_back({ j * BARRIER_WIDTH, i * BARRIER_WIDTH }); break;
			//case 'B':buf.Push(make_shared<PlayerBase>(j * BARRIER_WIDTH, i * BARRIER_WIDTH)); break;
			default:break;
			}
		}
	}
}

void Stage::AddEnemy() {
	static RandomInt randomInt;
	for (auto i = enemyPoint.begin(); i != enemyPoint.end(); i++) {
		/* 判断还有敌人没有生成，且生成点上没有其他对象 */
		if (Game::enemyMax - Game::enemyNow > 0 
			&& Game::GetGameTime() % 10 == 0 && randomInt(1, mode) == 1
			&& buf.Any([=](shared_ptr<Sprite> s) { 
				return IsTank(s) && IsHit(*i, TANK_WIDTH, TANK_WIDTH, 
					s->GetPos(), TANK_WIDTH, TANK_WIDTH); }) == nullptr) 
		{
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
