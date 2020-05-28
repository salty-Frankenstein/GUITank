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

/* ��Ϸ����Ļ��� */
class Sprite {
public:
	Sprite(int x = 0, int y = 0, int layer = 0, SpriteType type = S_OTHER);
	virtual void Update() = 0;	//���·�����ÿ֡����һ��
	virtual void Show() = 0;	//��ʾ������ÿ֡����һ��
	virtual void Delete() = 0;	//ɾ����������Ϸ��������ʱ����
	int GetLayer()const;
	SpriteType GetType()const;
	COORD GetPos()const;
	bool IsDeleted()const;
	static Buffer* bufferHdl;	//��Ϸ����ؾ����ʵ���������������Ϣ����
	static ResourcePool* resPoolHdl;//��Ϸ��Դ�ؾ����ʵ����Դ�Ļ�ȡ
protected:
	bool del;
	int layer;
	COORD posCur;
	SpriteType type;
};

/* ��Ϸ���󻺴棬����Ϸ����ͳһ���� */
class Buffer {
public:
	void Update();	//����buffer�����ж���
	void Show();	//��ʾbuffer�����ж���
	void Push(std::shared_ptr<Sprite> s);
	void Sort();	//����Ϸ����ͼ������
	int Size()const;
	/* Any: �����������������buffer�д���Ԫ�����㣬����ָ�룬���򷵻�nullptr */
	std::shared_ptr<Sprite> Any(std::function<bool(std::shared_ptr<Sprite>)>);
	/* Map: ����ͬ����ʽ���б��map */
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

