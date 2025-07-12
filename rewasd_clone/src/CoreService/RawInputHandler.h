#pragma once

#include <windows.h>

// Forward declaration to avoid circular include
class MappingEngine;

class RawInputHandler {
public:
    // The handler needs a reference to the mapping engine to send events to it.
    RawInputHandler(MappingEngine& engine);
    ~RawInputHandler();

    bool RegisterForRawInput(HWND hwnd);
    void ProcessRawInput(LPARAM lParam);

private:
    // Reference to the mapping engine.
    MappingEngine& mappingEngine;
};
