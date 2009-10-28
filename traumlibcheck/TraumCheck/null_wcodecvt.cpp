#include "common.h"

#include "null_wcodecvt.h"

std::wostream& wendl(std::wostream& out)
{
    out.put(L'\r');
    out.put(L'\n');
    out.flush();
    return out;
}//wendl

const wchar_t UTF_BOM = 0xfeff;

