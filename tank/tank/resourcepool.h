#pragma once
#include<map>
#include<memory>
#include"graphics.h"
#include"sound.h"
#include"dataaccess.h"
#include"resourceid.h"

#define GETBITMAP(resPool, id) (*(resPool).bmp[(id)])

#define GETSOUND(resPool, id) (*(resPool).sound[(id)])

#define DRAWBITMAP_R(resPool, id, left, top, right, bottom, angle) \
	((resPool).gf->DrawBitmap(GETBITMAP((resPool), (id)), left, top, right, bottom, angle))

#define DRAWBITMAP(resPool, id, left, top, right, bottom) \
	((resPool).gf->DrawBitmap(GETBITMAP((resPool), (id)), left, top, right, bottom))

#define PLAYMUSIC(resPool, id) \
	do{ \
		((Music*)((resPool).sound[(id)].get()))->active = true; \
		(resPool).sound[(id)]->Play(); \
	}while(0)

#define PLAYSOUND(resPool, id) ((resPool).sound[(id)]->Play())

struct ResourcePool {
	ResourcePool(GFactory&);
	void ResourceInit();
	void ResourceClear();

	GFactory *gf;
	std::shared_ptr<DataAccess> dao;
	std::map<ResourceID, std::shared_ptr<Bitmap>> bmp;
	std::map<ResourceID, std::shared_ptr<Sound>> sound;
};
