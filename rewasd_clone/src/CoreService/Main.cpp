#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

#include "CoreService/VirtualController.h"
#include "CoreService/DeviceEnumerator.h"
#include "CoreService/RawInputHandler.h"
#include "CoreService/MappingEngine.h"
#include "CoreService/Mapping/MappingRule.h" // For creating test mappings

// In a more complex app, you'd have a central context object rather than globals.
// For this example, we'll pass references down from main.
RawInputHandler* g_pRawInputHandler = nullptr;

std::string wstring_to_string(const std::wstring& wstr) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(wstr);
}

void PopulateDeviceList(HWND hListBox) {
    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);

    DeviceEnumerator enumerator;
    std::vector<InputDevice> devices = enumerator.EnumerateDevices();

    if (devices.empty()) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"No HID devices found.");
    } else {
        for (const auto& device : devices) {
            std::wstring wide_name(device.name.begin(), device.name.end());
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)wide_name.c_str());
        }
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            {
                HWND hListBox = CreateWindow(L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_VSCROLL,
                                             10, 10, 350, 200, hwnd, (HMENU)1, NULL, NULL);
                CreateWindow(L"BUTTON", L"Refresh", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                             10, 220, 80, 30, hwnd, (HMENU)2, NULL, NULL);
                PopulateDeviceList(hListBox);
            }
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 2) { // ID of the refresh button is 2
                HWND hListBox = GetDlgItem(hwnd, 1); // ID of the list box is 1
                PopulateDeviceList(hListBox);
            }
            break;
        case WM_INPUT:
            if (g_pRawInputHandler) g_pRawInputHandler->ProcessRawInput(lParam);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

HWND CreateMainWindow() {
    const wchar_t CLASS_NAME[]  = L"MainWClass";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Rewasd Clone",                // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
        );

    return hwnd;
}

// --- Task 2.2: Implement the Translation Loop ---
// This function creates a hardcoded mapping for demonstration purposes.
// In a real app, this would be loaded from a profile file.
void SetupTestMappings(MappingEngine& engine) {
    std::cout << "\nSetting up test mappings..." << std::endl;

    // Rule: Map physical button 0 to virtual Xbox 'A' button.
    // This mapping needs to handle both press and release.
    // Our simplified rule system doesn't differentiate yet, so the mapping engine's
    // ExecuteAction will get called on both press and release. The RawInputHandler's fake parser
    // and the MappingEngine's ExecuteAction will interpret the state.

    InputCondition condition = InputCondition::OnButtonPress(0); // Physical button 0

    // The action doesn't specify press/release, as that will be determined by the input event.
    // So we just specify the target button. A more complex system might have separate actions
    // for press and release. For now, the engine's `ExecuteAction` has logic to handle this.
    std::vector<OutputAction> actions;
    actions.push_back({ .action = VirtualButtonAction{ .button = VirtualButtonType::XBOX_A, .press = true } });
    // Note: The `.press` value here is somewhat redundant with our current simplified `ExecuteAction`
    // which relies on the source event. We'll keep it for clarity. A refined engine would use this.

    MappingRule rule(condition, actions);

    engine.LoadMappings({ rule });
}

int main() {
    // --- Core Component Initialization ---
    VirtualController controller;
    if (!controller.Initialize()) {
        std::cerr << "Failed to initialize virtual controller. Exiting." << std::endl;
        return 1;
    }
    std::cout << "Virtual controller initialized successfully." << std::endl;

    MappingEngine mappingEngine(controller); // Create the mapping engine

    // --- Setup Test Mappings (Task 2.2) ---
    SetupTestMappings(mappingEngine);
    // ------------------------------------

    HWND hwnd = CreateMainWindow();
    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    RawInputHandler rawInputHandler(mappingEngine); // Pass engine to handler
    g_pRawInputHandler = &rawInputHandler;
    if (!rawInputHandler.RegisterForRawInput(hwnd)) {
        std::cerr << "Failed to register for raw input. Exiting." << std::endl;
        return 1;
    }
    // ---------------------------------------

    std::cout << "\nCore service is running. Pressing physical button 0 should now trigger virtual Xbox 'A' button." << std::endl;
    std::cout << "Waiting for raw input... (Press Ctrl+C in console or close window to exit)" << std::endl;

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup
    g_pRawInputHandler = nullptr;
    controller.Shutdown();
    std::cout << "Core Service Shutting Down..." << std::endl;
    return 0;
}
