#include"dataaccessor.h"
#include<iostream>
#include<cstdlib>
using namespace std;


int main() {
	string path, name;
	cin >> path >> name;
	DataAccessor da(path, name);
	da.pr();
	cin >> name;
	try {
		da.Load(name);
	}
	catch (char const* c) {
		cout << c;
	}
	system("pause");
	return 0;
}
