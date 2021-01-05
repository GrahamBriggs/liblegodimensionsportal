#pragma once

#include "DimensionsCommand.h"
#include "liblegodimensionsportal.h"
	
	
class CommandFadePad : public DimensionsCommand
{
public:
	CommandFadePad(char fadeTime, char pulseCount, rgb colour0, rgb colour1, rgb colour2)
	{
		Command.push_back(0x55);
		Command.push_back(0x14);
		Command.push_back(0xc6);
		Command.push_back(0x26);
		
		
		Command.push_back(Enabled(colour0));
		Command.push_back(Enabled(colour0) ? fadeTime : 0);
		Command.push_back(Enabled(colour0) ? pulseCount : 0);
		Command.push_back(colour0.r);
		Command.push_back(colour0.g);
		Command.push_back(colour0.b);
		
		Command.push_back(Enabled(colour1));
		Command.push_back(Enabled(colour1) ? fadeTime : 0);
		Command.push_back(Enabled(colour1) ? pulseCount : 0);
		Command.push_back(colour1.r);
		Command.push_back(colour1.g);
		Command.push_back(colour1.b);
		
		Command.push_back(Enabled(colour2));
		Command.push_back(Enabled(colour2) ? fadeTime : 0);
		Command.push_back(Enabled(colour2) ? pulseCount : 0);
		Command.push_back(colour2.r);
		Command.push_back(colour2.g);
		Command.push_back(colour2.b);
	}
};