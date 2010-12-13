#pragma once

#include "LibNode.h"

class DirStructure : public LibNodeCatalog<LibNodeMarked>
{
public:
	DirStructure();

	bool add(const wchar_t* path);
};