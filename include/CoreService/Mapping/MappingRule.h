#pragma once

#include "InputEvent.h"
#include "OutputAction.h"
#include <vector>
#include <functional> // For std::function

// A `MappingRule` defines the relationship between a physical input and a virtual output.

// The condition that triggers the mapping.
// For now, it's a simple equality check on the input event's type and ID.
// This could be expanded to include more complex conditions (e.g., axis ranges, chords).
struct InputCondition {
    InputType type;

    // Using a union for the ID to save space, since it's one or the other.
    union {
        ButtonID buttonId;
        AxisID axisId;
    } id;

    // We need to know which member of the union is active.
    enum { IsButton, IsAxis } idType;

    // Example of how to create conditions easily
    static InputCondition OnButtonPress(ButtonID bId) {
        InputCondition c;
        c.type = InputType::Button;
        c.idType = IsButton;
        c.id.buttonId = bId;
        return c;
    }

    static InputCondition OnAxisMove(AxisID aId) {
        InputCondition c;
        c.type = InputType::Axis;
        c.idType = IsAxis;
        c.id.axisId = aId;
        return c;
    }
};

// A simple rule: one condition triggers one or more output actions.
class MappingRule {
public:
    // Default constructor for deserialization
    MappingRule() = default;

    MappingRule(const InputCondition& condition, const std::vector<OutputAction>& actions)
        : m_condition(condition), m_actions(actions) {}

    bool IsTriggeredBy(const InputEvent& event) const {
        if (event.type != m_condition.type) {
            return false;
        }

        if (m_condition.idType == InputCondition::IsButton && std::holds_alternative<ButtonInput>(event.data)) {
            const auto& buttonData = std::get<ButtonInput>(event.data);
            return buttonData.id == m_condition.id.buttonId;
        }

        if (m_condition.idType == InputCondition::IsAxis && std::holds_alternative<AxisInput>(event.data)) {
            const auto& axisData = std::get<AxisInput>(event.data);
            return axisData.id == m_condition.id.axisId;
        }

        return false;
    }

    const InputCondition& GetCondition() const { return m_condition; }
    const std::vector<OutputAction>& GetActions() const { return m_actions; }

private:
    InputCondition m_condition{};
    std::vector<OutputAction> m_actions{};
};
