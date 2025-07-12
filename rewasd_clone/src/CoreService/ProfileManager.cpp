#include "CoreService/ProfileManager.h"
#include "CoreService/Mapping/MappingRule.h" // Required for full type definition
#include <fstream>
#include <iostream> // For error messages

// Use the nlohmann json alias
using json = nlohmann::json;

Profile::Profile(std::string name) : profileName(std::move(name)) {}

const std::string& Profile::GetName() const {
    return profileName;
}

const std::vector<MappingRule>& Profile::GetMappings() const {
    return mappings;
}

void Profile::AddMapping(const MappingRule& rule) {
    mappings.push_back(rule);
}

ProfileManager::ProfileManager(MappingEngine& engine) : mappingEngine(engine) {}

// Forward declare the actual (de)serialization functions for MappingRule
// These need to be in the nlohmann namespace or accessible via ADL.
// For simplicity, we'll define them here.
namespace nlohmann {
    void to_json(json& j, const InputCondition& cond) {
        j = json{{"type", static_cast<int>(cond.type)},
                 {"id_type", static_cast<int>(cond.idType)}};
        if (cond.idType == InputCondition::IsButton) {
            j["button_id"] = cond.id.buttonId;
        } else {
            j["axis_id"] = cond.id.axisId;
        }
    }

    void from_json(const json& j, InputCondition& cond) {
        cond.type = static_cast<InputType>(j.at("type").get<int>());
        cond.idType = static_cast<InputCondition::IdType>(j.at("id_type").get<int>());
        if (cond.idType == InputCondition::IsButton) {
            cond.id.buttonId = j.at("button_id").get<ButtonID>();
        } else {
            cond.id.axisId = j.at("axis_id").get<AxisID>();
        }
    }

    void to_json(json& j, const OutputAction& action) {
        // This is a simplified version. A real implementation would handle
        // the variant (VirtualButtonAction, VirtualAxisAction, etc.) properly.
        if (std::holds_alternative<VirtualButtonAction>(action.action)) {
            const auto& btnAction = std::get<VirtualButtonAction>(action.action);
            j = json{{"type", "VirtualButtonAction"},
                     {"button", static_cast<int>(btnAction.button)},
                     {"press", btnAction.press}};
        } else if (std::holds_alternative<VirtualAxisAction>(action.action)) {
            const auto& axisAction = std::get<VirtualAxisAction>(action.action);
             j = json{{"type", "VirtualAxisAction"},
                     {"axis", static_cast<int>(axisAction.axis)},
                     {"value", axisAction.value}};
        }
        // Add other action types as needed
    }

    void from_json(const json& j, OutputAction& action) {
        std::string type = j.at("type").get<std::string>();
        if (type == "VirtualButtonAction") {
            VirtualButtonAction btnAction;
            btnAction.button = static_cast<VirtualButtonType>(j.at("button").get<int>());
            btnAction.press = j.at("press").get<bool>();
            action.action = btnAction;
        } else if (type == "VirtualAxisAction") {
            VirtualAxisAction axisAction;
            axisAction.axis = static_cast<VirtualAxisType>(j.at("axis").get<int>());
            axisAction.value = j.at("value").get<int>();
            action.action = axisAction;
        }
        // Add other action types as needed
    }

    void to_json(json& j, const MappingRule& rule) {
        // This requires MappingRule to expose its members or have getters
        // For now, assuming direct access or suitable getters for condition and actions
        // This is a conceptual placeholder as MappingRule's internals are private.
        // We would need to make MappingRule::condition and MappingRule::actions accessible.
        // For now, this won't compile without changes to MappingRule.
        // Let's assume MappingRule has:
        // const InputCondition& GetCondition() const;
        // const std::vector<OutputAction>& GetActions() const;
        // j = json{{"condition", rule.GetCondition()}, {"actions", rule.GetActions()}};

        // Placeholder if MappingRule internals are not accessible
        // This part needs to be adjusted based on MappingRule's actual interface
        j = json{{"error", "MappingRule to_json not fully implemented due to private members"}};
    }

    void from_json(const json& j, MappingRule& rule) {
        // Conceptual placeholder - requires MappingRule to be modifiable or have a suitable constructor
        // InputCondition cond = j.at("condition").get<InputCondition>();
        // std::vector<OutputAction> actions = j.at("actions").get<std::vector<OutputAction>>();
        // rule = MappingRule(cond, actions); // Assuming such a constructor or setters exist

        // Placeholder if MappingRule internals are not accessible
        std::cerr << "MappingRule from_json not fully implemented" << std::endl;
    }
} // namespace nlohmann

bool ProfileManager::LoadProfile(const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open profile file: " << filepath << std::endl;
        return false;
    }

    try {
        json j;
        ifs >> j;

        std::string profileName = j.at("profile_name").get<std::string>();
        Profile loadedProfile(profileName);

        if (j.contains("mappings") && j.at("mappings").is_array()) {
            for (const auto& mapping_json : j.at("mappings")) {
                // This will not work until MappingRule's from_json is correctly implemented
                // and MappingRule is default constructible or constructible from json.
                // MappingRule rule = mapping_json.get<MappingRule>();
                // loadedProfile.AddMapping(rule);
                std::cerr << "Warning: Skipping mapping loading due to incomplete MappingRule deserialization." << std::endl;
            }
        }

        ActivateProfile(loadedProfile);
        std::cout << "Profile loaded: " << profileName << std::endl;
        return true;

    } catch (json::parse_error& e) {
        std::cerr << "Error: Could not parse profile file " << filepath << ": " << e.what() << std::endl;
    } catch (json::exception& e) {
        std::cerr << "Error: JSON exception while loading profile " << filepath << ": " << e.what() << std::endl;
    }
    return false;
}

bool ProfileManager::SaveProfile(const Profile& profile, const std::string& filepath) {
    json j;
    j["profile_name"] = profile.GetName();

    // This will not work until MappingRule's to_json is correctly implemented
    // j["mappings"] = profile.GetMappings(); // This requires a to_json for std::vector<MappingRule>

    j["mappings"] = json::array(); // Placeholder
    for(const auto& rule : profile.GetMappings()) {
        // json rule_json;
        // to_json(rule_json, rule); // This needs a working to_json for MappingRule
        // j["mappings"].push_back(rule_json);
    }
     std::cerr << "Warning: Skipping mapping saving due to incomplete MappingRule serialization." << std::endl;


    std::ofstream ofs(filepath);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open profile file for saving: " << filepath << std::endl;
        return false;
    }

    try {
        ofs << j.dump(4); // Save with an indent of 4 for readability
        std::cout << "Profile saved: " << profile.GetName() << " to " << filepath << std::endl;
        return true;
    } catch (json::exception& e) {
        std::cerr << "Error: JSON exception while saving profile " << filepath << ": " << e.what() << std::endl;
    }
    return false;
}

void ProfileManager::ActivateProfile(const Profile& profile) {
    mappingEngine.LoadMappings(profile.GetMappings());
    std::cout << "Profile activated: " << profile.GetName() << std::endl;
}
