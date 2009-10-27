#include "common.h"

#include "DirStructure.h"

#include <windows.h>
#include <algorithm>

typedef std::vector<std::wstring> Combowstrings;

DirStructure::DirStructure()
{
}

bool DirStructure::add(const wchar_t *path)
{
	if(!path || !*path)
		return false;

	LibNodeCalalog::add(path, 0);

	std::wstring basepath(path);
	basepath.push_back('\\');
	
	std::wstring searchpath(basepath);
	searchpath.push_back('*');
	
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFileW(searchpath.c_str(),  &findFileData);

	if(hFind == INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return false;
	}

	Combowstrings delaydirs;
	
	std::wstring addpath;
	do {
		if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			if(!isDot(findFileData.cFileName))
				delaydirs.push_back(findFileData.cFileName);
		}
		else
			LibNodeCalalog::add(basepath + findFileData.cFileName, findFileData.nFileSizeLow);
	}
	while(FindNextFileW(hFind,  &findFileData));

	FindClose(hFind);

	Combowstrings::const_iterator it = delaydirs.begin();
	for(; it != delaydirs.end(); ++it){
		addpath = basepath;
		addpath += *it;
		add(addpath.c_str());
	}

	return true;
}