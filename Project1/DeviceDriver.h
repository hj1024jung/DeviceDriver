#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    static const int ReadTryCount = 5;

    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    static const int ReadIssueIntervalMilliSec = 200;


    FlashMemoryDevice* m_hardware;
};