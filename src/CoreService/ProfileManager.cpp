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
        } else if (std::holds_alternative<MacroAction>(action.action)) {
            const auto& macroAction = std::get<MacroAction>(action.action);
            j = json{{"type", "MacroAction"},
                     {"name", macroAction.macroName}};
            json steps = json::array();
            for (const auto& step : macroAction.sequence) {
                if (std::holds_alternative<VirtualButtonAction>(step)) {
                    const auto& b = std::get<VirtualButtonAction>(step);
                    steps.push_back({{"type", "button"}, {"id", static_cast<int>(b.button)}, {"press", b.press}});
                } else if (std::holds_alternative<DelayAction>(step)) {
                    const auto& d = std::get<DelayAction>(step);
                    steps.push_back({{"type", "delay"}, {"duration", d.durationMs}});
                }
            }
            j["sequence"] = steps;
        }
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
        } else if (type == "MacroAction") {
            MacroAction macro;
            macro.macroName = j.at("name").get<std::string>();
            for (const auto& step_j : j.at("sequence")) {
                std::string step_type = step_j.at("type").get<std::string>();
                if (step_type == "button") {
                    VirtualButtonAction b;
                    b.button = static_cast<VirtualButtonType>(step_j.at("id").get<int>());
                    b.press = step_j.at("press").get<bool>();
                    macro.sequence.push_back(b);
                } else if (step_type == "delay") {
                    DelayAction d;
                    d.durationMs = step_j.at("duration").get<uint32_t>();
                    macro.sequence.push_back(d);
                }
            }
            action.action = macro;
        }
    }

    void to_json(json& j, const MappingRule& rule) {
        j = json{{"condition", rule.GetCondition()}, {"actions", rule.GetActions()}};
    }

    void from_json(const json& j, MappingRule& rule) {
        InputCondition cond = j.at("condition").get<InputCondition>();
        std::vector<OutputAction> actions = j.at("actions").get<std::vector<OutputAction>>();
        rule = MappingRule(cond, actions);
    }
} // namespace nlohmann

#include <filesystem>
namespace fs = std::filesystem;

// ... (rest of the file)

void ProfileManager::LoadProfilesFromDirectory(const std::string& directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::cout << "Loading profile: " << entry.path().string() << std::endl;
            LoadProfile(entry.path().string());
        }
    }
}

bool ProfileManager::LoadProfile(const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "Error: Could not open profile file: " << filepath << std::endl;
        return false;
    }

    try {
        json j;
        ifs >> j;

        std::string profileName = j.at("profileName").get<std::string>();
        Profile loadedProfile(profileName);

        if (j.contains("mappings") && j.at("mappings").is_array()) {
            for (const auto& rule_json : j.at("mappings")) {
                 MappingRule rule;
                 from_json(rule_json, rule);
                 loadedProfile.AddMapping(rule);
            }
        }

        profiles.push_back(loadedProfile); // Add the loaded profile to the list
        std::cout << "Profile loaded and added to manager: " << profileName << std::endl;
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

    j["mappings"] = json::array();
    for(const auto& rule : profile.GetMappings()) {
        json rule_json;
        to_json(rule_json, rule);
        j["mappings"].push_back(rule_json);
    }


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
