#include"number.h"
using namespace std;

const wchar_t Number::image[10][6][4] = {
	{
		{ L'　',L'█',L'　' },
		{ L'█',L'　',L'█' },
		{ L'█',L'　',L'█' },
		{ L'█',L'　',L'█' },
		{ L'　',L'█',L'　' },
	},
	{
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
	},
	{
		{ L'█',L'█',L'　' },
		{ L'　',L'　',L'█' },
		{ L'█',L'█',L'█' },
		{ L'█',L'　',L'　' },
		{ L'　',L'█',L'█' },
	},
	{
		{ L'█',L'█',L'　' },
		{ L'　',L'　',L'█' },
		{ L'█',L'█',L'█' },
		{ L'　',L'　',L'█' },
		{ L'█',L'█',L'　' },
	},
	{
		{ L'█',L'　',L'█' },
		{ L'█',L'　',L'█' },
		{ L'█',L'█',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
	},
	{
		{ L'█',L'█',L'█' },
		{ L'█',L'　',L'　' },
		{ L'█',L'█',L'█' },
		{ L'　',L'　',L'█' },
		{ L'█',L'█',L'　' },
	},
	{
		{ L'　',L'█',L'█' },
		{ L'█',L'　',L'　' },
		{ L'█',L'█',L'█' },
		{ L'█',L'　',L'█' },
		{ L'　',L'█',L'　' },
	},
	{
		{ L'█',L'█',L'　' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
		{ L'　',L'　',L'█' },
	},
	{
		{ L'　',L'█',L'　' },
		{ L'█',L'　',L'█' },
		{ L'█',L'█',L'█' },
		{ L'█',L'　',L'█' },
		{ L'　',L'█',L'　' },
	},
	{
		{ L'　',L'█',L'　' },
		{ L'█',L'　',L'█' },
		{ L'█',L'█',L'█' },
		{ L'　',L'　',L'█' },
		{ L'█',L'█',L'　' },
	},
};

Number::Number(int x, int y, int length)
	:Sprite(x, y), LENGTH(length) {
	numberNow = 0;
	numberSet = 0;
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
	auto pos = posCur;
	
	for (int i = 0; i < 5; i++) {
		SetConsoleCursorPosition(GetStdOHdl(), pos);
		for (int j = 0; s[j] != '\0'; j++) {
			for (int k = 0; k < 3; k++)
				wcout << image[s[j] - '0'][i][k];
			wcout << L'　';
		}
		pos.Y++;
	}
}
