import tkinter as tk
from tkinter import ttk

class Application(tk.Tk):
    def __init__(self, profile_manager, mapping_engine):
        super().__init__()
        self.title("A-Game")
        self.geometry("400x200")

        self.profile_manager = profile_manager
        self.mapping_engine = mapping_engine

        self.create_widgets()

    def create_widgets(self):
        self.profile_label = ttk.Label(self, text="Select Profile:")
        self.profile_label.pack(pady=10)

        self.profile_variable = tk.StringVar(self)
        self.profile_dropdown = ttk.Combobox(self, textvariable=self.profile_variable)
        self.profile_dropdown["values"] = [p["profileName"] for p in self.profile_manager.profiles]
        if self.profile_manager.active_profile:
            self.profile_variable.set(self.profile_manager.active_profile["profileName"])
        self.profile_dropdown.pack(pady=5)

        self.activate_button = ttk.Button(self, text="Activate Profile", command=self.activate_profile)
        self.activate_button.pack(pady=10)

        self.status_label = ttk.Label(self, text="Status: Inactive")
        self.status_label.pack(pady=5)

    def activate_profile(self):
        profile_name = self.profile_variable.get()
        if self.profile_manager.set_active_profile(profile_name):
            self.status_label.config(text=f"Status: Active - {profile_name}")
        else:
            self.status_label.config(text="Status: Error - Profile not found")

if __name__ == "__main__":
    # This is for testing the GUI independently
    from profile_manager import ProfileManager
    from mapping_engine import MappingEngine
    from virtual_controller import VirtualController

    virtual_controller = VirtualController()
    profile_manager = ProfileManager(profiles_dir="profiles")
    mapping_engine = MappingEngine(virtual_controller, profile_manager)

    app = Application(profile_manager, mapping_engine)
    app.mainloop()
