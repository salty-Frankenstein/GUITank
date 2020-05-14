#pragma once
#include<string>
#include<map>

class DataAccessor {
public:
	DataAccessor(std::string path, std::string name);
	void Load(std::string name);
private:
	std::string GetLastPath(const std::string& p);
	std::string path;
	//pair: the prefix byte number and the byte number of each file
	std::map<std::string, std::pair<int, int>> fileMap;	
	void pr();
};
