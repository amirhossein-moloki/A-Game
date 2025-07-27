#pragma once

#include "MappingEngine.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// Forward declaration
class MappingRule;

class Profile {
public:
    Profile(std::string name);

    const std::string& GetName() const;
    const std::vector<MappingRule>& GetMappings() const;
    void AddMapping(const MappingRule& rule);

private:
    std::string profileName;
    std::vector<MappingRule> mappings;
};

class ProfileManager {
public:
    ProfileManager(MappingEngine& engine);

    void LoadProfilesFromDirectory(const std::string& directoryPath);
    bool LoadProfile(const std::string& filepath);
    bool SaveProfile(const Profile& profile, const std::string& filepath);
    void ActivateProfile(const Profile& profile);
    const std::vector<Profile>& GetProfiles() const { return profiles; }


private:
    MappingEngine& mappingEngine;
    std::vector<Profile> profiles;

    // JSON serialization helpers
    void to_json(nlohmann::json& j, const MappingRule& rule);
    void from_json(const nlohmann::json& j, MappingRule& rule);
};
