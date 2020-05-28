#pragma once

#include<list>
#include<memory>
#include<functional>
#include <windows.h>
#include"resourcepool.h"
class Game;
class Buffer;

enum SpriteType {
	S_PLAYER,
	S_ENEMY,
	S_PLAYER_BULLET,
	S_ENEMY_BULLET,
	S_DESTORYABLE,
	S_UNDESTORYABLE,
	S_ACCESSIBLE,
	S_PLAYER_BASE,
	S_OTHER
};

/* 游戏对象的基类 */
class Sprite {
public:
	Sprite(int x = 0, int y = 0, int layer = 0, SpriteType type = S_OTHER);
	virtual void Update() = 0;	//更新方法，每帧调用一次
	virtual void Show() = 0;	//显示方法，每帧调用一次
	virtual void Delete() = 0;	//删除方法，游戏对象消亡时调用
	int GetLayer()const;
	SpriteType GetType()const;
	COORD GetPos()const;
	bool IsDeleted()const;
	static Buffer* bufferHdl;	//游戏对象池句柄，实现与其它对象的消息传递
	static ResourcePool* resPoolHdl;//游戏资源池句柄，实现资源的获取
protected:
	bool del;
	int layer;
	COORD posCur;
	SpriteType type;
};

/* 游戏对象缓存，对游戏对象统一管理 */
class Buffer {
public:
	void Update();	//更新buffer中所有对象
	void Show();	//显示buffer中所有对象
	void Push(std::shared_ptr<Sprite> s);
	void Sort();	//按游戏对象图层排序
	int Size()const;
	/* Any: 传入条件函数，如果buffer中存在元素满足，返回指针，否则返回nullptr */
	std::shared_ptr<Sprite> Any(std::function<bool(std::shared_ptr<Sprite>)>);
	/* Map: 功能同函数式对列表的map */
	void Map(std::function<void(std::shared_ptr<Sprite>)> map,
		std::function<bool(std::shared_ptr<Sprite>)> cond =
		[](std::shared_ptr<Sprite>) {return true; }
	);
private:
	std::list<std::shared_ptr<Sprite>> spriteList;
};

bool IsTank(SpriteType t);
bool IsTank(std::shared_ptr<Sprite> s);
bool IsBarrier(SpriteType t);
bool IsBarrier(std::shared_ptr<Sprite> s);

