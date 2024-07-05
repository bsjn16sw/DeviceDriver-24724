#include "DeviceDriver.h"
#include <unordered_set>


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    std::unordered_set<int> readResults;
    for (int i = 0; i < 5; i++) {
        readResults.insert((int)(m_hardware->read(address)));
    }
    if (readResults.size() != 1) {
        return 0;
    }
    return *readResults.begin();
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}