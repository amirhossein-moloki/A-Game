#include "CoreService/RawInputHandler.h"
#include "CoreService/MappingEngine.h" // To send events to
#include <iostream>
#include <vector>

// Constructor now takes a reference to the MappingEngine
RawInputHandler::RawInputHandler(MappingEngine& engine) : mappingEngine(engine) {}

RawInputHandler::~RawInputHandler() {}

bool RawInputHandler::RegisterForRawInput(HWND hwnd) {
    if (hwnd == nullptr) {
        std::cerr << "Cannot register for Raw Input: HWND is null." << std::endl;
        return false;
    }

    RAWINPUTDEVICE rid[2]; // Register for both gamepad and joystick

    // Gamepad
    rid[0].usUsagePage = 0x01;
    rid[0].usUsage = 0x05;
    rid[0].dwFlags = RIDEV_INPUTSINK;
    rid[0].hwndTarget = hwnd;

    // Joystick
    rid[1].usUsagePage = 0x01;
    rid[1].usUsage = 0x04;
    rid[1].dwFlags = RIDEV_INPUTSINK;
    rid[1].hwndTarget = hwnd;

    if (RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE)) == FALSE) {
        std::cerr << "Failed to register raw input devices. Error: " << GetLastError() << std::endl;
        return false;
    }

    std::cout << "Successfully registered for Raw Input from GamePads and Joysticks." << std::endl;
    return true;
}

void RawInputHandler::ProcessRawInput(LPARAM lParam) {
    UINT dwSize = 0;
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

    if (dwSize == 0) return;

    std::vector<BYTE> lpb(dwSize);
    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb.data(), &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
        std::cerr << "GetRawInputData returned incorrect size." << std::endl;
        return;
    }

    RAWINPUT* raw = (RAWINPUT*)lpb.data();

    if (raw->header.dwType == RIM_TYPEHID) {
        // This is a placeholder for a proper HID parser.
        // A real implementation would need to parse the HID report descriptor
        // for the device to understand the format of bRawData.
        // For this example, we'll make a HUGE assumption that we're getting a
        // simple gamepad report and we'll fake a translation.

        // --- Start of FAKE HID Parsing ---
        // Let's pretend Button 0 is the first bit of the first byte of the data.
        if (raw->data.hid.dwSizeHid > 0) {
            bool isButtonPressed = (raw->data.hid.bRawData[0] & 0x01) != 0;
            ButtonID fakeButtonId = 0; // Let's say we've identified this as button 0

            // To avoid spamming, we'd need to track the previous state.
            // For now, we'll just fire the event. A real system needs state management.
            // This is a major simplification.

            // Create a standardized InputEvent
            ButtonInput btnInput{ fakeButtonId, isButtonPressed };
            InputEvent event(raw->header.hDevice, InputType::Button, btnInput);

            // Pass the standardized event to the mapping engine
            mappingEngine.ProcessInput(event);
        }
        // --- End of FAKE HID Parsing ---

        // The debug output is still useful
        // std::cout << "Received Raw HID Input from device: " << raw->header.hDevice << std::endl;
    }
}
