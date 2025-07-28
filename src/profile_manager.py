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
