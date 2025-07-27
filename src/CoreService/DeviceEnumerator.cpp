#include "DeviceEnumerator.h"
#include <iostream>

// Link with SetupAPI.lib
#pragma comment(lib, "Setupapi.lib")

DeviceEnumerator::DeviceEnumerator() {}

DeviceEnumerator::~DeviceEnumerator() {}

std::vector<InputDevice> DeviceEnumerator::EnumerateDevices() {
    std::vector<InputDevice> devices;
    // HDEVINFO is an opaque handle. INVALID_HANDLE_VALUE is the error condition.
    HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_HIDCLASS, nullptr, nullptr, DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get device information set. Error: " << GetLastError() << std::endl;
        return devices;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // Iterate through all the devices in the set.
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); ++i) {
        InputDevice currentDevice;
        GetDeviceDetails(hDevInfo, &devInfoData, currentDevice);
        devices.push_back(currentDevice);
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return devices;
}

void DeviceEnumerator::GetDeviceDetails(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pDevInfoData, InputDevice& device) {
    // Get Device Instance ID
    device.instanceId = DeviceEnumerator::GetDeviceRegistryProperty(hDevInfo, pDevInfoData, SPDRP_DEVICEDESC);

    // Get a friendly name if available, otherwise use the description
    device.name = DeviceEnumerator::GetDeviceRegistryProperty(hDevInfo, pDevInfoData, SPDRP_FRIENDLYNAME);
    if (device.name.empty()) {
        device.name = device.instanceId;
    }

    // Get Hardware IDs (contains VID and PID)
    std::wstring hardwareIds = DeviceEnumerator::GetDeviceRegistryProperty(hDevInfo, pDevInfoData, SPDRP_HARDWAREID);
    DeviceEnumerator::ParseHardwareIds(hardwareIds, device);
}

std::wstring DeviceEnumerator::GetDeviceRegistryProperty(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pDevInfoData, DWORD property) {
    DWORD dataType;
    DWORD requiredSize = 0;

    // First call to get the size of the buffer needed
    SetupDiGetDeviceRegistryProperty(hDevInfo, pDevInfoData, property, &dataType, nullptr, 0, &requiredSize);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        return L""; // Property may not exist
    }

    std::vector<BYTE> buffer(requiredSize);
    if (!SetupDiGetDeviceRegistryProperty(hDevInfo, pDevInfoData, property, &dataType, buffer.data(), (DWORD)buffer.size(), &requiredSize)) {
        return L""; // Failed to get property
    }

    // Assuming the property is a string (REG_SZ)
    if (dataType == REG_SZ || dataType == REG_MULTI_SZ) {
        return std::wstring(reinterpret_cast<wchar_t*>(buffer.data()));
    }

    return L"";
}

void DeviceEnumerator::ParseHardwareIds(const std::wstring& hardwareIds, InputDevice& device) {
    // The hardware ID string is a multi-string (null-character separated strings, ending with a double null).
    // The format is typically something like "HID\VID_045E&PID_028E&REV_0110".
    // We need to find the VID and PID substrings.

    size_t vidPos = hardwareIds.find(L"VID_");
    if (vidPos != std::wstring::npos) {
        device.vendorId = hardwareIds.substr(vidPos + 4, 4);
    }

    size_t pidPos = hardwareIds.find(L"PID_");
    if (pidPos != std::wstring::npos) {
        device.productId = hardwareIds.substr(pidPos + 4, 4);
    }
}
