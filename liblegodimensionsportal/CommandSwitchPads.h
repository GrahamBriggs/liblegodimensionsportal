#pragma once

#include "DimensionsCommand.h"

	
	
class CommandSwitchPads : public DimensionsCommand
{
public:
	CommandSwitchPads(rgb colour0, rgb colour1, rgb colour2)
	{
		Command.push_back(0x55);
		Command.push_back(0x0e);
		Command.push_back(0xc8);
		Command.push_back(0x06);
		
		
		Command.push_back(Enabled(colour0));
		Command.push_back(colour0.r);
		Command.push_back(colour0.g);
		Command.push_back(colour0.b);
		
		Command.push_back(Enabled(colour1));
		Command.push_back(colour1.r);
		Command.push_back(colour1.g);
		Command.push_back(colour1.b);
		
		Command.push_back(Enabled(colour2));
		Command.push_back(colour2.r);
		Command.push_back(colour2.g);
		Command.push_back(colour2.b);
	}
};