import os
import json

PROFILES_DIR = "rewasd_mapper/profiles"

class ProfileManager:
    def __init__(self):
        if not os.path.exists(PROFILES_DIR):
            os.makedirs(PROFILES_DIR)

    def get_profiles(self):
        """Returns a list of available profile names."""
        profiles = []
        for filename in os.listdir(PROFILES_DIR):
            if filename.endswith(".json"):
                profiles.append(os.path.splitext(filename)[0])
        return profiles

    def save_profile(self, profile_name, data):
        """Saves profile data to a JSON file."""
        if not profile_name:
            raise ValueError("Profile name cannot be empty.")

        filepath = os.path.join(PROFILES_DIR, f"{profile_name}.json")
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=4)

    def load_profile(self, profile_name):
        """Loads profile data from a JSON file."""
        filepath = os.path.join(PROFILES_DIR, f"{profile_name}.json")
        if not os.path.exists(filepath):
            return None
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)

    def delete_profile(self, profile_name):
        """Deletes a profile file."""
        filepath = os.path.join(PROFILES_DIR, f"{profile_name}.json")
        if os.path.exists(filepath):
            os.remove(filepath)
