#pragma once
#include <vector>
#include "liblegodimensionsportal.h"

inline char Enabled(rgb colour)
{
	if (colour.r == 0 && colour.g == 0 && colour.b == 0)
		return 0;
	else
		return 1;
}


class DimensionsCommand
{
public:
	
	DimensionsCommand();
	virtual ~DimensionsCommand();
	
	char* GetCommand();
	
protected:
	
	std::vector<char> Command;
	char* CommandBuffer;
};
