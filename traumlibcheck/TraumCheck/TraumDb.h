#pragma once

#include "LibNode.h"

class TraumDb : public LibNodeCatalog<LibNode>
{
public:
	TraumDb();

	bool add(const wchar_t* path);
};