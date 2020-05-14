#include"datacompressor.h"
#include<cstdlib>
#include<string>
#include<iostream>
using namespace std;

DataCompressor d;

int main() {
	string src, name;
	cout << "please input the source directory" << endl;
	cin >> src;
	cout << "please input the filename to generate"<<endl;
	cin >> name;
	try {
		d.Generate(src, name);
	}
	catch (char const* c) {
		cout << c << endl;
	}
	system("pause");
	return 0;
}
