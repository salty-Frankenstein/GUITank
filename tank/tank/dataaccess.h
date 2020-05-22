#pragma once
#include<string>
#include<map>
#include<list>

/* Data Accessor */
class DataAccessor {
public:
	DataAccessor(std::string path, std::string name);
	void Load(std::string name);
	void Clear();
	static std::string GetLastPath(const std::string& p);
private:
	std::string path;
	//pair: the prefix byte number and the byte number of each file
	std::map<std::string, std::pair<int, int>> fileMap;
	std::list<std::string> fileList;
	void pr();
};

/* Data Access Object */
class DataAccess {
public:
	virtual std::wstring GetFile(std::string path) = 0;
	virtual void ClearFile() = 0;
};

/* DAO for Normal accessing */
class NormalDataAccess :public DataAccess {
public:
	NormalDataAccess();
	std::wstring GetFile(std::string path);
	void ClearFile();
};

/* DAO for accessing Compressed Data */
class CompressedDataAccess :public DataAccess {
public:
	CompressedDataAccess(std::string path, std::string name);	//压缩包目录，压缩包名
	std::wstring GetFile(std::string path);
	void ClearFile();
private:
	DataAccessor da;
	std::string prefix;
};


