# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /app

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /app/build

# Include any dependencies generated for this target.
include CMakeFiles/CoreService.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CoreService.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CoreService.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CoreService.dir/flags.make

CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj: /app/src/CoreService/Main.cpp
CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj -c /app/src/CoreService/Main.cpp

CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/Main.cpp > CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/Main.cpp -o CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.s

CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj: /app/src/CoreService/VirtualController.cpp
CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj -c /app/src/CoreService/VirtualController.cpp

CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/VirtualController.cpp > CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/VirtualController.cpp -o CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.s

CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj: /app/src/CoreService/DeviceEnumerator.cpp
CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj -c /app/src/CoreService/DeviceEnumerator.cpp

CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/DeviceEnumerator.cpp > CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/DeviceEnumerator.cpp -o CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.s

CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj: /app/src/CoreService/RawInputHandler.cpp
CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj -c /app/src/CoreService/RawInputHandler.cpp

CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/RawInputHandler.cpp > CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/RawInputHandler.cpp -o CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.s

CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj: /app/src/CoreService/MappingEngine.cpp
CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj -c /app/src/CoreService/MappingEngine.cpp

CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/MappingEngine.cpp > CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/MappingEngine.cpp -o CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.s

CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj: CMakeFiles/CoreService.dir/flags.make
CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj: CMakeFiles/CoreService.dir/includes_CXX.rsp
CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj: /app/src/CoreService/ProfileManager.cpp
CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj: CMakeFiles/CoreService.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj -MF CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj.d -o CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj -c /app/src/CoreService/ProfileManager.cpp

CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/CoreService/ProfileManager.cpp > CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.i

CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/CoreService/ProfileManager.cpp -o CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.s

# Object files for target CoreService
CoreService_OBJECTS = \
"CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj" \
"CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj" \
"CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj" \
"CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj" \
"CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj" \
"CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj"

# External object files for target CoreService
CoreService_EXTERNAL_OBJECTS =

CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/Main.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/VirtualController.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/DeviceEnumerator.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/RawInputHandler.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/MappingEngine.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/src/CoreService/ProfileManager.cpp.obj
CoreService.exe: CMakeFiles/CoreService.dir/build.make
CoreService.exe: CMakeFiles/CoreService.dir/linkLibs.rsp
CoreService.exe: CMakeFiles/CoreService.dir/objects1.rsp
CoreService.exe: CMakeFiles/CoreService.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable CoreService.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CoreService.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CoreService.dir/build: CoreService.exe
.PHONY : CMakeFiles/CoreService.dir/build

CMakeFiles/CoreService.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CoreService.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CoreService.dir/clean

CMakeFiles/CoreService.dir/depend:
	cd /app/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /app /app /app/build /app/build /app/build/CMakeFiles/CoreService.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CoreService.dir/depend
