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

	//bmp.push_back(make_shared<Bitmap>(dao->GetFile(".\\src\\1.bmp")));
	for (auto b : bmp) {
		b.second->Create();
		gf->CreateBitmap(*b.second);
	}
}

void ResourcePool::ResourceClear() {
	bmp.clear();
}
