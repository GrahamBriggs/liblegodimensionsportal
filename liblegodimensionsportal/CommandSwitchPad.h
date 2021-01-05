#pragma once

#include "DimensionsCommand.h"

class CommandSwitchPad : public DimensionsCommand
{
public:
	CommandSwitchPad(char pad, rgb colour)
	{
		Command.push_back(0x55);
		Command.push_back(0x06);
		Command.push_back(0xc0);
		Command.push_back(0x02);
		Command.push_back(pad);
		Command.push_back(colour.r);
		Command.push_back(colour.g);
		Command.push_back(colour.b);
	}
};