#include "common.h"

#include "DirStructure.h"
#include "TraumDb.h"
#include "null_wcodecvt.h"

#include <windows.h>
#include <stdio.h>
#include <fstream>

void splitPath(Combowstrings& tree, const wchar_t* ptr)
{
	tree.clear();

	const wchar_t* start = ptr;

	for(; *ptr; ++ptr)
		if(*ptr == L'\\')
			tree.push_back(std::wstring(start, ptr));

	tree.push_back(std::wstring(start, ptr));
}

bool checkAndPrint(std::wostream& fout, const LibNodeCalalog& cat, LibNode::MarkType type, const wchar_t* header)
{
	bool isFind = false;
	for(LibNodeCalalog::const_iterator it = cat.begin(); it != cat.end(); ++it)
		if(it->mark() == type){
			if(!isFind){
				isFind = true;
				fout << wendl << header << wendl;
			}
			fout << it->path() << wendl;
		}
	return isFind;
}

int wmain(int argc, wchar_t* argv[])
{
	wprintf(L"Traum library check tool. V1.0b. 2009-10-29. Sk0rp\n");
	
	DirStructure dirStruct;

	wprintf(L"Reading EN...");
	if(dirStruct.add(L"en"))
		wprintf(L" done\n");
	else {
		wprintf(L" error\n");
		return -1;
	}

	wprintf(L"Reading RU...");
	if(dirStruct.add(L"ru"))
		wprintf(L" done\n");
	else {
		wprintf(L" error\n");
		return -1;
	}

	
	TraumDb traumDb;

	wprintf(L"Reading Traum db...");
	if(traumDb.add(L"db\\book"))
		wprintf(L" done\n");
	else {
		wprintf(L" error\n");
		return -1;
	}

	wprintf(L"Sorting...");
	dirStruct.sort();
	traumDb.sort();
	wprintf(L" done\n");

	wprintf(L"Checking...");

	std::wfstream fout;

	null_wcodecvt wcodec(1);
	std::locale wloc(std::locale::classic(), &wcodec);
	fout.imbue(wloc);

	fout.open("cmplog.txt", std::ios::out | std::ios::binary);
	if(!fout){
		std::cerr << "Failed to open cmplog.txt for writting" << std::endl;
		return 1;
	}

	fout << UTF_BOM << L"Протокол сравнения db\\book и библиотеки на диске." << wendl;
	
	bool lostFiles = false;
	
	std::wstring lastpath;

	LibNodeCalalog::iterator dit;
	LibNodeCalalog::iterator tit = traumDb.begin();
	
	for(; tit != traumDb.end(); ++tit){

		std::wstring curpath;
		tit->getFolder(curpath);

		if(curpath != lastpath){
			lastpath = curpath;

			Combowstrings tree;
			splitPath(tree, curpath.c_str());

			Combowstrings::const_iterator it = tree.begin();
			for(; it != tree.end(); ++it){
				dit = dirStruct.bsearch(it->c_str());
				if(dit != dirStruct.end())
					if(wcscmp(LibNode(it->c_str(), 0).file(), dit->file()))
						dit->setMark(LibNode::WRONG_CASE);
					else
						dit->setMark(LibNode::ALL_GOOD);
			}
		}

		LibNodeCalalog::iterator dit = dirStruct.bsearch(tit->path());
		if(dit != dirStruct.end()){
			if(tit->size() == dit->size())
				if(wcscmp(tit->file(), dit->file()))
					dit->setMark(LibNode::WRONG_CASE);
				else
					dit->setMark(LibNode::ALL_GOOD);
			else
				dit->setMark(LibNode::WRONG_SIZE);
			
		}
		else {
			if(!lostFiles){
				lostFiles = true;
				fout << wendl << L"Не найдено в библиотеке:" << wendl;
			}
			fout << tit->path() << wendl;
		}
	}

	bool overFiles = checkAndPrint(fout, dirStruct, LibNode::NO_FILE, L"\nЛишнее в библиотеке:");
	overFiles = checkAndPrint(fout, dirStruct, LibNode::WRONG_SIZE, L"\nДругой размер:") || overFiles;
	overFiles = checkAndPrint(fout, dirStruct, LibNode::WRONG_CASE, L"\nОтличается регистр букв:") || overFiles;

	if(!lostFiles && !overFiles)
		fout << wendl << L"Расхождений не обнаружено!" << wendl;

	fout.close();

	wprintf(L" done.  Look cmplog.txt\n");

	return 0;
}

