#pragma once

#include <cstdint>
#include <variant>
#include <vector>

// Define virtual controller elements that can be targeted
// These would correspond to ViGEmBus (e.g., XUSB_GAMEPAD_...) or other virtual outputs

enum class VirtualButtonType {
    // Xbox Controller Buttons
    XBOX_DPAD_UP,
    XBOX_DPAD_DOWN,
    XBOX_DPAD_LEFT,
    XBOX_DPAD_RIGHT,
    XBOX_START,
    XBOX_BACK,
    XBOX_LEFT_THUMB,
    XBOX_RIGHT_THUMB,
    XBOX_LEFT_SHOULDER,
    XBOX_RIGHT_SHOULDER,
    XBOX_GUIDE, // Special button
    XBOX_A,
    XBOX_B,
    XBOX_X,
    XBOX_Y,
    // Keyboard Keys (example, this would be extensive)
    KEY_SPACE,
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    // Mouse Buttons (example)
    MOUSE_LEFT_BUTTON,
    MOUSE_RIGHT_BUTTON
    // ... other virtual buttons/keys
};

enum class VirtualAxisType {
    // Xbox Controller Axes
    XBOX_LEFT_STICK_X,
    XBOX_LEFT_STICK_Y,
    XBOX_RIGHT_STICK_X,
    XBOX_RIGHT_STICK_Y,
    XBOX_LEFT_TRIGGER,  // Range 0-255
    XBOX_RIGHT_TRIGGER, // Range 0-255
    // Mouse Axes (example)
    MOUSE_X,
    MOUSE_Y,
    MOUSE_SCROLL_WHEEL
    // ... other virtual axes
};

struct VirtualButtonAction {
    VirtualButtonType button;
    bool press; // true to press, false to release
};

struct VirtualAxisAction {
    VirtualAxisType axis;
    int value; // Value depends on the axis (e.g., -32768 to 32767 for sticks, 0-255 for triggers)
};

// Placeholder for more complex actions like macros
struct MacroAction {
    std::string macroName; // Identifier for a predefined macro
    // Or perhaps a sequence of actions directly
    // std::vector<std::variant<VirtualButtonAction, VirtualAxisAction, DelayAction>> sequence;
};


// Using std::variant to hold different types of output actions
using OutputActionData = std::variant<
    VirtualButtonAction,
    VirtualAxisAction,
    MacroAction // Example for future extension
>;

struct OutputAction {
    OutputActionData action;
    // Potentially add target virtual device ID if multiple virtual controllers are supported
};
