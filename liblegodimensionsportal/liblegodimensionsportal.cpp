#include <map>

#include "liblegodimensionsportal.h"

#include "PortalThread.h"
#include "CommandSwitchPad.h"
#include "CommandSwitchPads.h"
#include "CommandFadePads.h"
#include "CommandFlashPads.h"

using namespace std;

//  Registered callbacks
map<padEventCallback, padEventCallback> RegisteredCallbackFns;

//  Callback functions
void PortalCallback(padEvent event)
{
	for (auto nextFn = RegisteredCallbackFns.begin(); nextFn != RegisteredCallbackFns.end(); ++nextFn)
	{
		(*nextFn->first)(event);
	}
}

//  Single instance of a Dimensions Portal object
PortalThread ThePortal(PortalCallback);


//  Register callback function
//
void RegisterPadEventCallback(padEventCallback fn)
{
	RegisteredCallbackFns[fn] = fn;
}


//  Initialize Portal
//
int  InitializePortal()
{	
	auto res = ThePortal.InitializePortal();
	if (res == 0)
	{
		ThePortal.Start();
	}
	
	return res;
}


//  Stop the portal
//
void StopPortal()
{
	ThePortal.Cancel();
}
	

//  Start monitoring pad state
//
int StartPadMonitor()
{
	ThePortal.ReadPadsEnabled = true;
}


//  Stop monitoring the pad state
void StopPadMonitor()
{
	ThePortal.ReadPadsEnabled = false;
}
	

//  Turn pad light off
//
int PadLightOff(char pad)
{
	CommandSwitchPad* switchPad = new CommandSwitchPad(pad, rgb());
	ThePortal.AddCommand(switchPad);
}


//  Switch pad light
//
int SwitchPadLight(char pad, rgb colour)
{
	CommandSwitchPad* switchPad = new CommandSwitchPad(pad, colour);
	ThePortal.AddCommand(switchPad);
}
	

//  Switch all pad lights
//
extern int SwitchAllLights(rgb colour0, rgb colour1, rgb colour2)
{
	CommandSwitchPads* switchPads = new CommandSwitchPads(colour0, colour1, colour2);
	ThePortal.AddCommand(switchPads);
}


//  Fade pad lights
//
extern int FadePadLights(char pulseTime, char pulseCount, rgb colour0, rgb colour1, rgb colour2)
{
	CommandFadePad* fadePads = new CommandFadePad(pulseTime, pulseCount, colour0, colour1, colour2);
	ThePortal.AddCommand(fadePads);
}


//  Flash pad lights
//
extern int FlashPadLights(char onLength, char offLength, char pulseCount, rgb colour0, rgb colour1, rgb colour2)
{
	CommandFlashPad* flashPads = new CommandFlashPad(onLength, offLength, pulseCount, colour0, colour1, colour2);
	ThePortal.AddCommand(flashPads);
}