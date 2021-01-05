#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	//  Pad Event Struct
	//
	typedef struct padEvent
	{
		unsigned long long LogUnixTimeMilliseconds;
		int Pad;
		bool Removed;
		const char* Uid;
	} padEvent;
	//
	typedef void(*padEventCallback)(padEvent);
	
	
	//  RGB struct
	//
	typedef struct rgb
	{ 
		rgb()
		{
			r = g = b = 0;
		}
		
		rgb(char red, char green, char blue)
		{
			r = red;
			g = green;
			b = blue;
		}
			
		char r;
		char g;
		char b;
		
	} rgb;
	

	//  Register a callback function to receive pad events
	extern void RegisterPadEventCallback(padEventCallback fn);
	
	// Unregister a callback function to receive pad events
	extern void UnRegisterPadEventCallback(padEventCallback fn);
	
	//  Initialize the portal and start the thread
	extern int  InitializePortal();
	
	//  Stop the portal thread
	extern void StopPortal();
	
	//  Enable pad monitor events
	extern int StartPadMonitor();
	
	//  Disable pad monitor events
	extern void StopPadMonitor();
	
	//  Switch a single pad light off
	extern int PadLightOff(char pad);
	
	//  Switch a single pad light to the give rgb colour
	extern int SwitchPadLight(char pad, rgb colour);
	
	//  Switch all pad lights to the given rgb colours
	extern int SwitchAllLights(rgb colour0, rgb colour1, rgb colour2);
	
	//  Fade pad lights
	/* Fade one or all pad(s) a given colour with optional pulsing effect
        The pad(s) will either revert to old colour or stay on the new one depending on the pulse_count value
        Odd: keep new colour, Even: keep previous colour. Exception: 0x00 keeps new colour.
        pulse_count values of 0x00 and above 0x199 will flash forever.
        pulse_time starts fast at 0x01 and continues to 0xff which is very slow, 0x00 causes immediate change.
        Pad numbering: 0:All, 1:Center, 2:Left, 3:Right
     */
	extern int FadePadLights(char pulseTime, char pulseCount, rgb colour0, rgb colour1, rgb colour2);
	
	//  Flash pad lights
	/*
	  Flash all 3 pads with individual colours and rates, either change to new or return to old based on pulse count.
        0 colour triplets will ignore that pad.
        Ignored pads will continue whatever they were doing previously.
        Pulse length - 0x00 is almost impersceptible,  0xff is ~10 seconds
        Number of flashes - odd value leaves pad in new colour, even leaves pad in old, except for 0x00, which changes to new. Values above 0xc6 dont stop.
	 */
	extern int FlashPadLights(char onLength, char offLength, char pulseCount, rgb colour0, rgb colour1, rgb colour2);


	
	#ifdef __cplusplus
	}
#endif
