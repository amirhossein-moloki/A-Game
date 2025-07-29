# main.py
# This script initializes and runs the core components of the input mapper.
# It uses a multi-threaded approach to run the UI and the core service concurrently.
#
# UI Framework: tkinter
# - Chosen for its simplicity and inclusion in the standard Python library.
# - For a more modern and feature-rich UI, consider using a framework like
#   PyQt, Kivy, or a web-based solution with Eel or PyWebview.
#
# Core Service:
# - The core service handles input capturing, mapping, and virtual controller emulation.
# - It runs in a separate thread to avoid blocking the UI.
#
# Future Improvements:
# - Implement a more robust communication channel between the UI and the core service,
#   such as a queue-based system or a local API.
# - Add more detailed error handling and logging.

import threading
import time
import sys
from virtual_controller import VirtualController
from profile_manager import ProfileManager
from mapping_engine import MappingEngine
from input_handler import InputHandler
from ui import App

def main_service(app, profile_manager):
    print("Core Service Starting...")

    # Initialize components
    virtual_controller = VirtualController()
    mapping_engine = MappingEngine(virtual_controller, profile_manager)
    input_handler = InputHandler(mapping_engine)

    # Load profiles
    if not profile_manager.profiles:
        print("No profiles found. Exiting.")
        # We shouldn't exit, but rather show an error in the UI
        app.active_profile_name["text"] = "No profiles found."
        return

    # Update UI with profiles
    for profile in profile_manager.profiles:
        app.profile_listbox.insert(tk.END, profile['profileName'])

    app.active_profile_name["text"] = profile_manager.active_profile['profileName']


    # Start input handling
    input_handler.start()
    print("\nCore service is running. Press Ctrl+C to exit.")

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nShutting down...")
        input_handler.stop()
        # The virtual controller should be properly shut down
        # In a real scenario, you might need to release the gamepad explicitly
        print("Core Service Shut Down.")

def main():
    profile_manager = ProfileManager(profiles_dir="profiles")
    app = App(profile_manager)

    # Run the core service in a separate thread
    service_thread = threading.Thread(target=main_service, args=(app, profile_manager), daemon=True)
    service_thread.start()

    app.mainloop()

if __name__ == "__main__":
    main()
