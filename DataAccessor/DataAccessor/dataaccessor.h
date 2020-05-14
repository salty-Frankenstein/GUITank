#pragma once
#include<string>
#include<map>
#include<list>

class DataAccessor {
public:
	DataAccessor(std::string path, std::string name);
	void Load(std::string name);
	void Clear();
private:
	std::string GetLastPath(const std::string& p);
	std::string path;
	//pair: the prefix byte number and the byte number of each file
	std::map<std::string, std::pair<int, int>> fileMap;	
	std::list<std::string> fileList;
	void pr();
};
