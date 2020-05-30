#include"sprite.h"
using namespace std;

Buffer* Sprite::bufferHdl = nullptr;
ResourcePool* Sprite::resPoolHdl = nullptr;

Sprite::Sprite(int x, int y, int _layer, SpriteType _type) {
	posCur.X = x;
	posCur.Y = y;
	layer = _layer;
	type = _type;
	del = false;
}

int Sprite::GetLayer()const {
	return layer;
}

SpriteType Sprite::GetType()const {
	return type;
}

COORD Sprite::GetPos()const {
	return posCur;
}

bool Sprite::IsDeleted()const {
	return del;
}

void Buffer::Show() {
	for (auto i = spriteList.begin(); i != spriteList.end(); i++)
		(*i)->Show();
}

void Buffer::Update() {
	for (auto i = spriteList.begin(); i != spriteList.end(); i++)
		(*i)->Update();
	spriteList.remove_if(
		[](shared_ptr<Sprite> x) -> bool {return x->IsDeleted(); }
	);
}

void Buffer::Push(shared_ptr<Sprite> s) {
	spriteList.push_back(s);
}

void Buffer::Sort() {
	spriteList.sort(
		[](shared_ptr<Sprite> &a, shared_ptr<Sprite> &b) {
		return a->GetLayer() > b->GetLayer();
	}
	);
}

int Buffer::Size()const {
	return spriteList.size();
}

shared_ptr<Sprite> Buffer::Any(function<bool(shared_ptr<Sprite>)> f) {
	for (auto i = spriteList.begin(); i != spriteList.end(); i++)
		if (f(*i))return *i;
	return nullptr;
}

void Buffer::Map(function<void(shared_ptr<Sprite>)> map,
	function<bool(shared_ptr<Sprite>)> cond) {
	for (auto i = spriteList.begin(); i != spriteList.end(); i++)
		if (cond(*i))map(*i);
}

bool IsTank(SpriteType t) {
	return t == S_ENEMY || t == S_PLAYER;
}

bool IsTank(shared_ptr<Sprite> s) {
	return IsTank(s->GetType());
}

bool IsBarrier(SpriteType t) {
	return t == S_DESTORYABLE || t == S_UNDESTORYABLE || t == S_ACCESSIBLE;
}

bool IsBarrier(shared_ptr<Sprite> s) {
	return IsBarrier(s->GetType());
}
