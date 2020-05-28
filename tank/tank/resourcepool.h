#pragma once
#include<vector>
#include<memory>
#include"graphics.h"
#include"dataaccess.h"

#define GETBITMAP(resPool, id) (*(resPool).bmp[id])

struct ResourcePool {
	ResourcePool(GFactory&);
	void ResourceInit();

	GFactory *gf;
	std::shared_ptr<DataAccess> dao;
	std::vector<std::shared_ptr<Bitmap>> bmp;
};
