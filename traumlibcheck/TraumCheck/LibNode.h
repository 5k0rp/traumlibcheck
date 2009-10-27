#pragma once

#include <string>
#include <vector>
#include <algorithm>

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

	iterator bsearch(const wchar_t* path) {
		LibNode val(path, 0);
		iterator it = std::lower_bound(begin(), end(), val);
		if(it != end() && !(val < *it))
			return it;
		return end();
	}

	const_iterator bsearch(const wchar_t* path) const {
		LibNode val(path, 0);
		const_iterator it = std::lower_bound(begin(), end(), val);
		if(it != end() && !(val < *it))
			return it;
		return end();
	}
};
