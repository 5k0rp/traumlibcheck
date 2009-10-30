#pragma once

#include "LibNode.h"

class TraumDb : public LibNodeCalalog
{
public:
	TraumDb();

	bool add(const wchar_t* path);
};