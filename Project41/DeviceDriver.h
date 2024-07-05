#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    bool isOkayToWrite(long address);

protected:
    FlashMemoryDevice* m_hardware;
};