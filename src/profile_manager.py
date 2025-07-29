import json
import os

class ProfileManager:
    def __init__(self, profiles_dir="profiles"):
        self.profiles_dir = profiles_dir
        self.profiles = self.load_profiles()
        self.active_profile = None
        if self.profiles:
            self.active_profile = self.profiles[0]

    def load_profiles(self):
        profiles = []
        for filename in os.listdir(self.profiles_dir):
            if filename.endswith(".json"):
                filepath = os.path.join(self.profiles_dir, filename)
                with open(filepath, "r", encoding="utf-8") as f:
                    profiles.append(json.load(f))
        return profiles

    def set_active_profile(self, profile_name):
        for profile in self.profiles:
            if profile["profileName"] == profile_name:
                self.active_profile = profile
                return True
        return False

    def create_profile(self, profile_name):
        profile_data = {"profileName": profile_name, "actions": []}
        filepath = os.path.join(self.profiles_dir, f"{profile_name}.json")
        with open(filepath, "w", encoding="utf-8") as f:
            json.dump(profile_data, f, indent=2)
        self.profiles.append(profile_data)

    def delete_profile(self, profile_name):
        filepath = os.path.join(self.profiles_dir, f"{profile_name}.json")
        if os.path.exists(filepath):
            os.remove(filepath)
        self.profiles = [p for p in self.profiles if p["profileName"] != profile_name]

    def save_mapping(self, profile_name, key, button):
        for profile in self.profiles:
            if profile["profileName"] == profile_name:
                # Check if the mapping already exists and update it
                for action in profile["actions"]:
                    if action["keyboardMouse"]["primary"] == key:
                        action["xboxController"]["primary"] = button
                        break
                else:
                    # Add a new mapping
                    profile["actions"].append({
                        "name": f"{key} to {button}",
                        "keyboardMouse": {"primary": key},
                        "xboxController": {"primary": button}
                    })
                filepath = os.path.join(self.profiles_dir, f"{profile_name}.json")
                with open(filepath, "w", encoding="utf-8") as f:
                    json.dump(profile, f, indent=2)
                break
