#pragma once

#include "DimensionsCommand.h"

	
	
class CommandFlashPad : public DimensionsCommand
{
public:
	CommandFlashPad(char onLength, char offLength, char pulseCount, rgb colour0, rgb colour1, rgb colour2)
	{
		Command.push_back(0x55);
		Command.push_back(0x17);
		Command.push_back(0xc7);
		Command.push_back(0x3e);
		
		
		Command.push_back(Enabled(colour0));
		Command.push_back(Enabled(colour0) ? onLength : 0);
		Command.push_back(Enabled(colour0) ? offLength : 0);
		Command.push_back(Enabled(colour0) ? pulseCount : 0);
		Command.push_back(colour0.r);
		Command.push_back(colour0.g);
		Command.push_back(colour0.b);
		
		Command.push_back(Enabled(colour1));
		Command.push_back(Enabled(colour1) ? onLength : 0);
		Command.push_back(Enabled(colour1) ? offLength : 0);
		Command.push_back(Enabled(colour1) ? pulseCount : 0);
		Command.push_back(colour1.r);
		Command.push_back(colour1.g);
		Command.push_back(colour1.b);
		
		Command.push_back(Enabled(colour2));
		Command.push_back(Enabled(colour2) ? onLength : 0);
		Command.push_back(Enabled(colour2) ? offLength : 0);
		Command.push_back(Enabled(colour2) ? pulseCount : 0);
		Command.push_back(colour2.r);
		Command.push_back(colour2.g);
		Command.push_back(colour2.b);
	}
};