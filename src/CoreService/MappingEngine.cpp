#include "CoreService/MappingEngine.h"
#include "CoreService/VirtualController.h" // For sending output
#include <iostream> // For debug messages

MappingEngine::MappingEngine(VirtualController& controller) : virtualController(controller) {}

MappingEngine::~MappingEngine() {}

void MappingEngine::LoadMappings(const std::vector<MappingRule>& rules) {
    activeMappings = rules;
    std::cout << "MappingEngine: Loaded " << activeMappings.size() << " mapping rules." << std::endl;
}

void MappingEngine::ProcessInput(const InputEvent& event) {
    // std::cout << "MappingEngine: Processing input event..." << std::endl; // Can be noisy

    for (const auto& rule : activeMappings) {
        if (rule.IsTriggeredBy(event)) {
            std::cout << "MappingEngine: Rule triggered by input." << std::endl;
            const auto& actions = rule.GetActions();
            for (const auto& action : actions) {
                ExecuteAction(action, event);
            }
            // Optimization: If a rule is triggered, do we stop or allow multiple rules to match?
            // For now, let's assume only one rule (or the first matching) should apply for a single input event.
            // This behavior might need to be configurable per profile/mapping.
            // For simplicity, we'll break after the first match.
            break;
        }
    }
}

void MappingEngine::ExecuteAction(const OutputAction& action, const InputEvent& sourceEvent) {
    std::cout << "MappingEngine: Executing action." << std::endl;

    if (std::holds_alternative<VirtualButtonAction>(action.action)) {
        const auto& btnAction = std::get<VirtualButtonAction>(action.action);
        bool shouldBePressed = false; // Default to not pressed

        // The action is for a button, so the source event must also be a button event.
        if (std::holds_alternative<ButtonInput>(sourceEvent.data)) {
            const auto& sourceButton = std::get<ButtonInput>(sourceEvent.data);
            shouldBePressed = sourceButton.isPressed;
        } else {
            // This case should ideally not happen if rules are set up correctly
            // (i.e., button actions only triggered by button inputs).
            std::cerr << "Warning: VirtualButtonAction triggered by a non-button input event." << std::endl;
            return;
        }

        std::cout << "  Action Type: VirtualButton, Button: " << static_cast<int>(btnAction.button)
                  << ", Should Press: " << shouldBePressed << std::endl;

        // Example: Map to VirtualController's Button A for demonstration
        if (btnAction.button == VirtualButtonType::XBOX_A) {
            if (shouldBePressed) {
                virtualController.PressButtonA();
            } else {
                virtualController.ReleaseButtonA();
            }
        }
        // TODO: Implement a comprehensive mapping from VirtualButtonType to actual ViGEmBus calls
        // This will likely involve a switch statement or a map.
        // virtualController.SetButtonState(btnAction.button, shouldBePressed);

    } else if (std::holds_alternative<VirtualAxisAction>(action.action)) {
        const auto& axisAction = std::get<VirtualAxisAction>(action.action);
        std::cout << "  Action Type: VirtualAxis, Axis: " << static_cast<int>(axisAction.axis)
                  << ", Value: " << axisAction.value << std::endl;

        // If the source event was an axis, pass its value directly.
        // This is a common scenario for axis-to-axis mapping.
        int valueToApply = axisAction.value;
        if (std::holds_alternative<AxisInput>(sourceEvent.data)) {
            const auto& sourceAxisData = std::get<AxisInput>(sourceEvent.data);
            // Potentially transform the value (e.g., scaling, inversion, deadzone)
            // For now, a direct pass-through if action value is a sentinel (e.g. -1 means use source)
            // This is a simplification; a more robust system is needed for axis transformation.
            if (axisAction.value == -1) { // Sentinel to indicate "use source value"
                 valueToApply = sourceAxisData.value;
                 std::cout << "  Using source axis value: " << valueToApply << std::endl;
            }
        }

        // TODO: Implement mapping from VirtualAxisType to actual ViGEmBus calls
        // virtualController.SetAxisValue(axisAction.axis, valueToApply);

    } else if (std::holds_alternative<MacroAction>(action.action)) {
        const auto& macroAction = std::get<MacroAction>(action.action);
        std::cout << "  Action Type: Macro, Name: " << macroAction.macroName << std::endl;
        // TODO: Implement macro execution logic
        // This would involve looking up the macro by name and executing its sequence of actions.
    } else {
        std::cout << "  Action Type: Unknown or not yet implemented." << std::endl;
    }
}
