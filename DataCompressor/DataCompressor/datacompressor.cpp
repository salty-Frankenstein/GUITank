#define _CRT_SECURE_NO_WARNINGS
#include"datacompressor.h"
#include<io.h>
#include<iostream>
#include<cstring>
using namespace std;

void DataCompressor::Generate(string dir, string name) {
	fileList.open(name + ".txt");
	fileData.open(name + ".dat", ios::binary);
	GetDirectory(dir.c_str());
	fileList.close();
	fileData.close();
}

void DataCompressor::GetDirectory(const char* dir, string dirnow) {
	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dirNew, &findData);
	if (handle == -1) {
		cout << "Failed to find file" << endl;
		return;
	}

	do {
		if (findData.attrib & _A_SUBDIR) {
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
			cout << "now processing: " << findData.name << "\t" << endl;
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);
			GetDirectory(dirNew, dirnow + "\\" + findData.name);
		}
		else {
			fileList << dirnow << "\\" << findData.name << ' ' << findData.size << endl;
			WriteData(string(dir) + "\\" + findData.name, findData.size);
		}
		
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);
}

void DataCompressor::WriteData(string name, int size) {
	ifstream fin(name, ios::binary);
	if (!fin.is_open())throw "file access error";
	char buf[200];
	int cnt = 0;
	while (size > cnt + 200) {
		fin.read(buf, sizeof(buf));
		fileData.write(buf, sizeof(buf));
		cnt += 200;
	}
	fin.read(buf, size - cnt);
	fileData.write(buf, size - cnt);
	fin.close();
}
