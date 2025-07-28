import time
import sys
import webbrowser
if sys.platform == "win32":
    import winreg
from virtual_controller import VirtualController
from profile_manager import ProfileManager
from mapping_engine import MappingEngine
from input_handler import InputHandler

def is_vigem_installed():
    if sys.platform == "win32":
        try:
            # Check for the ViGEmBus driver in the Windows registry
            key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r"SYSTEM\CurrentControlSet\Services\ViGEmBus")
            winreg.CloseKey(key)
            return True
        except (FileNotFoundError, NameError):
            return False
    return False

def main():
    print("Core Service Starting...")

    # Check for ViGEmBus driver
    if not is_vigem_installed():
        print("ViGEmBus driver not found. Please install it from https://github.com/ViGEm/ViGEmBus/releases")
        webbrowser.open("https://github.com/ViGEm/ViGEmBus/releases")
        sys.exit("ViGEmBus driver not found.")

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
