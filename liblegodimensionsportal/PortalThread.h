#pragma once
#include "Thread.h"
#include "usb.h"
#include "liblegodimensionsportal.h"
#include "DimensionsCommand.h"
#include <queue>

class PortalThread : public Thread
{
public:
	
	PortalThread(padEventCallback fn);
	
	virtual ~PortalThread();
	
	int InitializePortal();
	
	bool IsConnected() { return DeviceHandle != 0x00; }
	
	bool ReadPadsEnabled;
	
	virtual void Cancel();
	
	virtual void RunFunction();
	
	void AddCommand(DimensionsCommand* command);
	
protected:
	
	
	padEventCallback PadEventCallback;
	
	usb_dev_handle* DeviceHandle;
	
	//  message queue, protected with mutex
	std::mutex QueueMutex;
	std::queue<DimensionsCommand*> CommandQueue;
	
};