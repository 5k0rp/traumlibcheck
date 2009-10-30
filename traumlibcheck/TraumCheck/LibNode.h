#pragma once

#include <algorithm>

typedef unsigned long FileSizeType;

class LibNode
{
public:
	enum MarkType
	{	
		NO_FILE,
		WRONG_SIZE,
		WRONG_CASE,
		ALL_GOOD
	};
			
private:
	std::wstring path_;
	std::wstring lpath_;
	
	FileSizeType size_;

	MarkType mark_;

public:
	LibNode(const wchar_t* _path, FileSizeType _size);

	void setMark(MarkType _mark) { mark_ = _mark; }
	MarkType mark() const { return mark_; }

	const wchar_t* path() const { return path_.c_str(); }
	
	const wchar_t* file() const { 
		std::wstring::size_type pos = path_.find_last_of(L'\\');
		return pos == std::wstring::size_type(-1) ? path_.c_str() : path_.c_str() + pos + 1;
	}
	
	FileSizeType size() const { return size_; } 

	void getFolder(std::wstring& out) const;

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
