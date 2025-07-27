import time
import sys
from virtual_controller import VirtualController
from profile_manager import ProfileManager
from mapping_engine import MappingEngine
from input_handler import InputHandler

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

    print("\n--- Available Profiles ---")
    for profile in profile_manager.profiles:
        print(f"- {profile['profileName']}")

    print(f"\nActivating profile: {profile_manager.active_profile['profileName']}")

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

if __name__ == "__main__":
    main()
