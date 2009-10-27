#pragma once

#include <string>
#include <vector>

typedef unsigned long FileSizeType;

class LibNode
{
	std::wstring path_;
	std::wstring lpath_;
	
	FileSizeType size_;

	bool marked_;

public:
	LibNode(const wchar_t* _path, FileSizeType _size);

	void doMarked() { marked_ = true; }
	bool isMarked() const { return marked_; }

	const wchar_t* path() const { return path_.c_str(); }
	FileSizeType size() const { return 1; } 

	bool operator<(const LibNode& node) const { return lpath_ < node.lpath_; }
};


class LibNodeCalalog : public std::vector<LibNode>
{
public:
	LibNodeCalalog(int reservesize = 15000);

	bool isDot(const wchar_t *name)
	{
		return *name == L'.' && (!name[1] || name[1] == L'.' && !name[2]);
	}

	void add(const wchar_t *str, FileSizeType size);
	void add(const std::wstring& str, FileSizeType size);

	void sort();
};
