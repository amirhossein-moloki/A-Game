# ui.py
# This script defines the user interface for the input mapper.
# It uses tkinter to create the windows, buttons, and other widgets.
#
# Key Features:
# - A dark theme designed to be appealing to gamers.
# - A profile manager for creating, deleting, and activating mapping profiles.
# - A visual editor for mapping keyboard keys to controller buttons.
#
# Future Improvements:
# - Implement the full functionality of the profile editor, including saving and loading mappings.
# - Add support for more complex mappings, such as macros and sensitivity curves.
# - Improve the visual design with custom icons and more interactive elements.

import tkinter as tk
from tkinter import ttk

class App(tk.Tk):
    def __init__(self, profile_manager):
        super().__init__()
        self.profile_manager = profile_manager
        self.selected_key = None
        self.title("Input Mapper")
        self.geometry("800x600")
        self.configure(bg="#2e2e2e")

        self.style = ttk.Style(self)
        self.style.theme_use("clam")
        self.style.configure("TLabel", foreground="#00ff00", background="#1e1e1e", font=("Consolas", 12))
        self.style.configure("TButton", foreground="#00ff00", background="#3e3e3e", font=("Consolas", 12), borderwidth=1, relief="flat")
        self.style.map("TButton", background=[("active", "#5e5e5e")])
        self.style.configure("TFrame", background="#1e1e1e")
        self.configure(bg="#1e1e1e")

        self.create_widgets()

    def create_widgets(self):
        # Main frame
        main_frame = ttk.Frame(self, padding="20")
        main_frame.pack(fill="both", expand=True)

        # Title
        title_label = ttk.Label(main_frame, text="Input Mapper", font=("Arial", 24, "bold"))
        title_label.pack(pady=(0, 20))

        # Active Profile Section
        active_profile_frame = ttk.Frame(main_frame, padding="10")
        active_profile_frame.pack(fill="x", pady=(0, 20))

        active_profile_label = ttk.Label(active_profile_frame, text="Active Profile:", font=("Arial", 16, "bold"))
        active_profile_label.pack(side="left")

        self.active_profile_name = ttk.Label(active_profile_frame, text="None", font=("Arial", 16))
        self.active_profile_name.pack(side="left", padx=(10, 0))

        # Profile Manager Section
        profile_manager_frame = ttk.Frame(main_frame, padding="10")
        profile_manager_frame.pack(fill="both", expand=True)

        profile_list_label = ttk.Label(profile_manager_frame, text="Profiles", font=("Arial", 16, "bold"))
        profile_list_label.pack(pady=(0, 10))

        self.profile_listbox = tk.Listbox(profile_manager_frame, bg="#3e3e3e", fg="#00ff00", font=("Consolas", 12), borderwidth=0, selectbackground="#5e5e5e", selectforeground="#00ff00")
        self.profile_listbox.pack(fill="both", expand=True, pady=(0, 10))

        button_frame = ttk.Frame(profile_manager_frame)
        button_frame.pack(fill="x")

        new_button = ttk.Button(button_frame, text="New", command=self.new_profile)
        new_button.pack(side="left", padx=(0, 10))

        edit_button = ttk.Button(button_frame, text="Edit", command=self.edit_profile)
        edit_button.pack(side="left", padx=(0, 10))
    def edit_profile(self):
        selected_profile = self.profile_listbox.get(tk.ACTIVE)
        if selected_profile:
            edit_profile_window = tk.Toplevel(self)
            edit_profile_window.title(f"Edit Profile: {selected_profile}")
            edit_profile_window.geometry("800x600")
            edit_profile_window.configure(bg="#1e1e1e")

        notebook = ttk.Notebook(edit_profile_window)
        notebook.pack(fill="both", expand=True)

        mapping_frame = ttk.Frame(notebook)
        advanced_frame = ttk.Frame(notebook)

        notebook.add(mapping_frame, text="Mapping")
        notebook.add(advanced_frame, text="Advanced")

        # Sensitivity settings
        sensitivity_frame = ttk.Frame(advanced_frame, padding="10")
        sensitivity_frame.pack(fill="x")
        sensitivity_label = ttk.Label(sensitivity_frame, text="Left Stick Sensitivity:")
        sensitivity_label.pack(side="left")
        sensitivity_scale = ttk.Scale(sensitivity_frame, from_=0, to=200, orient="horizontal")
        sensitivity_scale.pack(side="left", fill="x", expand=True)

        # Macro settings
        macro_frame = ttk.Frame(advanced_frame, padding="10")
        macro_frame.pack(fill="x")
        macro_label = ttk.Label(macro_frame, text="Macro:")
        macro_label.pack(side="left")
        macro_entry = ttk.Entry(macro_frame)
        macro_entry.pack(side="left", fill="x", expand=True)

        self.selected_key_label = ttk.Label(mapping_frame, text="Selected Key: None")
            self.selected_key_label.pack()

            # Keyboard and Controller frames
        keyboard_frame = ttk.Frame(mapping_frame, width=400, height=600)
            keyboard_frame.pack(side="left", fill="both", expand=True, padx=10, pady=10)
            controller_frame = ttk.Frame(edit_profile_window, width=400, height=600)
            controller_frame.pack(side="right", fill="both", expand=True, padx=10, pady=10)

    def select_key(self, key):
        self.selected_key = key
        self.selected_key_label["text"] = f"Selected Key: {key}"

    def select_button(self, button):
        if self.selected_key:
            selected_profile = self.profile_listbox.get(tk.ACTIVE)
            if selected_profile:
                self.profile_manager.save_mapping(selected_profile, self.selected_key, button)
            self.selected_key = None
            self.selected_key_label["text"] = "Selected Key: None"

            # Keyboard representation
            keyboard_canvas = tk.Canvas(keyboard_frame, bg="#3e3e3e")
            keyboard_canvas.pack(fill="both", expand=True)
            # A more comprehensive keyboard layout
            keys = [
                ("Esc", 10, 10), ("F1", 60, 10), ("F2", 100, 10), ("F3", 140, 10), ("F4", 180, 10),
                ("`", 10, 50), ("1", 50, 50), ("2", 90, 50), ("3", 130, 50), ("4", 170, 50), ("5", 210, 50),
                ("Tab", 10, 90, 60), ("Q", 80, 90), ("W", 120, 90), ("E", 160, 90), ("R", 200, 90),
                ("Caps", 10, 130, 70), ("A", 90, 130), ("S", 130, 130), ("D", 170, 130), ("F", 210, 130),
                ("Shift", 10, 170, 80), ("Z", 100, 170), ("X", 140, 170), ("C", 180, 170), ("V", 220, 170),
                ("Ctrl", 10, 210, 60), ("Win", 80, 210), ("Alt", 130, 210), ("Space", 180, 210, 120),
            ]
            for item in keys:
                if len(item) == 3:
                    key, x, y = item
                    width = 30
                else:
                    key, x, y, width = item
                rect = keyboard_canvas.create_rectangle(x, y, x + width, y + 30, fill="#5e5e5e", outline="#00ff00", tags=("key", key))
                text = keyboard_canvas.create_text(x + width / 2, y + 15, text=key, fill="#00ff00", tags=("key_text", key))
                keyboard_canvas.tag_bind(rect, "<Button-1>", lambda event, k=key: self.select_key(k))
                keyboard_canvas.tag_bind(text, "<Button-1>", lambda event, k=key: self.select_key(k))

            # Controller representation
            controller_canvas = tk.Canvas(controller_frame, bg="#3e3e3e")
            controller_canvas.pack(fill="both", expand=True)
            # A more comprehensive controller layout
            buttons = [
                ("Y", 250, 50), ("X", 220, 80), ("B", 280, 80), ("A", 250, 110),
                ("LB", 50, 20), ("RB", 320, 20),
                ("LT", 50, -10, 60, 30), ("RT", 320, -10, 60, 30),
                ("View", 150, 80), ("Menu", 210, 80),
                ("L_Stick", 80, 120, 60), ("R_Stick", 290, 120, 60),
                ("D_Up", 120, 180), ("D_Down", 120, 240), ("D_Left", 90, 210), ("D_Right", 150, 210)
            ]
            for item in buttons:
                if len(item) == 3:
                    button, x, y = item
                    size = 30
                    oval = controller_canvas.create_oval(x, y, x + size, y + size, fill="#5e5e5e", outline="#00ff00", tags=("button", button))
                    text = controller_canvas.create_text(x + size / 2, y + size / 2, text=button, fill="#00ff00", tags=("button_text", button))
                    controller_canvas.tag_bind(oval, "<Button-1>", lambda event, b=button: self.select_button(b))
                    controller_canvas.tag_bind(text, "<Button-1>", lambda event, b=button: self.select_button(b))
                elif len(item) == 4:
                     button, x, y, size = item
                     oval = controller_canvas.create_oval(x, y, x + size, y + size, fill="#5e5e5e", outline="#00ff00", tags=("button", button))
                     text = controller_canvas.create_text(x + size / 2, y + size / 2, text=button, fill="#00ff00", tags=("button_text", button))
                     controller_canvas.tag_bind(oval, "<Button-1>", lambda event, b=button: self.select_button(b))
                     controller_canvas.tag_bind(text, "<Button-1>", lambda event, b=button: self.select_button(b))
                else:
                    button, x, y, width, height = item
                    rect = controller_canvas.create_rectangle(x, y, x + width, y + height, fill="#5e5e5e", outline="#00ff00", tags=("button", button))
                    text = controller_canvas.create_text(x + width / 2, y + height / 2, text=button, fill="#00ff00", tags=("button_text", button))
                    controller_canvas.tag_bind(rect, "<Button-1>", lambda event, b=button: self.select_button(b))
                    controller_canvas.tag_bind(text, "<Button-1>", lambda event, b=button: self.select_button(b))

        delete_button = ttk.Button(button_frame, text="Delete", command=self.delete_profile)
        delete_button.pack(side="left")

        activate_button = ttk.Button(button_frame, text="Activate", command=self.activate_profile)
        activate_button.pack(side="right")

    def activate_profile(self):
        selected_profile = self.profile_listbox.get(tk.ACTIVE)
        if selected_profile:
            self.profile_manager.set_active_profile(selected_profile)
            self.active_profile_name["text"] = selected_profile

    def new_profile(self):
        new_profile_window = tk.Toplevel(self)
        new_profile_window.title("New Profile")
        new_profile_window.geometry("400x200")
        new_profile_window.configure(bg="#1e1e1e")

        # Profile Name
        profile_name_frame = ttk.Frame(new_profile_window, padding="10")
        profile_name_frame.pack(fill="x")
        profile_name_label = ttk.Label(profile_name_frame, text="Profile Name:")
        profile_name_label.pack(side="left")
        profile_name_entry = ttk.Entry(profile_name_frame)
        profile_name_entry.pack(side="left", expand=True, fill="x")

        # Save Button
        save_button = ttk.Button(new_profile_window, text="Save", command=lambda: self.save_profile(profile_name_entry.get(), new_profile_window))
        save_button.pack(pady=10)

    def save_profile(self, profile_name, window):
        if profile_name:
            self.profile_manager.create_profile(profile_name)
            self.profile_listbox.insert(tk.END, profile_name)
            window.destroy()

    def delete_profile(self):
        selected_profile = self.profile_listbox.get(tk.ACTIVE)
        if selected_profile:
            # a confirmation dialog should be shown
            self.profile_manager.delete_profile(selected_profile)
            self.profile_listbox.delete(tk.ACTIVE)

if __name__ == "__main__":
    app = App()
    app.mainloop()
