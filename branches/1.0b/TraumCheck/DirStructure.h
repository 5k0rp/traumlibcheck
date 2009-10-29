#pragma once

#include "LibNode.h"

class DirStructure : public LibNodeCalalog
{
public:
	DirStructure();

	bool add(const wchar_t* path);
};