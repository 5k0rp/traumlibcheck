#include "common.h"

#include "DirStructure.h"
#include "TraumDb.h"

#include <windows.h>
#include <stdio.h>

int wmain(int argc, wchar_t* argv[])
{
	DirStructure dirStruct;

	wprintf(L"Reading EN...");
	if(dirStruct.add(L"en"))
		wprintf(L"  done\n");
	else {
		wprintf(L"  error\n");
		return -1;
	}

	wprintf(L"Reading RU...");
	if(dirStruct.add(L"ru"))
		wprintf(L"  done\n");
	else {
		wprintf(L"  error\n");
		return -1;
	}

	wprintf(L"Sorting...");
	dirStruct.sort();
	wprintf(L"  done\n");

	
	TraumDb traumDb;

	wprintf(L"Readind Traum db...");
	if(traumDb.add(L"db\\book"))
		wprintf(L"  done\n");
	else {
		wprintf(L"  error\n");
		return -1;
	}

	wprintf(L"Sorting...");
	traumDb.sort();
	wprintf(L"  done\n");

	LibNodeCalalog::iterator tit = traumDb.begin();
	for(; tit != traumDb.end(); ++tit){
		LibNodeCalalog::iterator dit = dirStruct.bsearch(tit->path());
		if(dit != dirStruct.end())
			dit->doMarked();
	}
	
	return 0;
}

