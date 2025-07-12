#pragma once

#include <vector>
#include <string>
#include <windows.h> // Required for Windows data types like HDEVINFO, etc.

struct InputDevice {
    std::wstring name;
    std::wstring instanceId;
    std::wstring vendorId;
    std::wstring productId;
};

class DeviceEnumerator {
public:
    DeviceEnumerator();
    ~DeviceEnumerator();

    std::vector<InputDevice> EnumerateDevices();

private:
    // This is a placeholder for the actual device enumeration logic.
    // In a real implementation, this would use SetupAPI.
    void GetDeviceDetails(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pDevInfoData, InputDevice& device);
    std::wstring GetDeviceRegistryProperty(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pDevInfoData, DWORD property);
    void ParseHardwareIds(const std::wstring& hardwareIds, InputDevice& device);
};
