#pragma once
#include<fstream>
#include<string>

class DataCompressor {
public:
	void Generate(std::string dir, std::string name);
	
private:
	void GetDirectory(const char* dir, std::string dirnow = ".");
	void WriteData(std::string name, int size);
	std::ofstream fileList;
	std::ofstream fileData;
};
