#include "FileHandler.h"


void FileHandler::findFiles(wstring Directory, vector<wstring>& fileFilter, bool subDirectorys)
{
	WIN32_FIND_DATA findData;
	AddBackSlashToPath(Directory);
	wstring originalPath = Directory;

	if (!DirectoryExists(Directory))
	{
		cout << "Directory does not exist!";
		return;
	}
	
	Directory.append(L"*");

	HANDLE hFindFile = FindFirstFile(Directory.c_str(), &findData);

	if (hFindFile != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hFindFile, &findData))
		{
			if (lstrcmp(findData.cFileName, L".") == 0 || lstrcmp(findData.cFileName, L"..") == 0)
				continue;

			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && subDirectorys)
			{
				findFiles(originalPath.append(findData.cFileName), fileFilter, subDirectorys);
			}

			wstring fileName = findData.cFileName;

			for (vector<wstring>::iterator it = fileFilter.begin(); it != fileFilter.end(); it++)
			{
				if (fileName.find(*it) != wstring::npos)
				{
					filePathes.push_back(fileName);
					break;
				}
			}
		}
	}
	return;
}

void FileHandler::AddBackSlashToPath(wstring &Path)
{
	if (Path.back() == L'\\')
	{
		return;
	}
	Path.append(L"\\");
}

bool FileHandler::DirectoryExists(wstring &Path)
{
	DWORD dFileAttributes = GetFileAttributes(Path.c_str());
	if (dFileAttributes != 0xFFFFFFFF && (dFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return true;
	return false;
}

FileHandler::FileHandler()
{
	vector<wstring> a;
	a.push_back(L".mp3");
	a.push_back(L".txt");
	a.push_back(L".exe");
	findFiles(L"C:\\tmp", a, true);
}


FileHandler::~FileHandler()
{
}
