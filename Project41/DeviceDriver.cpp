#include "DeviceDriver.h"
#include <unordered_set>


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    m_hardware->read(address);
    m_hardware->read(address);
    m_hardware->read(address);
    m_hardware->read(address);
    m_hardware->read(address);
    return 0;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}