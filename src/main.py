import sys
from virtual_controller import VirtualController
from profile_manager import ProfileManager
from mapping_engine import MappingEngine
from input_handler import InputHandler
from gui import Application

def main():
    print("Core Service Starting...")

    # Initialize components
    virtual_controller = VirtualController()
    profile_manager = ProfileManager(profiles_dir="profiles")
    mapping_engine = MappingEngine(virtual_controller, profile_manager)
    input_handler = InputHandler(mapping_engine)

    # Load profiles
    if not profile_manager.profiles:
        print("No profiles found. Exiting.")
        sys.exit(1)

    # Start input handling
    input_handler.start()
    print("\nCore service is running. Press Ctrl+C to exit.")

    # Start the GUI
    app = Application(profile_manager, mapping_engine)
    app.mainloop()

    print("\nShutting down...")
    input_handler.stop()
    print("Core Service Shut Down.")


if __name__ == "__main__":
    main()
