#pragma once

#include "Mapping/InputEvent.h"
#include "Mapping/MappingRule.h"
#include <vector>
#include <memory> // For std::unique_ptr

// Forward declarations to avoid circular dependencies
class VirtualController;

class MappingEngine {
public:
    // The engine needs a way to send output, so it gets a reference to the virtual controller.
    MappingEngine(VirtualController& controller);
    ~MappingEngine();

    // The main entry point for the engine.
    // It takes a raw input event, finds the appropriate mapping, and executes the output action.
    void ProcessInput(const InputEvent& event);

    // Loads a set of mapping rules. This will eventually load from a profile.
    void LoadMappings(const std::vector<MappingRule>& rules);

private:
    // A reference to the virtual controller to send commands to.
    VirtualController& virtualController;

    // The currently active set of mapping rules.
    std::vector<MappingRule> activeMappings;

    // Executes the actions defined by a mapping rule.
    void ExecuteAction(const OutputAction& action, const InputEvent& sourceEvent);
};
