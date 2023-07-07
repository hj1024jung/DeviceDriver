#pragma once
#include "DeviceDriver.h"

class Application
{
public:
	explicit  Application(DeviceDriver* pstDriver)
		:m_pstDriver(pstDriver)
	{}

	void ReadAndPrint(int startAddr, int endAddr);
	void WriteAll(int value);

private:
	DeviceDriver* m_pstDriver;
};