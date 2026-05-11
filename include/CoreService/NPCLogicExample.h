#pragma once

#include <string>
#include <vector>
#include <iostream>

// Simple representation of body parts for dismemberment
enum class BodyPart {
    Head,
    Torso,
    LeftArm,
    RightArm,
    LeftLeg,
    RightLeg
};

// State of the NPC
enum class NPCState {
    Idle,
    Chained,
    Dead
};

struct BodyPartStatus {
    BodyPart part;
    bool isAttached = true;
    float health = 100.0f;
};

class NPC {
public:
    NPC(std::string name) : name(name), state(NPCState::Idle) {
        // Initialize body parts
        bodyParts = {
            {BodyPart::Head}, {BodyPart::Torso},
            {BodyPart::LeftArm}, {BodyPart::RightArm},
            {BodyPart::LeftLeg}, {BodyPart::RightLeg}
        };
    }

    void Chain() {
        if (state != NPCState::Dead) {
            state = NPCState::Chained;
            std::cout << name << " has been chained!" << std::endl;
        }
    }

    void TakeDamage(BodyPart part, float damage) {
        for (auto& bp : bodyParts) {
            if (bp.part == part && bp.isAttached) {
                bp.health -= damage;
                std::cout << name << "'s " << BodyPartToString(part) << " took " << damage << " damage. Health: " << bp.health << std::endl;

                if (bp.health <= 0) {
                    bp.isAttached = false;
                    std::cout << name << "'s " << BodyPartToString(part) << " has been cut off!" << std::endl;
                }
                break;
            }
        }
    }

private:
    std::string name;
    NPCState state;
    std::vector<BodyPartStatus> bodyParts;

    std::string BodyPartToString(BodyPart part) {
        switch (part) {
            case BodyPart::Head: return "Head";
            case BodyPart::LeftArm: return "Left Arm";
            case BodyPart::RightArm: return "Right Arm";
            // ... etc
            default: return "Part";
        }
    }
};
