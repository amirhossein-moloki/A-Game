# Core Service - Input Mapper

This project is a C++ application for Windows that captures input from hardware devices (like keyboards and mice) and remaps them to a virtual gamepad controller (like an Xbox controller). It uses JSON-based profiles for flexible input mapping.

This allows you to play games that only support gamepads with your keyboard and mouse.

## Features

- **Profile-based Mapping:** Create and switch between different mapping profiles using simple JSON files.
- **Raw Input:** Uses the Windows Raw Input API to capture input, ensuring high compatibility and performance.
- **Virtual Controller Emulation:** Uses the ViGEmBus driver to create and manage virtual Xbox 360 controllers.
- **Dynamic Device Detection:** Enumerates connected HID (Human Interface Devices) at runtime.

## Dependencies

Before building the project, you need to install the following dependency:

- **[ViGEmBus Driver](https://github.com/ViGEm/ViGEmBus/releases):** This is a required kernel-mode driver. You must download and install it for the application to work.

The following dependency is managed automatically by CMake:

- **[nlohmann/json](https://github.com/nlohmann/json):** A C++ library for reading and parsing JSON profiles.

## How to Build

This project uses CMake to generate build files.

### Prerequisites

- A C++ compiler that supports C++17 (e.g., MSVC from Visual Studio).
- [CMake](https://cmake.org/download/) (version 3.10 or higher).
- [Git](https://git-scm.com/downloads/).

### Build Steps

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd <repository_directory>
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure and generate the project:**
    ```bash
    cmake ..
    ```
    *Note: If you are using Visual Studio, you can specify the generator, e.g., `cmake .. -G "Visual Studio 17 2022"`.*

4.  **Build the project:**
    ```bash
    cmake --build .
    ```
    This will create the `CoreService.exe` executable inside the `build/Debug` or `build/Release` directory.

## How to Use

1.  **Ensure ViGEmBus is installed.**
2.  **Run the executable:**
    Open a terminal or command prompt, navigate to the directory containing `CoreService.exe`, and run it:
    ```bash
    .\CoreService.exe
    ```
3.  The application will start in the background, load all available `.json` profiles from the `src/CoreService/Profiles/` directory, and activate the first one it finds.
4.  The console window will show the detected devices and which profile is active.
5.  While the application is running, inputs from your keyboard and mouse will be translated into virtual gamepad inputs according to the rules in the active profile.

## Creating Profiles

Profiles are JSON files that define how inputs are mapped. You can create your own `.json` files and place them in the `src/CoreService/Profiles/` directory.

The application currently loads a sample profile named `WarzoneDefaultMapping.json` which contains mappings for the game Warzone. You can use this file as a template to create your own profiles.

### Example Profile Structure

*(Note: The JSON parsing logic is still under development. The current structure is based on the provided `WarzoneDefaultMapping.json`.)*

```json
{
  "profileName": "My Custom Profile",
  "actions": [
    {
      "name": "Jump",
      "keyboardMouse": { "primary": "Spacebar" },
      "xboxController": { "primary": "A_Button" }
    },
    {
      "name": "Fire",
      "keyboardMouse": { "primary": "Mouse_LeftClick" },
      "xboxController": { "primary": "RT" }
    }
  ]
}
```

To exit the application, simply close the console window or press `Ctrl+C`.
