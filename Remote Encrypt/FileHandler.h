#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>

using namespace std;

class FileHandler
{
private:
	vector<wstring> filePathes;
	void findFiles(wstring Directory, vector<wstring> &fileFilter, bool subDirectorys);
	void AddBackSlashToPath(wstring &Path);
	bool DirectoryExists(wstring &Path);

public:
	FileHandler();
	~FileHandler();
};

