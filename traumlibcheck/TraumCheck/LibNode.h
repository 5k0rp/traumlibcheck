#pragma once

#include <algorithm>

typedef unsigned long FileSizeType;

class LibNode
{
	std::wstring path_;
	std::wstring lpath_;
	
	FileSizeType size_;

public:
	LibNode(const wchar_t* _path, FileSizeType _size);

	const wchar_t* path() const { return path_.c_str(); }
	
	const wchar_t* file() const { 
		std::wstring::size_type pos = path_.find_last_of(L'\\');
		return pos == std::wstring::size_type(-1) ? path_.c_str() : path_.c_str() + pos + 1;
	}
	
	FileSizeType size() const { return size_; } 

	void getFolder(std::wstring& out) const;

	bool operator<(const LibNode& node) const { return lpath_ < node.lpath_; }
};

class LibNodeMarked : public LibNode
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
	MarkType mark_;

	std::wstring correctPath_;	
	FileSizeType correctSize_;

public:
	LibNodeMarked(const wchar_t* _path, FileSizeType _size);

	void setMark(MarkType _mark) { mark_ = _mark; }
	MarkType mark() const { return mark_; }

	void setCorrectPath(const std::wstring& correctPath) { correctPath_ = correctPath; }
	const wchar_t* getCorrectPath() const { return correctPath_.c_str(); }

	void setCorrectSize(FileSizeType correctSize) { correctSize_ = correctSize; }
	FileSizeType getCorrectSize() const { return correctSize_; }
};

template <class LibNodeType>
class LibNodeCatalog : public std::vector<LibNodeType>
{
public:
	LibNodeCatalog(int reservesize = 15000) {
		reserve(reservesize);
	}

	bool isDot(const wchar_t *name)
	{
		return *name == L'.' && (!name[1] || name[1] == L'.' && !name[2]);
	}

	void add(const wchar_t *str, FileSizeType size) {
		push_back(LibNodeType(str, size));
	}
	void add(const std::wstring& str, FileSizeType size){
		push_back(LibNodeType(str.c_str(), size));
	}

	void sort() {
		std::sort(begin(), end());
	}

	iterator bsearch(const wchar_t* path) {
		LibNodeType val(path, 0);
		iterator it = std::lower_bound(begin(), end(), val);
		if(it != end() && !(val < *it))
			return it;
		return end();
	}

	const_iterator bsearch(const wchar_t* path) const {
		LibNodeType val(path, 0);
		const_iterator it = std::lower_bound(begin(), end(), val);
		if(it != end() && !(val < *it))
			return it;
		return end();
	}
};
