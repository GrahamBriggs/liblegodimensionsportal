#include "DimensionsCommand.h"

using namespace std;



void PadMessage(vector<char>& buffer)
{
	for (int i = buffer.size(); i < 32; i++)
		buffer.push_back(0x00);
}
	
void GenerateChecksum(vector<char>& buffer)
{
	int checkSum = 0x00;
	for (int i = 0; i < buffer.size(); i++)
	{
		checkSum += buffer[i];
		if (checkSum > 256)
			checkSum -= 256;
	}
	buffer.push_back((char)checkSum);
}




DimensionsCommand::DimensionsCommand()
{
	CommandBuffer = 0x00;
}




DimensionsCommand::~DimensionsCommand()
{
	if (CommandBuffer != 0x00)
		delete CommandBuffer;
}


char* DimensionsCommand::GetCommand()
{
	GenerateChecksum(Command);
	PadMessage(Command);
	
	CommandBuffer = new char[32];
	for (int i = 0; i < Command.size(); i++)
		CommandBuffer[i] = Command[i];
	
	return CommandBuffer;
}