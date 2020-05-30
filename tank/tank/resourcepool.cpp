#include"resourcepool.h"
using namespace std;
ResourcePool::ResourcePool(GFactory& g) : gf(&g) {
	dao = make_shared<NormalDataAccess>();
	//dao = make_shared<CompressedDataAccess>(".\\", "src");
}

void ResourcePool::ResourceInit() {
	gf->Create();
	bmp[BID_PLAYERTANK] = make_shared<Bitmap>(dao->GetFile(".\\src\\p1tankU.gif"));
	bmp[BID_IRONWALL] = make_shared<Bitmap>(dao->GetFile(".\\src\\steel.gif"));
	bmp[BID_BRICKWALL] = make_shared<Bitmap>(dao->GetFile(".\\src\\walls.gif"));
	bmp[BID_WATERWALL] = make_shared<Bitmap>(dao->GetFile(".\\src\\water.gif"));
	bmp[BID_PLAYERBASE] = make_shared<Bitmap>(dao->GetFile(".\\src\\symbol.gif"));
	bmp[BID_PLAYERBULLET] = make_shared<Bitmap>(dao->GetFile(".\\src\\tankmissile.gif"));
	bmp[BID_ENENYBULLET] = make_shared<Bitmap>(dao->GetFile(".\\src\\enemymissile.gif"));

	bmp[BID_HEAVY_R] = make_shared<Bitmap>(dao->GetFile(".\\src\\heavyRed.png"));
	bmp[BID_HEAVY_G] = make_shared<Bitmap>(dao->GetFile(".\\src\\heavyGreen.png"));
	bmp[BID_HEAVY_B] = make_shared<Bitmap>(dao->GetFile(".\\src\\heavyBlue.png"));
	bmp[BID_LIGHT] = make_shared<Bitmap>(dao->GetFile(".\\src\\enemy1U.gif"));
	bmp[BID_ARMORED_G] = make_shared<Bitmap>(dao->GetFile(".\\src\\armoredGreen.png"));
	bmp[BID_ARMORED_B] = make_shared<Bitmap>(dao->GetFile(".\\src\\armoredBlue.png"));
	bmp[BID_ANTI] = make_shared<Bitmap>(dao->GetFile(".\\src\\anti.png"));

	//number images
	for (auto i = BID_NUM0; i <= BID_NUM9; i++) {
		string path;
		path += ".\\src\\" + to_string(i - BID_NUM0) + ".png";
		bmp[i] = make_shared<Bitmap>(dao->GetFile(path));
	}

	for (auto b : bmp) {
		b.second->Create();
		gf->CreateBitmap(*b.second);
	}
}

void ResourcePool::ResourceClear() {
	bmp.clear();
}
