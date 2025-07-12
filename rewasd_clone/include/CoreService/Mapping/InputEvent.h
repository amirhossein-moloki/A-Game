#pragma once

#include <string>
#include <cstdint> // For uintN_t types
#include <variant>   // For std::variant

// Represents the physical device that generated the input.
// Using a HANDLE for now as that's what RawInput provides.
// Could be a more abstract ID later if needed.
using PhysicalDeviceID = void*; // Corresponds to RAWINPUTHEADER::hDevice

enum class InputType {
    Unknown,
    Button,
    Axis,
    Trigger, // Could be a special type of axis or handled as an axis
    HatSwitch // POV Hat
};

// Specific identifier for a button on a device (e.g., button 0, button 1, etc.)
// This will be device-specific initially, derived from HID usage pages/usages.
using ButtonID = uint16_t;

// Specific identifier for an axis on a device (e.g., X-axis, Y-axis, Z-axis)
using AxisID = uint16_t;

struct ButtonInput {
    ButtonID id;
    bool isPressed;
};

struct AxisInput {
    AxisID id;
    int value; // Raw axis value, typically from -32768 to 32767 or 0 to 255 for triggers
};

// Using std::variant to hold different types of input data.
// This can be extended with more specific input types (e.g., HatSwitchInput).
using InputData = std::variant<ButtonInput, AxisInput>;

struct InputEvent {
    PhysicalDeviceID deviceID; // Identifies the source physical device
    InputType type;
    InputData data;
    uint64_t timestamp; // Optional: for timing, macros, etc.

    InputEvent(PhysicalDeviceID devId, InputType t, InputData d)
        : deviceID(devId), type(t), data(d), timestamp(0) {} // Timestamp can be set properly later
};
