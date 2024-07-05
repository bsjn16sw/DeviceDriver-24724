#include "DeviceDriver.h"
#include <unordered_set>
#include <stdexcept>
#include <string>

class ReadFailException : public std::exception {
public:
    ReadFailException(const char* msg)
        : message(msg) {

    }
    const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

class WriteFailException : public std::exception {
public:
    WriteFailException(const char* msg)
        : message(msg) {

    }
    const char* what() const throw() {
        return message.c_str();
    }

private:
    std::string message;
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    std::unordered_set<int> readResults;
    for (int i = 0; i < 5; i++) {
        readResults.insert((int)(m_hardware->read(address)));
    }
    if (readResults.size() != 1) {
        throw ReadFailException("FlashMemoryDevice returns different value in 5 times.");
    }
    return *readResults.begin();
}

void DeviceDriver::write(long address, int data)
{
    if (isOkayToWrite(address) == false) {
        throw WriteFailException("FlashMemoryDevice is written so cannot be written again.");
    }
    m_hardware->write(address, (unsigned char)data);
}

bool DeviceDriver::isOkayToWrite(long address)
{
    unsigned char data;
    try {
        data = m_hardware->read(address);
    }
    catch (ReadFailException& e) {
        return false;
    }

    if (data == 0xFF)    return true;
    return false;
}