#include"resourcepool.h"
using namespace std;
ResourcePool::ResourcePool(GFactory& g) : gf(&g) {
	dao = make_shared<NormalDataAccess>();
	//dao = make_shared<CompressedDataAccess>(".\\", "src");
}

void ResourcePool::ResourceInit() {
	gf->Create();
	bmp.push_back(make_shared<Bitmap>(dao->GetFile(".\\src\\p1tankU.gif")));
	bmp.push_back(make_shared<Bitmap>(dao->GetFile(".\\src\\1.bmp")));
	for (auto b : bmp) {
		b->Create();
		gf->CreateBitmap(*b);
	}
}
