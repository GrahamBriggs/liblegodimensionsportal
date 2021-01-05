//  Joystick Thread
//  Code adapted from Jason White
//  https://gist.github.com/jasonwhite/c5b2048c15993d285130
//  

#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <string>
#include "PortalThread.h"
#include "StringExtensions.h"
#include <list>


using namespace std;


//  Constructor
//
PortalThread::PortalThread(padEventCallback fn)
{
	PadEventCallback = fn;
	DeviceHandle = 0x00;

}


//  Destructor
//
PortalThread::~PortalThread()
{
	if (ThreadRunning)
	{
		Cancel();
	}
}


//  Cancel function
//
void PortalThread::Cancel()
{
	if (DeviceHandle != 0x00)
	{
		usb_close(DeviceHandle);
	}
	
	Thread::Cancel();
}


//  Initialize the portal and start the thread
//
int PortalThread::InitializePortal()
{
	struct usb_bus *bus;
	struct usb_device *dev;
	struct usb_device* found = NULL;
	
	usb_init();
	usb_find_busses();
	usb_find_devices();
	for (bus = usb_busses; bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next) 
		{
			//  searching for a single instance of the Lego Dimensions device
			if (dev->descriptor.idVendor == 0x0e6f) 
			{
				found = dev;
				break;
			}
		}
		
		if (found)
			break;
	}
	
	// open the device
	DeviceHandle = usb_open(found);
	
	int res = -1;
	if (DeviceHandle != 0x00)
	{
		//  detech kernal driver (don't check return code, it will fail if kernal driver is not attached and we don't care then)
		usb_detach_kernel_driver_np(DeviceHandle, 0);

		//  set the default configuration for the device
		res = usb_set_configuration(DeviceHandle, 1);
		if (res == 0)
		{
			//  send the init command
			char initCmd[32] = { 0x55, 0x0f, 0xb0, 0x01, 0x28, 0x63, 0x29, 0x20, 0x4c, 0x45, 0x47, 0x4f, 0x20, 0x32, 0x30, 0x31, 0x34, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			if (usb_bulk_write(DeviceHandle, 1, initCmd, 32, 1000) != 32)
				res = -1;
		}
	}
	
	return res;
}


//  Add a device command to the queue
//
void PortalThread::AddCommand(DimensionsCommand* command)
{
	{
		LockMutex lockQueue(QueueMutex);
		CommandQueue.push(command);
	}
}


//  Thread run function
//
void PortalThread::RunFunction()
{
	char readBuffer[32] = { 0x00 };
	
	while (ThreadRunning)
	{		
		if (ReadPadsEnabled)
		{
			auto readBytes = usb_bulk_read(DeviceHandle, 0x81, readBuffer, 32, 50);
			if (readBytes > 0)
			{
				switch (readBuffer[0])
				{
					case  0x56:	//  read data about tag on pad
					{
						padEvent event;
				
						event.Pad = (int)(readBuffer[2]);
						event.Removed = (bool)(readBuffer[5]);
							
						string uid = "";
						for (int i = 6; i < 13; i++)
						{
							uid += format("%02x", readBuffer[i]);
						}
						event.Uid = uid.c_str();

						PadEventCallback(event);
					}
					break;
				}	
			}
		}
		
		list<DimensionsCommand*> commands;
		{
			LockMutex lockQueue(QueueMutex);
		
			while (CommandQueue.size() > 0)
			{
				commands.push_back(CommandQueue.front());
				CommandQueue.pop();
			}
		}
	
		//  send commands to the dimensions portal
		for(auto nextCommand = commands.begin() ; nextCommand != commands.end() ; ++nextCommand)
		{
			auto wroteBytes = usb_bulk_write(DeviceHandle, 1, (*nextCommand)->GetCommand(), 32, 1000);
			
			delete(*nextCommand); 
		}
		
		Sleep(10);
	}
}