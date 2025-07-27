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
#include "CoreService/ProfileManager.h"
#include "CoreService/Mapping/MappingRule.h" // For creating test mappings

// In a more complex app, you'd have a central context object rather than globals.
// For this example, we'll pass references down from main.
RawInputHandler* g_pRawInputHandler = nullptr;

std::string wstring_to_string(const std::wstring& wstr) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(wstr);
}

void PrintDeviceList() {
    std::cout << "\nEnumerating HID devices..." << std::endl;
    DeviceEnumerator enumerator;
    std::vector<InputDevice> devices = enumerator.EnumerateDevices();
    if (devices.empty()) {
        std::cout << "No HID devices found." << std::endl;
    } else {
        std::cout << "Found " << devices.size() << " devices." << std::endl;
        // ... (printing logic is the same)
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_INPUT:
            if (g_pRawInputHandler) g_pRawInputHandler->ProcessRawInput(lParam);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

HWND CreateHiddenWindow() {
    const wchar_t CLASS_NAME[] = L"CoreServiceHiddenWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
    return CreateWindowEx(0, CLASS_NAME, L"Core Service Hidden Window", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, GetModuleHandle(NULL), NULL);
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
    std::cout << "Core Service Starting..." << std::endl;
    PrintDeviceList();

    // --- Core Component Initialization ---
    VirtualController controller;
    if (!controller.Initialize()) {
        std::cerr << "Failed to initialize virtual controller. Exiting." << std::endl;
        return 1;
    }
    std::cout << "Virtual controller initialized successfully." << std::endl;

    MappingEngine mappingEngine(controller); // Create the mapping engine
    ProfileManager profileManager(mappingEngine);

    // --- Load Profiles ---
    std::string profilePath = "Profiles"; // Relative path to the profiles directory
    profileManager.LoadProfilesFromDirectory(profilePath);

    const auto& profiles = profileManager.GetProfiles();
    if (!profiles.empty()) {
        std::cout << "\n--- Available Profiles ---" << std::endl;
        for (const auto& profile : profiles) {
            std::cout << "- " << profile.GetName() << std::endl;
        }
        // Activate the first loaded profile for demonstration
        profileManager.ActivateProfile(profiles.front());
    } else {
        std::cout << "\nNo profiles found. Using default empty mapping." << std::endl;
    }
    // --------------------


    HWND hwnd = CreateHiddenWindow();
    if (hwnd == NULL) {
        std::cerr << "Failed to create hidden window. Exiting." << std::endl;
        return 1;
    }
    std::cout << "\nCreated hidden window for message processing." << std::endl;

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
