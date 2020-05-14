#include"dataaccessor.h"
#include<fstream>
#include<iostream>
#include<Windows.h>
using namespace std;

DataAccessor::DataAccessor(string _path, string name)
	: path(_path + "\\" + name) {
	ifstream fin(path + ".txt");
	if (!fin.is_open())throw "path error";
	string filename;
	int bytenum, prefix = 0;
	while (1) {
		fin >> filename >> bytenum;
		if (fin.eof())break;
		fileMap[filename] = { prefix,bytenum };
		prefix += bytenum;
	}
	fin.close();
}

void DataAccessor::Load(string name) {
	auto fileCur = fileMap.find(name);
	if (fileCur == fileMap.end())
		throw "no such file in data";

	ifstream fin(path + ".dat", ios::binary);
	ofstream fout(GetLastPath(name), ios::binary);
	if (!fin.is_open())throw "path error";

	auto fileInfo = fileCur->second;
	fin.seekg(fileInfo.first, ios::beg);
	char buf[200];
	int cnt = 0;
	while (fileInfo.second > cnt + 200) {
		fin.read(buf, sizeof(buf));
		fout.write(buf, sizeof(buf));
		cnt += 200;
	}
	fin.read(buf, fileInfo.second - cnt);
	fout.write(buf, fileInfo.second - cnt);
	fin.close();
	fout.close();
	fileList.push_back(GetLastPath(name));
}

void DataAccessor::pr() {
	for (auto i : fileMap) {
		cout << i.first << ' ' << i.second.first << ' ' << i.second.second << endl;
	}
}

string DataAccessor::GetLastPath(const string& p) {
	int l = p.length();
	for (int i = l - 1; i >= 0; i--) {
		if (p[i] == '\\')
			return p.substr(i + 1, l - i - 1);
	}
	return p;
}

void DataAccessor::Clear() {
	for (auto file : fileList) {
		DeleteFile(file.c_str());
	}
	fileList.clear();
}
