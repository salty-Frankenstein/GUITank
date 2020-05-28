#pragma once
#include<map>
#include<memory>
#include"graphics.h"
#include"dataaccess.h"
#include"resourceid.h"

#define GETBITMAP(resPool, id) (*(resPool).bmp[(id)])
#define DRAWBITMAP_R(resPool, id, left, top, right, bottom, angle) \
	((resPool).gf->DrawBitmap(GETBITMAP((resPool), (id)), left, top, right, bottom, angle))
#define DRAWBITMAP(resPool, id, left, top, right, bottom) \
	((resPool).gf->DrawBitmap(GETBITMAP((resPool), (id)), left, top, right, bottom))

struct ResourcePool {
	ResourcePool(GFactory&);
	void ResourceInit();
	void ResourceClear();

	GFactory *gf;
	std::shared_ptr<DataAccess> dao;
	std::map<ResourceID, std::shared_ptr<Bitmap>> bmp;
};
