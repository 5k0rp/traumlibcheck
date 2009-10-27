#include "common.h"

#include "LibNode.h"

#include <algorithm>
#include <functional>

LibNode::LibNode(const wchar_t* _path, FileSizeType _size)
: marked_(false)
, path_(_path)
, lpath_(_path)
, size_(_size)
{
	std::locale locRus("RUS");
	std::transform(lpath_.begin(), lpath_.end(), lpath_.begin(),
		std::bind1st(std::mem_fun(&std::ctype<wchar_t>::tolower), &std::use_facet<std::ctype<wchar_t> >(locRus)));
}

LibNodeCalalog::LibNodeCalalog(int reservesize)
{
	reserve(reservesize);
}

void LibNodeCalalog::add(const wchar_t *str, FileSizeType size)
{
	push_back(LibNode(str, size));
}

void LibNodeCalalog::add(const std::wstring& str, FileSizeType size)
{
	push_back(LibNode(str.c_str(), size));
}

void LibNodeCalalog::sort()
{
	std::sort(begin(), end());
}
