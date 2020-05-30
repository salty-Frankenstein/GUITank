#include"number.h"
using namespace std;

Number::Number(int x, int y, int length, double _size)
	:Sprite(x, y), LENGTH(length) {
	numberNow = 0;
	numberSet = 0;
	size = _size;
	for (auto i = BID_NUM0; i <= BID_NUM9; i++)
		image[i - BID_NUM0] = i;
}

void Number::SetNumber(int x) {
	numberSet = x;
}

void Number::Delete() {}

void Number::Update() {
	/* 数字滚动效果 */
	numberNow = 0.5 * (numberNow + numberSet);
	if (numberNow < numberSet)numberNow++;
	else if (numberNow > numberSet)numberNow--;
}

void Number::Show() {
	string s = to_string(numberNow);
	while (s.length() < LENGTH)
		s = '0' + s;
	for (int i = 0; i < s.length(); i++) {
		DRAWBITMAP(*resPoolHdl, image[s[i] - '0'],
			posCur.X + i * (30*size), posCur.Y, posCur.X + (i + 1) * (30*size), posCur.Y + (37*size));
	}
}
