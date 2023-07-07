#include <stdexcept>
#include <Windows.h>
#include "DeviceDriver.h"

using namespace std;

class ReadFailException : public exception
{
public:
    explicit ReadFailException()
		: exception("__READ_EXCEPTION_OCCURED__")
    {}
};


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    const int firstReadVal = m_hardware->read(address);

    for (int loop = 0; loop < (ReadTryCount - 1); loop++)
    {
        Sleep(ReadIssueIntervalMilliSec);

        int readVal = m_hardware->read(address);

    	if (firstReadVal != readVal)
	    {
            throw ReadFailException();
	    }
    }

    return firstReadVal;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}