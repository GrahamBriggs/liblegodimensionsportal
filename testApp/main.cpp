#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <usb.h>
#include <string.h>

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <map>


#include "Thread.h"
#include "StringExtensions.h"
#include "CommandSwitchPads.h"
#include "CommandSwitchPad.h"
#include "liblegodimensionsportal.h"


using namespace std;

void PortalCallback(padEvent event);
bool ProcessKeyboardInput(string input);

int NextColourIndex = 0;
int MaxColourIndex = 15;
rgb Colours[14] = {
	rgb(192, 57, 43),
	rgb(155, 89, 182),
	rgb(41, 128, 185),
	rgb(26, 188, 156),	
	rgb(39, 174, 96),
	rgb(241, 196, 15),
	rgb(230, 126, 34),
	rgb(231, 76, 60),
	rgb(142, 68, 173),
	rgb(52, 152, 219),
	rgb(22, 160, 133),
	rgb(46, 204, 113),
	rgb(243, 156, 18),
	rgb(211, 84, 0)
};


map<string, rgb> DeviceColours;


int main(int argc, char *argv[])
{
	
	InitializePortal();
	StartPadMonitor();
	RegisterPadEventCallback(PortalCallback);
	
	
	
		
	string input;
	while (true)
	{
		getline(cin, input);
		toUpper(input);
		
		if (!ProcessKeyboardInput(input))
		{
		
			break;
		}
	}
			
	StopPortal();
	

	
	
	return 0;
}



//  Process keyboard input from the board read / demo file run loop
//
bool ProcessKeyboardInput(string input)
{
	if (input.compare("Q") == 0) 
	{
		return false;
	}
	
	
	return true;
}

bool IndicatorPad = false;

void PortalCallback(padEvent event)
{
	cout << "Device " << event.Uid << " was " << (event.Removed ? " removed from pad " : " added to pad ") << event.Pad << endl; 
	
	string key = string(event.Uid);

	if (event.Removed)
	{
		PadLightOff(event.Pad);
		if (IndicatorPad)
		{
			PadLightOff(1);
			IndicatorPad = false;
		}
	}
	else
	{
		if (DeviceColours.find(key) == DeviceColours.end())
		{
			if (NextColourIndex == MaxColourIndex)
				NextColourIndex = 0;
		
			cout << "New device assigned colour " << NextColourIndex << "." << endl;
			DeviceColours[key] = Colours[NextColourIndex++];
			SwitchPadLight(1, rgb(0, 200, 0));
			IndicatorPad = true;
			SwitchPadLight(event.Pad, DeviceColours[key]);
		}
		else
		{
			SwitchPadLight(event.Pad, DeviceColours[key]);
		}
	}
		
}