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

void LibNode::getFolder(std::wstring& out) const {
	static const std::wstring::size_type npos = -1;

	std::wstring::size_type idx1 = path_.find_last_of(L'\\');
	std::wstring::size_type idx2 = path_.find_last_of(L'/');

	if(idx1 == npos)
		if(idx2 == npos)
			out.clear();
		else
			out = std::wstring(path_.begin(), path_.begin() + idx2);
	else
		if(idx2 == npos)
			out = std::wstring(path_.begin(), path_.begin() + idx1);
		else
			out = std::wstring(path_.begin(), path_.begin() + (idx1 < idx2 ? idx1 : idx2));

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
