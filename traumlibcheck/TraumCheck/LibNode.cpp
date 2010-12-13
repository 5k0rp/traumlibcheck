#include "common.h"

#include "LibNode.h"

#include <algorithm>
#include <functional>

LibNode::LibNode(const wchar_t* _path, FileSizeType _size)
: path_(_path)
, lpath_(_path)
, size_(_size)
{
	std::locale locRus("RUS");
	std::transform(lpath_.begin(), lpath_.end(), lpath_.begin(),
		std::bind1st(std::mem_fun(&std::ctype<wchar_t>::tolower), &std::use_facet<std::ctype<wchar_t> >(locRus)));
}

void LibNode::getFolder(std::wstring& out) const
{
	std::wstring::size_type idx = path_.find_last_of(L'\\');

	if(idx == std::wstring::size_type(-1))
		out.clear();
	else
		out = std::wstring(path_.begin(), path_.begin() + idx);
}

LibNodeMarked::LibNodeMarked(const wchar_t* _path, FileSizeType _size)
: LibNode(_path, _size)
, mark_(NO_FILE)
, correctPath_(_path)
, correctSize_(_size)
{

}