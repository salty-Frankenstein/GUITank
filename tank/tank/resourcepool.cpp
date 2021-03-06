#include"resourcepool.h"
#include"common.h"
using namespace std;

ResourcePool::ResourcePool(GFactory& g) : gf(&g) {
	//dao = make_shared<NormalDataAccess>();
	dao = make_shared<CompressedDataAccess>(".\\", "res");
}

void ResourcePool::ResourceInit() {
	gf->Create();

	/* Bitmap resources */
	bmp[BID_PLAYERTANK] = make_shared<Bitmap>(dao->GetFile(".\\res\\p1tankU.gif"));
	bmp[BID_IRONWALL] = make_shared<Bitmap>(dao->GetFile(".\\res\\steel.gif"));
	bmp[BID_BRICKWALL] = make_shared<Bitmap>(dao->GetFile(".\\res\\walls.gif"));
	bmp[BID_WATERWALL] = make_shared<Bitmap>(dao->GetFile(".\\res\\water.gif"));
	bmp[BID_PLAYERBASE] = make_shared<Bitmap>(dao->GetFile(".\\res\\symbol.gif"));
	bmp[BID_PLAYERBULLET] = make_shared<Bitmap>(dao->GetFile(".\\res\\tankmissile.gif"));
	bmp[BID_ENENYBULLET] = make_shared<Bitmap>(dao->GetFile(".\\res\\enemymissile.gif"));

	bmp[BID_HEAVY_R] = make_shared<Bitmap>(dao->GetFile(".\\res\\heavyRed.png"));
	bmp[BID_HEAVY_G] = make_shared<Bitmap>(dao->GetFile(".\\res\\heavyGreen.png"));
	bmp[BID_HEAVY_B] = make_shared<Bitmap>(dao->GetFile(".\\res\\heavyBlue.png"));
	bmp[BID_LIGHT] = make_shared<Bitmap>(dao->GetFile(".\\res\\enemy1U.gif"));
	bmp[BID_ARMORED_G] = make_shared<Bitmap>(dao->GetFile(".\\res\\armoredGreen.png"));
	bmp[BID_ARMORED_B] = make_shared<Bitmap>(dao->GetFile(".\\res\\armoredBlue.png"));
	bmp[BID_ANTI] = make_shared<Bitmap>(dao->GetFile(".\\res\\anti.png"));
	bmp[BID_BACKGROUND] = make_shared<Bitmap>(dao->GetFile(".\\res\\bg.png"));
	bmp[BID_COVER] = make_shared<Bitmap>(dao->GetFile(".\\res\\cover.png"));

	bmp[BID_BUSH] = make_shared<Bitmap>(dao->GetFile(".\\res\\grass.png"));

	//buttons
	bmp[BID_EASY0] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\easy0.png"));
	bmp[BID_EASY1] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\easy1.png"));
	bmp[BID_NORMAL0] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\normal0.png"));
	bmp[BID_NORMAL1] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\normal1.png"));
	bmp[BID_HARD0] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\hard0.png"));
	bmp[BID_HARD1] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\hard1.png"));
	bmp[BID_EXIT0] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\exit0.png"));
	bmp[BID_EXIT1] = make_shared<Bitmap>(dao->GetFile(".\\res\\button\\exit1.png"));

	bmp[BID_GAMEOVER] = make_shared<Bitmap>(dao->GetFile(".\\res\\gameover.png"));
	bmp[BID_WIN] = make_shared<Bitmap>(dao->GetFile(".\\res\\win.png"));

	//number images
	for (auto i = BID_NUM0; i <= BID_NUM9; i++) {
		string path;
		path += ".\\res\\font\\" + to_string(i - BID_NUM0) + ".png";
		bmp[i] = make_shared<Bitmap>(dao->GetFile(path));
	}

	for (auto b : bmp) {
		b.second->Create();
		gf->CreateBitmap(*b.second);
	}

	/* sound resources */
	sound[SID_START] = make_shared<Music>(dao->GetFile(".\\res\\se\\start.wav"));
	sound[SID_FIRE] = make_shared<Sound>(dao->GetFile(".\\res\\se\\fire.wav"));
	sound[SID_BLAST] = make_shared<Sound>(dao->GetFile(".\\res\\se\\blast.wav"));
}

void ResourcePool::ResourceClear() {
	bmp.clear();
}
